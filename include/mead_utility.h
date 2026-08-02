#ifndef MEAD_UTILITY_H
#define MEAD_UTILITY_H

#include <string>
#include <format>

namespace Mead
{
    struct WidthPercent
    {
        explicit WidthPercent(int percent)
            : mWP(std::clamp(percent, 0, 100) / 100.0)
        {}

        double mWP;
    };
    
    struct HeightPercent 
    { 
        explicit HeightPercent(int percent)
            : mHP(std::clamp(percent, 0, 100) / 100.0)
        {}

        double mHP; 
    };

    enum class Alignment
    {
        TOP, RIGHT, BOTTOM, LEFT,
        TOP_LEFT, TOP_RIGHT, 
        BOTTOM_LEFT, BOTTOM_RIGHT, 
        CENTER,

        TITLE_LEFT, TITLE_CENTER, TITLE_RIGHT
    };

    struct RGB
    {
        uint8_t r;
        uint8_t g;
        uint8_t b;

        std::string ToAnsiForeground() const
        {
            return std::format("\033[38;2;{};{};{}m", r, g, b);
        }
        std::string ToAnsiBackground() const
        {
            return std::format("\033[48;2;{};{};{}m", r, g, b);
        }
        
        static RGB Red() { return RGB{180, 80, 80}; }
        static RGB Green() { return RGB{100, 170, 100}; }
        static RGB Blue() { return RGB{100, 120, 180}; }
    };
}

#endif
