#pragma once
#include "virtual_screen.hpp"
class Screen {
    protected: VirtualScreen vscreen;

    public:
        virtual void update() {};
        Screen(const VirtualScreen &vscreen): vscreen{vscreen} {};
};
