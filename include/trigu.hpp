#pragma once

#include "object.hpp"
#include "draw.hpp"

#include <array>

class Trigu : protected Object {
    private:
        std::array<graphics::Vector2, 3> vertices;

        void update_params();
        void update_rotation();
    public:

        graphics::Color color;

        void render(const VirtualScreen &vscreen) ;
        void set_vector2(const graphics::Vector2& vector2);
        void set_rotation(float rotation);
        void rotate_by(float rotation);
        void set_x(float x);
        void set_y(float y);
        void move_x_by(float units);
        void move_y_by(float units);

        std::array<graphics::Vector2, 3>& calculate_vertices();

        Trigu(float x, float y, float w, float h, float rotation, const graphics::Color& color);
        
};
