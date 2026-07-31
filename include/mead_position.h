#ifndef MEAD_POSITION_H
#define MEAD_POSITION_H

#include <memory>
#include <utility>

namespace Mead
{
    class Panel;

    enum class Anchor
    {
        TOP, RIGHT, BOTTOM, LEFT,
        TOP_LEFT, TOP_RIGHT, 
        BOTTOM_LEFT, BOTTOM_RIGHT, 
        CENTER,
    };

    enum class Allignment
    {
        TOP, RIGHT, BOTTOM, LEFT,
        TOP_LEFT, TOP_RIGHT, 
        BOTTOM_LEFT, BOTTOM_RIGHT, 
        CENTER,

        TITLE_LEFT, TITLE_CENTER, TITLE_RIGHT
    };

    class Position
    {
    public:
        Position(Mead::Anchor anchor);
        Position(Mead::Allignment allignment);
        ~Position();
        
        int GetX() const;
        int GetY() const;
        std::pair<int, int> GetPosition() const;
        void CalculateAnchorPosition(int width, int height, const Mead::Panel *parent);
        void CalculateAllignmentPosition(int width, int height, const Mead::Panel *parent);
        void ResetPosition();
    private:
        class Impl;
        std::unique_ptr<Impl> mImpl;
    };
}   

#endif
