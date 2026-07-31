#ifndef MEAD_BORDER_H
#define MEAD_BORDER_H

#include <memory>
#include <string>
#include "mead_border.h"
#include "mead_component.h"

namespace Mead
{
    class Panel;

    class Border : public Mead::IComponent
    {
    public:
        Border(std::string&& horizontal, std::string&& vertical, 
            std::string&& topRight, std::string&& topLeft, std::string&& bottomLeft,
            std::string&& bottomRight);
        ~Border();

        static Border Basic();
        static Border Round();
        static Border Thick();
    protected:
        void SetParent(Mead::Panel *parent) override;
        void Display(std::string& buffer, std::size_t id) override;
        void ResetPosition() override;
    private:
        class Impl;
        std::unique_ptr<Impl> mImpl;
    };
}

#endif
