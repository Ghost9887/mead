#include "mead_panel.h"
#include "mead_terminal.h"
#include "mead_position.h"
#include <unistd.h>
#include <utility>

class Mead::Panel::Impl
{
public:
    Impl(const Mead::WidthPercent widthPercent, const Mead::HeightPercent heightPercent, const Mead::Alignment alignment) :
        mWidthPercent(std::move(widthPercent)), mHeightPercent(std::move(heightPercent)), mPosition(Mead::Position(alignment)) {}
    ~Impl() = default;
    
    void Add(Mead::IComponent &component)
    {
        mComponents.push_back(&component);
        
    }
    
    void CalculateSize()
    {
        std::pair<int, int> size { Mead::Terminal::GetInstance().GetTerminalSize() };
        if (mParent)
        {
            //we want the panel to be in the parent panel so we dont include the edges
            size.first = mParent->GetWidth() - 2;
            size.second = mParent->GetHeight() - 2;
        }

        mWidth = size.first * mWidthPercent.mWP;
        mHeight = size.second * mHeightPercent.mHP;
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
    int mWidth, mHeight, mInnerWidth, mInnerHeight;
    Mead::Position mPosition;
    std::vector<Mead::IComponent*> mComponents {};
    std::string mScreenBuffer {};
    Mead::Panel* mParent { nullptr };
};

Mead::Panel::Panel(const Mead::WidthPercent widthPercent, 
        const Mead::HeightPercent heightPercent, const Mead::Alignment alignment) :
    mImpl(std::make_unique<Mead::Panel::Impl>(std::move(widthPercent), std::move(heightPercent), std::move(alignment))) {}

Mead::Panel::~Panel() = default;

Mead::Panel Mead::Panel::FullScreen()
{
    return Mead::Panel(Mead::WidthPercent(100), Mead::HeightPercent(100), Mead::Alignment::TOP_LEFT);
}

Mead::Panel& Mead::Panel::Add(Mead::IComponent &component)
{
    mImpl->Add(component);
    component.SetParent(this);
    return *this;
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
    mImpl->mPosition.CalculatePosition(mImpl->mWidth, mImpl->mHeight, mImpl->mParent);

    for (auto* c : mImpl->mComponents)
    {
        c->Display(buffer);
    }
}

void Mead::Panel::ResetPosition()
{
    mImpl->mPosition.ResetPosition();
}
