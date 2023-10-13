#include "draw.hpp"
#include "virtual_screen.hpp"

class Trigu {
    public:
        float x;
        float y;
        float w;
        float h;
        Color color;
        void render(VirtualScreen vscreen);
};
