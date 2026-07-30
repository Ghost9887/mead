#include "mead_terminal.h"
#include "mead_panel.h"
#include <termios.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <vector>
#include <string>

class Mead::Terminal::Impl 
{
public:
    Impl() 
    {
        tcgetattr(STDIN_FILENO, &mOriginal);
        mRaw = mOriginal;
        mRaw.c_lflag &= ~(ICANON | ISIG | IEXTEN | ECHO);
        mRaw.c_iflag &= ~(ICRNL | IXON | BRKINT | INPCK | ISTRIP);
        tcsetattr(STDIN_FILENO, TCSAFLUSH, &mRaw);
        write(STDOUT_FILENO, "\033[2J", 4);
        write(STDOUT_FILENO, "\033[H", 3);
    }
    ~Impl()
    {
        tcsetattr(STDIN_FILENO, TCSAFLUSH, &mOriginal);
        write(STDOUT_FILENO, "\033[2J", 4);
        write(STDOUT_FILENO, "\033[H", 3);
    }

    std::pair<int, int> GetTerminalSize()
    {
        struct winsize ws;
        ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws);       

        return { ws.ws_col, ws.ws_row };
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
