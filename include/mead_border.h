#ifndef MEAD_BORDER_H
#define MEAD_BORDER_H

#include <memory>
#include <string>
#include "mead_component.h"
#include "mead_style.h"

namespace Mead
{
    class Panel;

    class Border : public Mead::IComponent
    {
    public:
        Border(const std::string horizontal, const std::string vertical, 
            const std::string topRight, const std::string topLeft, const std::string bottomLeft,
            const std::string bottomRight);
        ~Border();

        static Border Basic();
        static Border Round();
        static Border Thick();

        Border& SetColor(const Mead::RGB rgb);
    protected:
        void SetParent(Mead::Panel *parent) override;
        void Display(std::string& buffer) override;
        void ResetPosition() override;
    private:
        class Impl;
        std::unique_ptr<Impl> mImpl;
    };
}

#endif
