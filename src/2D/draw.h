#ifndef DRAW_H
#define DRAW_H 1

#include <stddef.h>
#include <raylib.h>
#include "math.h"

void draw_shape(mat3x3 *m, vec2 *verts, size_t vert_count, int *indices, size_t ind_count) {
    for (int i = 0; i < ind_count; i+=2) {
        int k0 = indices[i];
        int k1 = indices[i+1];

        vec2 first = mat3x3_mul_vec2(*m, verts[k0]);
        vec2 next = mat3x3_mul_vec2(*m, verts[k1]);

        first = screen_to_world_space(first);
        next =  screen_to_world_space(next);

        DrawLine(first.x, first.y, next.x, next.y, GREEN);        
    }
}

#endif // DRAW_H
