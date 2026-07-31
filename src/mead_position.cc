#include "mead_position.h"
#include "mead_panel.h"
#include "mead_terminal.h"
#include <optional>
#include <utility>

class Mead::Position::Impl
{
public:
    Impl(Mead::Anchor anchor) :
        mAnchor(anchor) {}
    Impl(Mead::Allignment allignment) :
        mAllignment(allignment) {}
    ~Impl() = default;
    
    void SetPosition(std::pair<int, int>&& position)
    {
        mPosition = position;
    }

public:
    std::optional<Mead::Anchor> mAnchor { std::nullopt };
    std::optional<Mead::Allignment> mAllignment { std::nullopt };
    std::optional<std::pair<int, int>> mPosition { std::nullopt };
};

Mead::Position::Position(Mead::Anchor anchor) :
    mImpl(std::make_unique<Mead::Position::Impl>(anchor)) {}

Mead::Position::Position(Mead::Allignment allignment) :
    mImpl(std::make_unique<Mead::Position::Impl>(allignment)) {}

Mead::Position::~Position() = default;

//includes the border area
void Mead::Position::CalculateAnchorPosition(int width, int height, const Mead::Panel *parent)
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

    switch (mImpl->mAnchor.value())
    {
        case Mead::Anchor::TOP:
            mImpl->SetPosition({
                baseX + (parentWidth - width) / 2,
                baseY
            });
            break;
        case Mead::Anchor::RIGHT:
            mImpl->SetPosition({
                baseX + (parentWidth - width),
                baseY + (parentHeight - height) / 2
            });
            break;
        case Mead::Anchor::BOTTOM:
            mImpl->SetPosition({
                baseX + (parentWidth - width) / 2,
                baseY + parentHeight - height
            });
            break;
        case Mead::Anchor::LEFT:
            mImpl->SetPosition({
                baseX,
                baseY + (parentHeight - height) / 2
            });
            break;
        case Mead::Anchor::TOP_LEFT:
            mImpl->SetPosition({ baseX, baseY});
            break;
        case Mead::Anchor::TOP_RIGHT:
            mImpl->SetPosition({
                baseX + (parentWidth - width),
                baseY
            });
            break;
        case Mead::Anchor::BOTTOM_LEFT:
            mImpl->SetPosition({
                baseX,
                baseY + parentHeight - height
            });
            break;
        case Mead::Anchor::BOTTOM_RIGHT:
            mImpl->SetPosition({
                baseX + (parentWidth - width),
                baseY + parentHeight - height
            });
            break;
        case Mead::Anchor::CENTER:
            mImpl->SetPosition({
                baseX + (parentWidth  - width)  / 2,
                baseY + (parentHeight - height) / 2
            });
            break;
    }
}

void Mead::Position::CalculateAllignmentPosition(int width, int height, const Mead::Panel *parent)
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

    switch (mImpl->mAllignment.value())
    {
        case Mead::Allignment::TOP:
            mImpl->SetPosition({
                baseX + (parentWidth - width) / 2,
                baseY + 1
            });
            break;
        case Mead::Allignment::RIGHT:
            mImpl->SetPosition({
                baseX + (parentWidth - width) - 1,
                baseY + (parentHeight - height) / 2
            });
            break;
        case Mead::Allignment::BOTTOM:
            mImpl->SetPosition({
                baseX + (parentWidth - width) / 2,
                baseY + parentHeight - height - 1
            });
            break;
        case Mead::Allignment::LEFT:
            mImpl->SetPosition({
                baseX + 1,
                baseY + (parentHeight - height) / 2
            });
            break;
        case Mead::Allignment::TOP_LEFT:
            mImpl->SetPosition({ baseX + 1, baseY + 1});
            break;
        case Mead::Allignment::TOP_RIGHT:
            mImpl->SetPosition({
                baseX + (parentWidth - width) - 1,
                baseY + 1
            });
            break;
        case Mead::Allignment::BOTTOM_LEFT:
            mImpl->SetPosition({
                baseX + 1,
                baseY + parentHeight - height - 1
            });
            break;
        case Mead::Allignment::BOTTOM_RIGHT:
            mImpl->SetPosition({
                baseX + (parentWidth - width) - 1,
                baseY + parentHeight - height - 1
            });
            break;
        case Mead::Allignment::CENTER:
            mImpl->SetPosition({
                baseX + (parentWidth  - width)  / 2,
                baseY + (parentHeight - height) / 2
            });
            break;
        case Mead::Allignment::TITLE_CENTER:
            mImpl->SetPosition({
                baseX + (parentWidth - width) / 2,
                baseY
            });
            break;
        case Mead::Allignment::TITLE_LEFT:
            mImpl->SetPosition({ baseX, baseY});
            break;
        case Mead::Allignment::TITLE_RIGHT:
            mImpl->SetPosition({
                baseX + (parentWidth - width),
                baseY
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
