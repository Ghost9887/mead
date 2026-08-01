#include "mead_border.h"
#include "mead_panel.h"
#include <format>

class Mead::Border::Impl
{
public:
    Impl(const std::string horizontal, const std::string vertical, 
            const std::string topLeft, const std::string topRight, 
            const std::string bottomLeft, const std::string bottomRight) :
        mHorizontal(std::move(horizontal)), mVertical(std::move(vertical)), mTopLeft(std::move(topLeft)),
        mTopRight(std::move(topRight)), mBottomLeft(std::move(bottomLeft)), mBottomRight(std::move(bottomRight)) {}
    ~Impl() = default;
public:
    std::string mHorizontal;
    std::string mVertical;
    std::string mTopLeft;
    std::string mTopRight;
    std::string mBottomLeft;
    std::string mBottomRight;
    Mead::Style mStyle {};
    Mead::Panel* mParent { nullptr };
};

Mead::Border::Border(const std::string horizontal, const std::string vertical, 
        const std::string topRight, const std::string topLeft, const std::string bottomLeft,
        const std::string bottomRight) :
    mImpl(std::make_unique<Mead::Border::Impl>(std::move(horizontal), std::move(vertical), std::move(topRight),
                std::move(topLeft), std::move(bottomLeft), std::move(bottomRight))) {}

Mead::Border::~Border() = default;

Mead::Border Mead::Border::Basic()
{
    return Mead::Border("─", "│", "┌", "┐", "└", "┘");
}

Mead::Border Mead::Border::Round()
{
    return Mead::Border("─", "│", "╭", "╮", "╰", "╯");
}

Mead::Border Mead::Border::Thick()
{
    return Mead::Border("━", "┃", "┏", "┓", "┗", "┛");
}

Mead::Border& Mead::Border::SetColor(const Mead::RGB rgb)
{
    mImpl->mStyle.SetForegroundColor(std::move(rgb));
    return *this;
}

void Mead::Border::SetParent(Mead::Panel *parent)
{
    mImpl->mParent = parent;
}

void Mead::Border::Display(std::string& buffer)
{
    mImpl->mStyle.StartStyle(buffer);

    auto[x, y] { mImpl->mParent->GetPosition() };
    auto[width, height] { mImpl->mParent->GetSize() };
    
    for (std::size_t i {}; i < height; ++i)
    {
        for (std::size_t j {}; j < width; ++j)
        {
            buffer += std::format("\x1b[{};{}H", i + y + 1, j + x + 1);
            if (i == 0 && j == 0) buffer += mImpl->mTopLeft;
            else if (i == 0 && j == width - 1) buffer += mImpl->mTopRight;
            else if (i == height - 1 && j == 0) buffer += mImpl->mBottomLeft;
            else if (i == height - 1 && j == width - 1) buffer += mImpl->mBottomRight;
            else if (i == 0 || i == height - 1) buffer += mImpl->mHorizontal;
            else if (j == 0 || j == width - 1) buffer += mImpl->mVertical;
        }
    }

    mImpl->mStyle.EndStyle(buffer);
}

void Mead::Border::ResetPosition() {}
