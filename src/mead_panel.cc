#include "mead_panel.h"
#include "mead_terminal.h"
#include "mead_position.h"
#include <unistd.h>
#include <utility>

class Mead::Panel::Impl
{
public:
    Impl(const Mead::WidthPercent widthPercent, const Mead::HeightPercent heightPercent, const Mead::Anchor anchor) :
        mWidthPercent(std::move(widthPercent)), mHeightPercent(std::move(heightPercent)), mPosition(Mead::Position(anchor)) {}
    ~Impl() = default;
    
    void Add(Mead::IComponent &component)
    {
        mComponents.push_back(&component);
        
    }
    
    void CalculateSize()
    {
        auto[width, height] = Mead::Terminal::GetInstance().GetTerminalSize();
        mWidth = width  * mWidthPercent.mWP;
        mHeight = height * mHeightPercent.mHP;
    }
    
    void Clear(std::string &buffer)
    {
        auto [x, y] = mPosition.GetPosition();

        std::string blankRow(mWidth, ' ');

        for (std::size_t i = 0; i < mHeight; ++i)
        {
            buffer += std::format("\x1b[{};{}H", y + i + 1, x + 1);
            buffer += blankRow;
        }
    }

public:
    const Mead::WidthPercent mWidthPercent;
    const Mead::HeightPercent mHeightPercent;
    int mWidth, mHeight;
    Mead::Position mPosition;
    std::vector<Mead::IComponent*> mComponents {};
    std::string mScreenBuffer {};
    Mead::Panel* mParent { nullptr };
};

Mead::Panel::Panel(const Mead::WidthPercent widthPercent, 
        const Mead::HeightPercent heightPercent, const Mead::Anchor anchor) :
    mImpl(std::make_unique<Mead::Panel::Impl>(std::move(widthPercent), std::move(heightPercent), std::move(anchor))) {}

Mead::Panel::~Panel() = default;

Mead::Panel Mead::Panel::FullScreen()
{
    return Mead::Panel(Mead::WidthPercent(100), Mead::HeightPercent(100), Mead::Anchor::TOP_LEFT);
}

void Mead::Panel::Add(Mead::IComponent &component)
{
    mImpl->Add(component);
    component.SetParent(this);
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

std::pair<int, int> Mead::Panel::GetSize() const
{
    return { GetWidth(), GetHeight() };
}

std::pair<int, int> Mead::Panel::GetPosition() const
{
    return { GetX(), GetY() };
}

std::vector<Mead::IComponent*>& Mead::Panel::GetComponents()
{
    return mImpl->mComponents;
}

void Mead::Panel::SetParent(Mead::Panel *parent)
{
    mImpl->mParent = parent;
}

void Mead::Panel::Display(std::string &buffer)
{
    //this is for panels that overlap so they draw over eachother
    mImpl->Clear(buffer);

    mImpl->CalculateSize();
    mImpl->mPosition.CalculatePosition(mImpl->mWidth, mImpl->mHeight, nullptr);

    for (auto* c : mImpl->mComponents)
    {
        c->Display(buffer);
    }
}

void Mead::Panel::ResetPosition()
{
    mImpl->mPosition.ResetPosition();
}
