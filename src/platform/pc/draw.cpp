#include "draw.hpp"
#include <SDL2/SDL.h>
#include <iostream>
#include "dimensions.hpp"
#include "text.hpp"

SDL_Renderer* renderer;
SDL_Window* window = NULL;

void graphics::init() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cout << "[CRITICAL] SDL_Init Error: " << SDL_GetError() << std::endl;
        exit(1);
    }

    window = SDL_CreateWindow("TriguWars [PC]", NULL, NULL, SCREEN_WIDTH, SCREEN_HEIGHT, NULL);
    if (window == NULL) {
        std::cout << "[CRITICAL] SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        exit(1);
    }

    renderer = SDL_CreateRenderer(window, -1, NULL);
    if (renderer == NULL) {
        std::cout << "[CRITICAL] SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        exit(1);
    }

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0xFF);
    SDL_RenderClear(renderer);

    graphics::text::init();

}

void graphics::close() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void graphics::start_frame() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0xFF);
    SDL_RenderClear(renderer);
}

void graphics::end_frame() {
    SDL_RenderPresent(renderer);
}

void graphics::draw_rectangle(int x, int y, int w, int h, const Color& color) {
   SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
   SDL_Rect r {x, y, w, h};
   SDL_RenderDrawRect(renderer, &r);
   SDL_RenderFillRect(renderer, &r);
}

void graphics::draw_line(int x1, int y1, int x2, int y2, const Color &color) {
   SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
   SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
}


void graphics::draw_triangle(int x1, int y1, int x2, int y2, int x3, int y3, const Color& color) {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_Vertex* vertices = (SDL_Vertex*)malloc(sizeof(SDL_Vertex) * 3);

    vertices[0] = {
        {(float)x1, (float)y1}, {(Uint8)color.r, (Uint8)color.g, (Uint8)color.b, (Uint8)color.a}, {1, 1}
    };
    vertices[1] = {
        {(float)x2, (float)y2}, {(Uint8)color.r, (Uint8)color.g, (Uint8)color.b, (Uint8)color.a}, {1, 1}
    };
    vertices[2] = {
        {(float)x3, (float)y3}, {(Uint8)color.r, (Uint8)color.g, (Uint8)color.b, (Uint8)color.a}, {1, 1}
    };

    SDL_RenderGeometry(renderer, NULL, vertices, 3, NULL, 0);
    free(vertices);
}

void graphics::draw_vertices(const Vector2 *vertices, int n_vertices, const Color& color, bool fill) {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    if (fill) {
        for (int i = 0; i < n_vertices - 2; i++) {
            // NOTE: Se puede OPTIMIZAR si se usa SDL_RenderGeometry directamente
            graphics::draw_triangle(
                vertices[0].x, vertices[0].y,
                vertices[i+1].x, vertices[i+1].y,
                vertices[i+2 % n_vertices].x,  vertices[i+2 % n_vertices].y,
                color);
        }
    } else {
        int i;
        for (i = 0; i < n_vertices - 1; ++i) {
            graphics::draw_line(vertices[i].x, vertices[i].y, vertices[i+1].x, vertices[i+1].y, color);
        }
        graphics::draw_line(vertices[i].x, vertices[i].y, vertices[0].x, vertices[0].y, color);
    }
};

SDL_Renderer* graphics::get_renderer() {
    return renderer;
}
