#include "mead_panel.h"
#include "mead_terminal.h"
#include <unistd.h>
#include <utility>
#include <unordered_map>

class Mead::Panel::Impl
{
public:
    Impl(Mead::WidthPercent widthPercent, Mead::HeightPercent heightPercent, Mead::Location location) :
        mInstanceId(mGlobalId++), mWidthPercent(widthPercent), 
        mHeightPercent(heightPercent), mPosition(Mead::Position(location)) {}
    ~Impl() = default;
    
    std::size_t GetId() const
    {
        return mInstanceId;
    }

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
public:
    inline static std::size_t mGlobalId { 1 }; // 0 is the terminal
    std::size_t mInstanceId;
    Mead::WidthPercent mWidthPercent;
    Mead::HeightPercent mHeightPercent;
    int mWidth, mHeight;
    Mead::Position mPosition;
    std::vector<Mead::IComponent*> mComponents {};
    std::string mScreenBuffer {};
    std::unordered_map<std::size_t, Mead::Panel*> mParents {};
};

Mead::Panel::Panel(Mead::WidthPercent widthPercent, Mead::HeightPercent heightPercent, Mead::Location location) :
    mImpl(std::make_unique<Mead::Panel::Impl>(widthPercent, heightPercent, location)) {}

Mead::Panel::~Panel() = default;

Mead::Panel Mead::Panel::FullScreen()
{
    return Mead::Panel(Mead::WidthPercent(100), Mead::HeightPercent(100), Mead::Location::TOP_LEFT);
}

void Mead::Panel::Add(Mead::IComponent &component)
{
    mImpl->Add(component);
    component.SetParent(this);
}

std::size_t Mead::Panel::GetId() const
{
    return mImpl->mInstanceId;
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

std::pair<int, int> Mead::Panel::GetSize()
{
    return { GetWidth(), GetHeight() };
}

std::pair<int, int> Mead::Panel::GetPosition()
{
    return { GetX(), GetY() };
}

std::vector<Mead::IComponent*>& Mead::Panel::GetComponents()
{
    return mImpl->mComponents;
}

void Mead::Panel::SetParent(Mead::Panel *parent)
{
    mImpl->mParents.insert({parent->GetId(), parent});
}

void Mead::Panel::Display(std::string &buffer, std::size_t id)
{
    if (mImpl->mParents.find(id) == mImpl->mParents.end() && id != 0) return;
    
    mImpl->CalculateSize();
    mImpl->mPosition.CalculatePosition(mImpl->mWidth, mImpl->mHeight, (id != 0) ? mImpl->mParents[id] : nullptr);

    for (auto* c : mImpl->mComponents)
    {
        c->Display(buffer, GetId());
    }
}

void Mead::Panel::ResetPosition()
{
    mImpl->mPosition.ResetPosition();
}
