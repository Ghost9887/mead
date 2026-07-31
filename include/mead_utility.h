#ifndef MEAD_UTILITY_H
#define MEAD_UTILITY_H

namespace Mead
{
    struct WidthPercent 
    { 
        WidthPercent(int percent)
        {
            if (percent < 0) percent = 0;
            else if (percent > 100) percent = 100;
            mWP = static_cast<double>(percent) / 100;
        }

        double mWP; 
    };
    
    struct HeightPercent 
    { 
        HeightPercent(int percent)
        {
            if (percent < 0) percent = 0;
            else if (percent > 100) percent = 100;
            mHP = static_cast<double>(percent) / 100;
        }

        double mHP; 
    };
}

#endif
