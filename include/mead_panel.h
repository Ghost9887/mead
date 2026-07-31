#ifndef MEAD_PANEL_H
#define MEAD_PANEL_H

#include "mead_component.h"
#include "mead_utility.h"
#include "mead_position.h"
#include <memory>
#include <string>
#include <utility>
#include <vector>

namespace Mead 
{
    class Terminal;
    class Panel : public Mead::IComponent
    {
    public:
        Panel(Mead::WidthPercent widthPercent, Mead::HeightPercent heightPercent, Mead::Location location); 
        ~Panel();
        
        std::size_t GetId() const;
        int GetWidth() const;
        int GetHeight() const;
        int GetX() const;
        int GetY() const;
        std::pair<int, int> GetSize();
        std::pair<int, int> GetPosition();
        static Panel FullScreen();
        void Add(Mead::IComponent &component);

        friend class Mead::Terminal;
    protected:
        std::vector<IComponent*>& GetComponents();
        void SetParent(Mead::Panel *parent) override;
        void Display(std::string& buffer, std::size_t id) override;
        void ResetPosition() override;
    private:
        class Impl;
        std::unique_ptr<Impl> mImpl;
    };

}

#endif
