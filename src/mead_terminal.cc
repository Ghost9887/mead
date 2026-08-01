#include "mead_terminal.h"
#include "mead_panel.h"
#include <termios.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <vector>
#include <string>
#include <signal.h>

class Mead::Terminal::Impl 
{
public:
    Impl() 
    {
        tcgetattr(STDIN_FILENO, &mOriginal);
        signal(SIGWINCH, Mead::Terminal::Impl::HandleResize);
        mRaw = mOriginal;
        mRaw.c_lflag &= ~(ICANON | ISIG | IEXTEN | ECHO);
        mRaw.c_iflag &= ~(ICRNL | IXON | BRKINT | INPCK | ISTRIP);
        mRaw.c_cc[VMIN] = 0;
        mRaw.c_cc[VTIME] = 1;
        tcsetattr(STDIN_FILENO, TCSAFLUSH, &mRaw);
        write(STDOUT_FILENO, "\033[2J", 4);
        write(STDOUT_FILENO, "\033[H", 3);
        struct winsize ws;
        ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws);
        mWidth = ws.ws_col;
        mHeight = ws.ws_row;
    }
    ~Impl()
    {
        tcsetattr(STDIN_FILENO, TCSAFLUSH, &mOriginal);
        write(STDOUT_FILENO, "\033[2J", 4);
        write(STDOUT_FILENO, "\033[H", 3);
    }

    static void HandleResize(int)
    {
        Mead::Terminal::GetInstance().mImpl->mHasResized = true;
    }

    void ResizePanel(Mead::Panel *panel)
    {
        panel->ResetPosition();
        for (Mead::IComponent* c : panel->GetComponents())
        {
            c->ResetPosition();
            if (auto* a = dynamic_cast<Mead::Panel*>(c)) ResizePanel(a);
        }
    }

    void ResizeContent()
    {
        struct winsize ws;
        ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws);
        mWidth = ws.ws_col;
        mHeight = ws.ws_row;

        for (auto* p : mPanels)
        {
            ResizePanel(p);
        }
        mHasResized = false;
    }

    std::pair<int, int> GetTerminalSize()
    {
        return { mWidth, mHeight };
    }

    char GetKey()
    {
        char c;
        read(STDIN_FILENO, &c, 1);
        return c;
    }
public:
    struct termios mOriginal;
    struct termios mRaw;
    bool mHasResized { false };
    int mWidth, mHeight;
    std::string mScreenBuffer {};
    std::string mAlternateBuffer {};
    std::vector<Mead::Panel*> mPanels {};
};

Mead::Terminal::Terminal() :
    mImpl(std::make_unique<Mead::Terminal::Impl>()) {}

Mead::Terminal::~Terminal() = default;

Mead::Terminal& Mead::Terminal::GetInstance() 
{
    static Mead::Terminal instance;
    return instance;
}

void Mead::Terminal::AddPanel(Mead::Panel &panel)
{
    mImpl->mPanels.push_back(&panel);
}

void Mead::Terminal::Render(Mead::Panel &panel)
{
    if (mImpl->mHasResized) mImpl->ResizeContent();

    panel.Display(mImpl->mAlternateBuffer);

    if (mImpl->mAlternateBuffer == mImpl->mScreenBuffer)
    {
        mImpl->mAlternateBuffer.clear();
        return;
    }

    mImpl->mScreenBuffer = std::move(mImpl->mAlternateBuffer);

    write(STDOUT_FILENO, "\x1b[?25l", 6);
    write(STDOUT_FILENO, "\x1b[H", 3);
    write(STDOUT_FILENO, "\x1b[2J", 4);
    write(STDOUT_FILENO, mImpl->mScreenBuffer.c_str(),
                          mImpl->mScreenBuffer.size());
    write(STDOUT_FILENO, "\x1b[?25h", 6);
}

void Mead::Terminal::RenderAll()
{
    for (auto* p : mImpl->mPanels)
    {
        Render(*p);
    }
}

int Mead::Terminal::GetTerminalWidth()
{
    return mImpl->GetTerminalSize().first;
}

int Mead::Terminal::GetTerminalHeight()
{
    return mImpl->GetTerminalSize().second;
}

std::pair<int, int> Mead::Terminal::GetTerminalSize() 
{
    return mImpl->GetTerminalSize();
}

char Mead::Terminal::GetKey()
{
    return mImpl->GetKey();
}
