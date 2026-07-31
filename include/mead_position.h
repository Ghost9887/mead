#ifndef MEAD_POSITION_H
#define MEAD_POSITION_H

#include <memory>
#include <utility>

namespace Mead
{
    class Panel;

    enum class Location
    {
        TOP, RIGHT, BOTTOM, LEFT,
        TOP_LEFT, TOP_RIGHT, 
        BOTTOM_LEFT, BOTTOM_RIGHT,
        CENTER
    };

    class Position
    {
    public:
        Position(Location location);
        ~Position();
        
        int GetX() const;
        int GetY() const;
        std::pair<int, int> GetPosition() const;
        void CalculatePosition(int width, int height, const Mead::Panel *parent);
        void ResetPosition();
    private:
        class Impl;
        std::unique_ptr<Impl> mImpl;
    };
}   

#endif
