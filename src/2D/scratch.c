#include "scratch.h"

#include "draw.h"
#include "math.h"

static vec2 verts[4] = {
    {-1,  1},
    { 1,  1},
    { 1, -1},
    {-1, -1},
};

static int indices[8] = {
    0, 1,
    1, 2,
    2, 3,
    3, 0
};

mat3x3 model;

void setup(void) {
    model = mat3x3_identity();
}

void update(void) {

}

void draw(void) {
    draw_shape(&model, verts, 4, indices, 8);
}
