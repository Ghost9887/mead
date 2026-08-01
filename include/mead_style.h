#ifndef MEAD_STYLE_H
#define MEAD_STYLE_H

#include <memory>
#include <string>
#include "mead_utility.h"

namespace Mead
{
    class Style
    {
    public:
        Style();
        ~Style();
        
        void SetForegroundColor(Mead::RGB rgb);
        void SetBackgroundColor(Mead::RGB rgb);

        void StartStyle(std::string& buffer);
        void EndStyle(std::string& buffer);
    private:
        class Impl;
        std::unique_ptr<Impl> mImpl;
    };
}

#endif
