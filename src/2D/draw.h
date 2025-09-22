#ifndef DRAW_H
#define DRAW_H 1

#include <stddef.h>
#include <raylib.h>
#include "math.h"

void draw_shape(mat3x3 *m, vec2 *verts, size_t vert_count, int *indices, size_t ind_count) {
    for (int i = 0; i < ind_count; i+=2) {
        int k0 = indices[i];
        int k1 = indices[i+1];

        vec3 vk0 = (vec3){verts[k0].x, verts[k0].y, 1};
        vec3 vk1 = (vec3){verts[k1].x, verts[k1].y, 1};

        vec3 first = mat3x3_mul_vec3(*m, vk0);
        vec3 next = mat3x3_mul_vec3(*m, vk1);

        vec2 f = screen_to_world_space((vec2){first.x, first.y});
        vec2 n =  screen_to_world_space((vec2){next.x, next.y});

        DrawLine(f.x, f.y, n.x, n.y, GREEN);        
    }
}

#endif // DRAW_H
