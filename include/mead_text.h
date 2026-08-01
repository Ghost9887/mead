#ifndef MEAD_TEXT_H
#define MEAD_TEXT_H

#include "mead_component.h"
#include "mead_utility.h"
#include <memory>
#include <string>

namespace Mead
{
    class Panel;
    class Position;

    class Text : public Mead::IComponent
    {
    public:
        Text(const std::string text, const Mead::Alignment alignment);
        ~Text();

        int GetWidth() const;
        int GetHeight() const;
        int GetX() const;
        int GetY() const;
        
        Text& SetText(std::string text);
        Text& SetForegroundColor(const Mead::RGB rgb);
        Text& SetBackgroundColor(const Mead::RGB rgb);
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
