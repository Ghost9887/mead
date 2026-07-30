#ifndef MEAD_COMPONENT_H
#define MEAD_COMPONENT_H

#include <string>

namespace Mead
{
    class Panel;

    class Component
    {
    public:
        virtual ~Component() = default;
        virtual void SetParent(Mead::Panel *parent) = 0;
        virtual void Display(std::string& buffer) = 0;
    };
}

#endif
