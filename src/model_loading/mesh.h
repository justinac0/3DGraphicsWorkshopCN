#ifndef MESH_H
#define MESH_H 1

#include <raylib.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>

#include "math.h"

#define DEFAULT_VERT_CAP (1000000)

typedef struct mesh {
  size_t lines_len;
  size_t lines_cap;
  size_t verts_len;
  size_t verts_cap;
  vec3 *verts;
  vec2i *lines;
} mesh;

mesh mesh_init(size_t verts_cap, size_t lines_cap) {
  mesh m;
  m.verts_cap = verts_cap;
  m.lines_cap = lines_cap;
  m.verts_len = m.lines_len = 0;

  m.verts = (vec3*)calloc(m.verts_cap, sizeof(vec3));
  assert(m.verts);

  m.lines = (vec2i*)calloc(m.lines_cap, sizeof(vec2i));
  assert(m.lines);

  return m;
}

void mesh_free(mesh *m) {
  assert(m);

  free(m->verts);
  free(m->lines);
}

void mesh_add_vert(mesh *m, vec3 v) {
  assert(m);

  if (m->verts_len + 1 > m->verts_cap) {
    m->verts = (vec3*)realloc(m->verts, m->verts_cap * 1.4);
    assert(m->verts);
  }

  m->verts[m->verts_len].x = v.x;
  m->verts[m->verts_len].y = v.y;
  m->verts[m->verts_len].z = v.z;
  m->verts_len++;
}

void mesh_add_line(mesh *m, vec2i v) {
  assert(m);

  if (m->lines_len + 1 > m->lines_cap) {
    m->lines = (vec2i*)realloc(m->lines, m->lines_cap * 1.4);
    assert(m->verts);
  }

  m->lines[m->lines_len].x = v.x;
  m->lines[m->lines_len].y = v.y;
  m->lines_len++;
}

void mesh_draw(mesh *m, mat4x4 *mp) {
  for (int i = 0; i < m->lines_len; i++) {
    int k0 = m->lines[i].x;
    int k1 = m->lines[i].y;

    vec4 hv0 = { m->verts[k0].x, m->verts[k0].y, m->verts[k0].z, 1.0 };
    vec4 hv1 = { m->verts[k1].x, m->verts[k1].y, m->verts[k1].z, 1.0 };

    viewport vp = { .x = 0, .y = 0, .width = GetScreenWidth(), .height = GetScreenHeight() };

    vec4 clip0 = mat4x4_mul_vec4(*mp, hv0);
    vec4 clip1 = mat4x4_mul_vec4(*mp, hv1);

    if (!clip_line(&clip0, &clip1)) continue;

    clip0.x /= clip0.w; clip0.y /= clip0.w; clip0.z /= clip0.w;
    clip1.x /= clip1.w; clip1.y /= clip1.w; clip1.z /= clip1.w;

    vec3 first = ndc_to_screen((vec3){clip0.x, clip0.y, clip0.z}, vp);
    vec3 next  = ndc_to_screen((vec3){clip1.x, clip1.y, clip1.z}, vp);

    DrawLine(first.x, first.y, next.x, next.y, RED);
  }
}

mesh load_wavefront(const char *filepath) {
  FILE *file = fopen(filepath, "r");
  if (!file) {
    perror("failed to load file");
  }

  mesh m = mesh_init(DEFAULT_VERT_CAP, 3 * DEFAULT_VERT_CAP);

  char line[2048];
  //.read through wavefront obj file and parse contents
  while (fgets(line, sizeof(line), file)) {
    // add verticies
    if (strncmp(line, "v ", 2) == 0) {
      float x, y, z;
      int status = sscanf(line + 2, "%f %f %f\n", &x, &y, &z);
      assert(status == 3);
      mesh_add_vert(&m, (vec3){x, y, z});
    }
    // add lines
    // f v1/vt1 v2/vt2 v3/vt3 ...
    if (strncmp(line, "f ", 2) == 0) {
      int p0, p1, p2, p3, p4, p5;
      int status =
          sscanf(line + 2, "%d/%d %d/%d %d/%d\n", &p0, &p1, &p2, &p3, &p4, &p5);
      assert(status == 6);

      mesh_add_line(&m, (vec2i){p0 - 1, p2 - 1});
      mesh_add_line(&m, (vec2i){p2 - 1, p4 - 1});
    }
  }

  fclose(file);

  return m;
}

#endif // MESH_H
