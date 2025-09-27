#include "scratch.h"
#include "math.h"
#include "draw.h"

vec3 cube[8] = {
    (vec3){ 1, -1,  1},
    (vec3){ 1,  1,  1},
    (vec3){ 1, -1, -1},
    (vec3){ 1,  1, -1},
    (vec3){-1, -1,  1},
    (vec3){-1,  1,  1},
    (vec3){-1, -1, -1},
    (vec3){-1,  1, -1},
};

int indices[24] = {
    0, 1,
    0, 2,
    1, 3,
    2, 3,
    
    4, 5,
    5, 7,
    6, 7,
    4, 6,
    
    0, 4,
    1, 5,
    2, 6,
    3, 7,
};

void setup(void) {
}

void update(void) {
}

void draw(void) {
    DrawText("NOT IMPLEMENTED", 0, 0, 24, WHITE);
}

