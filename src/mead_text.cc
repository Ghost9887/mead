#include "mead_text.h"
#include <format>

class Mead::Text::Impl
{
public:
    Impl(const std::string& text, const Mead::Location location) :
        mText(text), mPosition(Mead::Position(location)) {}
    ~Impl() = default;

public:
    const std::string mText;
    Mead::Position mPosition;
    Mead::Panel *mParent { nullptr };
};

Mead::Text::Text(const std::string& text, const Mead::Location location) :
    mImpl(std::make_unique<Impl>(text, location)) {}

Mead::Text::Text(const std::string&& text, const Mead::Location location) :
    mImpl(std::make_unique<Impl>(text, location)) {}

Mead::Text::~Text() = default;

int Mead::Text::GetWidth() const
{
    return mImpl->mText.size();
}

int Mead::Text::GetHeight() const
{
    return 1; 
}

int Mead::Text::GetX() const
{
    return mImpl->mPosition.GetX();
}

int Mead::Text::GetY() const
{
    return mImpl->mPosition.GetY();
}

void Mead::Text::SetParent(Mead::Panel *parent)
{
    mImpl->mParent = parent;
}

void Mead::Text::Display(std::string& buffer)
{
    mImpl->mPosition.CalculatePosition(mImpl->mText.size(), 0, mImpl->mParent);
    auto[x, y] = mImpl->mPosition.GetPosition();
    buffer += std::format("\x1b[{};{}H", y + 1, x + 1);
    for (char c : mImpl->mText)
    {
        buffer += c; 
        buffer += std::format("\x1b[{};{}H", y + 1, ++x + 1);
    }
}
