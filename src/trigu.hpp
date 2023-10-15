#include "draw.hpp"
#include "virtual_screen.hpp"

class Trigu {
    public:
        float x;
        float y;
        float w;
        float h;
        // rotation of trigu in radians
        float rotation;
        graphics::Color color;
        void render(VirtualScreen &vscreen);
        Trigu(float x, float y, float w, float h, float rotation, const graphics::Color &color);
};
