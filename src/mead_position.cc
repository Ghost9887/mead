#include "mead_position.h"
#include "mead_panel.h"
#include "mead_terminal.h"
#include <optional>
#include <utility>

class Mead::Position::Impl
{
public:
    Impl(Mead::Location location) :
        mLocation(location) {}
    ~Impl() = default;
    
    void SetPosition(std::pair<int, int>&& position)
    {
        mPosition = position;
    }

public:
    Mead::Location mLocation;
    std::optional<std::pair<int, int>> mPosition { std::nullopt };
};

Mead::Position::Position(Mead::Location location) :
    mImpl(std::make_unique<Mead::Position::Impl>(location)) {}

Mead::Position::~Position() = default;

void Mead::Position::CalculatePosition(int width, int height, const Mead::Panel *parent)
{
    if (mImpl->mPosition.has_value()) return;

    int baseX {};
    int baseY {};
    int parentWidth {};
    int parentHeight {};

    if (parent)
    {
        baseX = parent->GetX();
        baseY = parent->GetY();
        parentWidth  = parent->GetWidth();
        parentHeight = parent->GetHeight();
    }
    else
    {
        auto [termWidth, termHeight] = Mead::Terminal::GetInstance().GetTerminalSize();
        parentWidth  = termWidth;
        parentHeight = termHeight;
    }

    switch (mImpl->mLocation)
    {
        case Mead::Location::TOP:
            mImpl->SetPosition({
                baseX + (parentWidth - width) / 2,
                baseY
            });
            break;

        case Mead::Location::RIGHT:
            mImpl->SetPosition({
                baseX + (parentWidth - width),
                baseY + (parentHeight - height) / 2
            });
            break;

        case Mead::Location::BOTTOM:
            mImpl->SetPosition({
                baseX + (parentWidth - width) / 2,
                baseY + parentHeight - height
            });
            break;

        case Mead::Location::LEFT:
            mImpl->SetPosition({
                baseX,
                baseY + (parentHeight - height) / 2
            });
            break;

        case Mead::Location::TOP_LEFT:
            mImpl->SetPosition({ baseX, baseY });
            break;

        case Mead::Location::TOP_RIGHT:
            mImpl->SetPosition({
                baseX + (parentWidth - width),
                baseY
            });
            break;

        case Mead::Location::BOTTOM_LEFT:
            mImpl->SetPosition({
                baseX,
                baseY + parentHeight - height
            });
            break;

        case Mead::Location::BOTTOM_RIGHT:
            mImpl->SetPosition({
                baseX + (parentWidth - width),
                baseY + parentHeight - height
            });
            break;

        case Mead::Location::CENTER:
            mImpl->SetPosition({
                baseX + (parentWidth  - width)  / 2,
                baseY + (parentHeight - height) / 2
            });
            break;
    }
}

int Mead::Position::GetX() const
{
    if (mImpl->mPosition.has_value())
    {
        return mImpl->mPosition.value().first;
    }
    return 0;
}

int Mead::Position::GetY() const
{
    if (mImpl->mPosition.has_value())
    {
        return mImpl->mPosition.value().second;
    }
    return 0;
}

std::pair<int, int> Mead::Position::GetPosition() const
{
    if (!mImpl->mPosition.has_value()) return { 0, 0 };
    return mImpl->mPosition.value();
}

void Mead::Position::ResetPosition()
{
    mImpl->mPosition = std::nullopt;
}
