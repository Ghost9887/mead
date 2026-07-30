#ifndef MEAD_BORDER_H
#define MEAD_BORDER_H

#include <memory>
#include <string>
#include "mead_border.h"
#include "mead_component.h"

namespace Mead
{
    class Panel;

    class Border : public Mead::Component
    {
    public:
        Border(std::string&& horizontal, std::string&& vertical, 
            std::string&& topRight, std::string&& topLeft, std::string&& bottomLeft,
            std::string&& bottomRight);
        ~Border();

        static Border Basic();
    protected:
        void SetParent(Mead::Panel *parent) override;
        void Display(std::string& buffer) override;
    private:
        class Impl;
        std::unique_ptr<Impl> mImpl;
    };
}

#endif
