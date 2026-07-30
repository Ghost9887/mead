#include "mead_border.h"
#include "mead_panel.h"
#include <format>

class Mead::Border::Impl
{
public:
    Impl(std::string& horizontal, std::string& vertical, 
            std::string& topLeft, std::string& topRight, 
            std::string& bottomLeft, std::string& bottomRight) :
        mHorizontal(horizontal), mVertical(vertical), mTopLeft(topLeft),
        mTopRight(topRight), mBottomLeft(bottomLeft), mBottomRight(bottomRight) {}
    ~Impl() = default;
public:
    std::string mHorizontal;
    std::string mVertical;
    std::string mTopLeft;
    std::string mTopRight;
    std::string mBottomLeft;
    std::string mBottomRight;
    Mead::Panel *mParent;
};

Mead::Border::Border(std::string&& horizontal, std::string&& vertical, 
        std::string&& topRight, std::string&& topLeft, std::string&& bottomLeft,
        std::string&& bottomRight) :
    mImpl(std::make_unique<Mead::Border::Impl>(horizontal, vertical, topRight,
                topLeft, bottomLeft, bottomRight)) {}

Mead::Border::~Border() = default;

Mead::Border Mead::Border::Basic()
{
    return Mead::Border("─", "│", "┌", "┐", "└", "┘");
}

void Mead::Border::SetParent(Mead::Panel *parent)
{
    mImpl->mParent = parent;
}

void Mead::Border::Display(std::string& buffer)
{
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
}
