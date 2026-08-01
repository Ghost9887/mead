#include "mead_text.h"
#include "mead_panel.h"
#include "mead_position.h"
#include "mead_style.h"
#include <format>
#include <optional>

class Mead::Text::Impl
{
public:
    Impl(const std::string text, const Mead::Alignment alignment) :
        mText(std::move(text)), mPosition(Mead::Position(alignment)) {}
    ~Impl() = default;

public:
    std::string mText;
    Mead::Position mPosition;
    Mead::Style mStyle;
    Mead::Panel* mParent { nullptr };
};

Mead::Text::Text(const std::string text, const Mead::Alignment alignment) :
    mImpl(std::make_unique<Impl>(std::move(text), std::move(alignment))) {}

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

Mead::Text& Mead::Text::SetForegroundColor(const Mead::RGB rgb)
{
    mImpl->mStyle.SetForegroundColor(std::move(rgb));
    return *this;
}

Mead::Text& Mead::Text::SetBackgroundColor(const Mead::RGB rgb)
{
    mImpl->mStyle.SetBackgroundColor(std::move(rgb));
    return *this;
}

Mead::Text& Mead::Text::SetText(std::string text)
{
    mImpl->mText = std::move(text);
    return *this;
}

void Mead::Text::SetParent(Mead::Panel* parent)
{
    mImpl->mParent = parent;
}

void Mead::Text::Display(std::string& buffer)
{
    mImpl->mStyle.StartStyle(buffer);

    mImpl->mPosition.CalculatePosition(mImpl->mText.size(), 0, mImpl->mParent);
    auto[x, y] = mImpl->mPosition.GetPosition();
    buffer += std::format("\x1b[{};{}H", y + 1, x + 1);
    for (char c : mImpl->mText)
    {
        buffer += c; 
        buffer += std::format("\x1b[{};{}H", y + 1, ++x + 1);
    }

    mImpl->mStyle.EndStyle(buffer);
}

void Mead::Text::ResetPosition()
{
    mImpl->mPosition.ResetPosition();
}
