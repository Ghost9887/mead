#ifndef MEAD_POSITION_H
#define MEAD_POSITION_H

#include "mead_utility.h"
#include <memory>
#include <utility>

namespace Mead
{
    class Panel;

    class Position
    {
    public:
        Position(Mead::Anchor anchor);
        Position(Mead::Alignment alignment);
        ~Position();
        
        int GetX() const;
        int GetY() const;
        std::pair<int, int> GetPosition() const;
        void CalculatePosition(const int width, const int height, const Mead::Panel *parent);
        void ResetPosition();
    private:
        class Impl;
        std::unique_ptr<Impl> mImpl;
    };
}   

#endif
