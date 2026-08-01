#ifndef MEAD_TERMINAL_H
#define MEAD_TERMINAL_H

#include <memory>
#include <utility>

namespace Mead 
{
    class Panel;

    class Terminal 
    {
    public:
        Terminal(const Terminal&) = delete;
        Terminal& operator=(const Terminal&) = delete;

        static Terminal& GetInstance();
        void AddPanel(Mead::Panel &panel);
        void Render(Mead::Panel &panel);
        void RenderAll();
        int GetTerminalWidth();
        int GetTerminalHeight();
        std::pair<int, int> GetTerminalSize();
        char GetKey(); //TEMPORARY
    private:
        Terminal();
        ~Terminal();
        class Impl;
        std::unique_ptr<Impl> mImpl;
    };
}

#endif
