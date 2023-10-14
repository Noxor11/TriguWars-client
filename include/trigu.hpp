#include "draw.hpp"
#include "virtual_screen.hpp"

class Trigu {
    public:
        float x;
        float y;
        float w;
        float h;
        float rotation; // rotation of trigu in radians
        graphics::Color color;
        void render(VirtualScreen &vscreen);
        Trigu(float x, float y, float w, float h, float rotation, const graphics::Color& color);
};
