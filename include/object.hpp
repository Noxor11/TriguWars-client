#pragma once

#include "draw.hpp"
#include "virtual_screen.hpp"


class Object {
    protected:
        graphics::Vector2 center;

        union {
            struct {
                float x;
                float y;
            };
            
            graphics::Vector2 vector2;
        };

        float w;
        float h;
        float rotation; // rotation of trigu in radians

    public:

        const graphics::Vector2& calculate_center();
        const graphics::Vector2& get_vector2() const;
        void set_vector2(const graphics::Vector2& vector2);
        float get_rotation() const;

        void set_rotation(float rotation);
        void move_x_by(float units);
        void move_y_by(float units);
        void set_x(float x);
        void set_y(float y);

        Object(float x, float y, float w, float h, float rotation);
};
