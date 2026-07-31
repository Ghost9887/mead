#ifndef MEAD_TEXT_H
#define MEAD_TEXT_H

#include "mead_component.h"
#include "mead_utility.h"
#include "mead_position.h"
#include <memory>
#include <string>

namespace Mead
{
    class Panel;

    class Text : public Mead::IComponent
    {
    public:
        Text(const std::string &text, const Mead::Allignment allignment);
        Text(const std::string &&text, const Mead::Allignment allignment);
        ~Text();

        int GetWidth() const;
        int GetHeight() const;
        int GetX() const;
        int GetY() const;
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
