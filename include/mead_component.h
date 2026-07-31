#ifndef MEAD_COMPONENT_H
#define MEAD_COMPONENT_H

#include <string>

namespace Mead
{
    class Panel;

    class IComponent
    {
    public:
        virtual ~IComponent() = default;
        virtual void SetParent(Mead::Panel *parent) = 0;
        virtual void Display(std::string& buffer, std::size_t id) = 0;
        virtual void ResetPosition() = 0;
    };
}

#endif
