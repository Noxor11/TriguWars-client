#include "object.hpp"
#include "draw.hpp"
#include "virtual_screen.hpp"

#include <cmath>
#include <box2d/box2d.h>

using namespace graphics;

//void rotate_vector(b2Vec2* vec, int vertices_count, const b2Vec2& center, float angle) {
//    // https://en.wikipedia.org/wiki/Rotation_matrix
//    // https://danceswithcode.net/engineeringnotes/rotations_in_2d/rotations_in_2d.html
//
//    for (int i = 0; i < vertices_count; i++){
//        vec[i] = {
//            (vec[i].x - center.x) * std::cos(angle) + (vec[i].y - center.y) * std::sin(angle) + center.x,
//            (vec[i].x - center.x) * -std::sin(angle) + (vec[i].y - center.y) * std::cos(angle) + center.y
//        };
//    }
//
//};
//
//Object::Object(b2Body* body, std::function<void(const b2Vec2*)> drawing_function) :
//    body{body}, drawing_function{drawing_function} {
//
//        calculate_vertices();
//        // memcpy(this->vertices, vertices, sizeof(b2Vec2) * vertices_count);
//}
//
//Object::~Object(){
//    // delete[] vertices;
//}
//
//void Object::calculate_vertices(){
//    for (b2Fixture* fix = body->GetFixtureList(); fix; fix->GetNext()){
//        if (fix->GetType() == b2Shape::e_polygon){
//            auto shape = (b2PolygonShape*)fix->GetShape();
//
//
//            this->vertices = shape->m_vertices;
//            this->vertices_count = shape->m_count;
//            break;
//        }
//    }
//}
//
//
//void Object::draw(){
//    const auto& pos = body->GetTransform();
//
//    b2Vec2 vec[vertices_count];
//
//    for (int i = 0; i < vertices_count; i++){
//        vec[i] = b2Mul(pos, vertices[i]);
//    }
//
//    drawing_function(vec);
//}

Object::~Object() {

}
