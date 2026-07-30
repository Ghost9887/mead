#include "mead_panel.h"
#include "mead.h"
#include <vector>
#include <unistd.h>
#include <utility>

class Mead::Panel::Impl
{
public:
    Impl(Mead::XPercent xPercent, Mead::YPercent yPercent, Mead::Location location) :
        mXPercent(xPercent), mYPercent(yPercent), mPosition(Mead::Position(location)) {}
    ~Impl() = default;

    void Add(Mead::Component &component)
    {
        mComponents.push_back(&component);
        
    }
    
    void CalculateSize()
    {
        auto[width, height] = Mead::Terminal::GetInstance().GetTerminalSize();
        mWidth  = width  * static_cast<float>(mXPercent.p / 100.0f);
        mHeight = height * static_cast<float>(mYPercent.p / 100.0f);

        if (mParent)
        {
            mWidth = mParent->GetWidth() * (static_cast<float>((mXPercent.p / 100.0f)));
            mHeight = mParent->GetHeight() * (static_cast<float>((mYPercent.p / 100.0f)));
        }
    }

    void Display()
    {
        CalculateSize();
        mPosition.CalculatePosition(mWidth, mHeight, mParent);

        for (auto* c : mComponents)
        {
            c->Display(mScreenBuffer);
        }

        mScreenBuffer += "\x1b[?25h";
        write(STDOUT_FILENO, mScreenBuffer.c_str(), mScreenBuffer.size());
        mScreenBuffer.clear();
        mScreenBuffer += "\x1b[?25l"; 
        mScreenBuffer += "\x1b[2J";
    }
public:
    Mead::XPercent mXPercent;
    Mead::YPercent mYPercent;
    Mead::Position mPosition;
    int mWidth, mHeight;
    std::vector<Mead::Component*> mComponents {};
    std::string mScreenBuffer {};
    Mead::Panel *mParent { nullptr };
};

Mead::Panel::Panel(Mead::XPercent xPercent, Mead::YPercent yPercent, Mead::Location location) :
    mImpl(std::make_unique<Mead::Panel::Impl>(xPercent, yPercent, location)) {}

Mead::Panel::~Panel() = default;

Mead::Panel Mead::Panel::FullScreen()
{
    return Mead::Panel(Mead::XPercent(100), Mead::YPercent(100), Mead::Location::TOP_LEFT);
}

void Mead::Panel::Add(Mead::Component &component)
{
    mImpl->Add(component);
    component.SetParent(this);
}

void Mead::Panel::SetParent(Mead::Panel *parent)
{
    mImpl->mParent = parent;
}

void Mead::Panel::Display()
{
    mImpl->Display();
}

int Mead::Panel::GetWidth() const
{
    return mImpl->mWidth;
}

int Mead::Panel::GetHeight() const
{
    return mImpl->mHeight;
}

int Mead::Panel::GetX() const
{
    return mImpl->mPosition.GetX();
}

int Mead::Panel::GetY() const
{
    return mImpl->mPosition.GetY();
}

void Mead::Panel::Display(std::string &buffer)
{
    mImpl->CalculateSize();
    mImpl->mPosition.CalculatePosition(mImpl->mWidth, mImpl->mHeight, mImpl->mParent);

    for (auto* c : mImpl->mComponents)
    {
        c->Display(buffer);
    }
}
