#include "draw.hpp"
#include "game.hpp"
#include "text.hpp"
#include "input.hpp"
#include "virtual_screen.hpp"
#include "trigu.hpp"
#include "title_screen.hpp"
#include "object.hpp"
#ifdef __3DS__
#include <3ds.h>
#endif

#include <box2d/box2d.h>
#include <cmath>
#include <iostream>
#include <string>

using namespace graphics;

int main() {
    graphics::init();
    graphics::text::set_font("CubicCoreMono");
    input::init();

    /*
    VirtualScreen screen = VirtualScreen(0, 0, 100, 100, 1.0);
    TitleScreen title_screen;
    // Trigu trigito = Trigu(80, 80, 30, 30, 1/8 * 3.14, Color{0, 255, 255, 255});

    float i = 0;
    float x = 0.0;


    b2Vec2 gravity(0.0f, -10.0f);
    b2World* world = new b2World(gravity);
    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(0.0f, -10.0f);
    b2Body* groundBody = world->CreateBody(&groundBodyDef);
    b2PolygonShape groundObject;

    b2Vec2 vertices[4];
    vertices[0] = b2Vec2{30,10};
    vertices[1] = b2Vec2{200, 10};
    vertices[2] = b2Vec2{30,40};
    vertices[3] = b2Vec2{200,40};

    groundObject.Set(vertices, 4);
    groundBody->CreateFixture(&groundObject, 0.0f);
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(0.0f, 100.0f);
    b2Body* body = world->CreateBody(&bodyDef);

    b2PolygonShape dynamicBox;
    vertices[0] = b2Vec2{30,10};
    vertices[1] = b2Vec2{90, 10};
    vertices[2] = b2Vec2{100,70};
    dynamicBox.Set(vertices, 3);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.3f;
    body->CreateFixture(&fixtureDef);
    float timeStep = 1.0f;
    int32 velocityIterations = 6;
    int32 positionIterations = 2;


    //auto ground = Object(groundBody, [](const b2Vec2* vec) {
    //    graphics::draw_line(vec[0].x, vec[0].y,
    //                        vec[1].x, vec[1].y, {120, 24, 20, 255});
    //
    //    graphics::draw_line(vec[1].x, vec[1].y,
    //                        vec[2].x, vec[2].y, {120, 24, 20, 255});
    //
    //    graphics::draw_line(vec[2].x, vec[2].y,
    //                        vec[3].x, vec[3].y, {120, 24, 20, 255});
    //
    //    graphics::draw_line(vec[3].x, vec[3].y,
    //                        vec[0].x, vec[0].y, {120, 24, 20, 255});

    //});

    //auto box = Object(body, [](const b2Vec2* vec){
    //    graphics::draw_triangle(vec[0].x, vec[0].y, vec[1].x, vec[1].y, vec[2].x, vec[2].y, Color{255,0, 0, 255});
    //});
    */

    Game game(b2Vec2(0.0f, 0.0f), 4, 2);


#ifdef __3DS__
    while (aptMainLoop()) {
#else
    while (true) {
#endif

        graphics::start_frame();

        input::scan();

        game.update(0.16f);

        graphics::end_frame();
        /*
        i += 3.14 / 60;
        if (input::is_key_down(input::BUTTON_DPAD_RIGHT)) {
            x += 2;
        }

        title_screen.update();

        // graphics::draw_triangle(vertices[0].x, vertices[0].y, vertices[1].x, vertices[1].y, vertices[2].x, vertices[3].y, Color{255,0, 0, 255});

        // trigito.move_x_by(input::joystick1.x / 32);
        // trigito.move_y_by(input::joystick1.y / 32);


        // trigito.rotate_by(0.1);

        // trigito.render(screen);

        if (input::get_touch()) {
            // graphics::draw_rectangle(input::touch.x, input::touch.y, 40, 40, {225, 192, 203, 255});
            body->SetTransform({(float)input::touch.x, (float)input::touch.y}, body->GetAngle());
            body->SetAwake(true);
            // box.calculate_vertices();
        }
*/


/*

        // update world
        world->Step(timeStep, velocityIterations, positionIterations);
        b2Vec2 position = body->GetPosition();
        //ground.draw();
        //box.draw();


        std::cout << position.y << "\n";
        //  ("%4.2f %4.2f %4.2f\n", position.x, position.y, angle);
        

        graphics::end_frame();
        */
    }

    graphics::close();
    return 0;
}
