#ifndef MATH_H
#define MATH_H

#include <math.h>

#define UNIT (100)

typedef struct vec2 {
    double x, y;
} vec2;

vec2 vec2_add(vec2 a, vec2 b) {
    return (vec2){
        .x = a.x + b.x,
        .y = a.y + b.y,
    };
}

vec2 vec2_scalar(vec2 a, double s) {
    return (vec2){
        .x = a.x * s,
        .y = a.y * s,
    };
}

vec2 screen_to_world_space(vec2 position) {
    vec2 screenOffset = (vec2){
        .x = (double)(GetScreenWidth()/2.0),
        .y = (double)(GetScreenHeight()/2.0),
    };

    return vec2_add(vec2_scalar(position, UNIT), screenOffset);
}

#endif // MATH_H
