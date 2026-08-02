#ifndef MEAD_PANEL_H
#define MEAD_PANEL_H

#include "mead_component.h"
#include "mead_utility.h"
#include <memory>
#include <string>
#include <utility>
#include <vector>

namespace Mead 
{
    class Terminal;
    class Position;

    class Panel : public Mead::IComponent
    {
    public:
        Panel(const Mead::WidthPercent widthPercent, 
              const Mead::HeightPercent heightPercent, 
              const Mead::Alignment alignment); 
        ~Panel();

        static Panel FullScreen();
        int GetWidth() const;
        int GetHeight() const;
        int GetX() const;
        int GetY() const;
        std::pair<int, int> GetSize() const;
        std::pair<int, int> GetPosition() const;
        Panel& Add(Mead::IComponent &component);

        friend class Mead::Terminal;
    protected:
        std::vector<IComponent*>& GetComponents();
        void SetParent(Mead::Panel *parent) override;
        void Display(std::string& buffer) override;
        void ResetPosition() override;
    private:
        class Impl;
        std::unique_ptr<Impl> mImpl;
    };
}

#endif
