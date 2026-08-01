#include "mead_style.h"
#include "mead_utility.h"
#include <optional>

class Mead::Style::Impl
{
public:
    Impl() = default;
    ~Impl() = default;
    
public:
    std::optional<Mead::RGB> mForegroundColor { std::nullopt };
    std::optional<Mead::RGB> mBackgroundColor { std::nullopt };
};

Mead::Style::Style() :
    mImpl(std::make_unique<Mead::Style::Impl>()) {}

Mead::Style::~Style() = default;

void Mead::Style::SetForegroundColor(const Mead::RGB rgb)
{
    mImpl->mForegroundColor = std::move(rgb);
}

void Mead::Style::SetBackgroundColor(const Mead::RGB rgb)
{
    mImpl->mBackgroundColor = std::move(rgb);
}

void Mead::Style::StartStyle(std::string& buffer)
{
    if (mImpl->mForegroundColor.has_value()) buffer += mImpl->mForegroundColor.value().ToAnsiForeground(); 
    if (mImpl->mBackgroundColor.has_value()) buffer += mImpl->mBackgroundColor.value().ToAnsiBackground();
}

void Mead::Style::EndStyle(std::string& buffer)
{
    if (mImpl->mForegroundColor.has_value()) buffer += "\033[39m";
    if (mImpl->mBackgroundColor.has_value()) buffer += "\033[49m";
}

