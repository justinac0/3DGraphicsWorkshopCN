#ifndef DRAW_H
#define DRAW_H 1

#include <stdio.h>
#include <raylib.h>
#include "math.h"

void draw_shape(mat4x4 mp, vec3 *verts, size_t vert_count, int *indices, size_t ind_count) {
    for (int i = 0; i < ind_count; i+=2) {
        int k0 = indices[i];
        int k1 = indices[i+1];

        vec4 vk0 = (vec4){verts[k0].x, verts[k0].y, verts[k0].z, 1};
        vec4 vk1 = (vec4){verts[k1].x, verts[k1].y, verts[k1].z, 1};

        vec4 first = mat4x4_mul_vec4(mp, vk0);
        vec4 next = mat4x4_mul_vec4(mp, vk1);

        vec3 f = screen_to_world_space((vec3){first.x, first.y, first.z});
        vec3 n =  screen_to_world_space((vec3){next.x, next.y, next.z});

        DrawLine(f.x, f.y, n.x, n.y, GREEN);
    }
}

// NOT COVERED IN WORKSHOP - uses code that defines clip space and viewport
void draw_draw(mat4x4 mp, vec3 *verts, size_t vert_count, int *indices, size_t ind_count) {
  for (int i = 0; i < ind_count; i+=2) {
    int k0 = indices[i];
    int k1 = indices[i+1];

    vec4 hv0 = { verts[k0].x, verts[k0].y, verts[k0].z, 1.0 };
    vec4 hv1 = { verts[k1].x, verts[k1].y, verts[k1].z, 1.0 };

    viewport vp = { .x = 0, .y = 0, .width = GetScreenWidth(), .height = GetScreenHeight() };

    vec4 clip0 = mat4x4_mul_vec4(mp, hv0);
    vec4 clip1 = mat4x4_mul_vec4(mp, hv1);

    if (!clip_line(&clip0, &clip1)) continue;

    clip0.x /= clip0.w; clip0.y /= clip0.w; clip0.z /= clip0.w;
    clip1.x /= clip1.w; clip1.y /= clip1.w; clip1.z /= clip1.w;

    vec3 first = ndc_to_screen((vec3){clip0.x, clip0.y, clip0.z}, vp);
    vec3 next  = ndc_to_screen((vec3){clip1.x, clip1.y, clip1.z}, vp);

    DrawLine(first.x, first.y, next.x, next.y, GREEN);
  }
}

#endif // DRAW_H
