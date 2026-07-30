#ifndef MEAD_PANEL_H
#define MEAD_PANEL_H

#include "mead_component.h"
#include "mead_utility.h"
#include "mead_position.h"
#include <memory>
#include <string>

namespace Mead 
{
    class Panel : public Mead::Component
    {
    public:
        Panel(Mead::XPercent x, Mead::YPercent y, Mead::Location location); 
        ~Panel();
        
        int GetWidth() const;
        int GetHeight() const;
        int GetX() const;
        int GetY() const;
        static Panel FullScreen();
        void Add(Mead::Component &component);
        void Display();
    protected:
        void SetParent(Mead::Panel *parent) override;
        void Display(std::string& buffer) override;
    private:
        class Impl;
        std::unique_ptr<Impl> mImpl;
    };
}

#endif
