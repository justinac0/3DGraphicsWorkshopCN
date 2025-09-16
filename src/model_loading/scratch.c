#include "scratch.h"

#include <assert.h>
#include <math.h>
#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define UNIT (250)

typedef struct vec3 {
  double x, y, z;
} vec3;

vec3 vec3_add(vec3 a, vec3 b) {
  return (vec3){
      .x = a.x + b.x,
      .y = a.y + b.y,
      .z = a.z + b.z,
  };
}

vec3 vec3_scalar(vec3 a, double s) {
  return (vec3){
      .x = a.x * s,
      .y = a.y * s,
      .z = a.z * s,
  };
}

vec3 screen_to_world_space(vec3 position) {
  vec3 screenOffset = (vec3){
      .x = (double)(GetScreenWidth() / 2.0),
      .y = (double)(GetScreenHeight() / 2.0),
  };

  return vec3_add(vec3_scalar(position, UNIT), screenOffset);
}

typedef struct vec4 {
  double x, y, z, w;
} vec4;

typedef union mat4x4 {
  vec4 v[4];
  double mm[4][4];
  struct {
    double m00, m01, m02, m03;
    double m10, m11, m12, m13;
    double m20, m21, m22, m23;
    double m30, m31, m32, m33;
  };
} mat4x4;

mat4x4 mat4x4_fill(double v) {
  mat4x4 result = {
      (vec4){v, v, v, v},
      (vec4){v, v, v, v},
      (vec4){v, v, v, v},
      (vec4){v, v, v, v},
  };
  return result;
}

mat4x4 mat4x4_identity(void) {
  mat4x4 result = {
      (vec4){1, 0, 0, 0},
      (vec4){0, 1, 0, 0},
      (vec4){0, 0, 1, 0},
      (vec4){0, 0, 0, 1},
  };
  return result;
}

mat4x4 mat4x4_mul(mat4x4 a, mat4x4 b) {
  mat4x4 result = mat4x4_fill(0);

  for (int row = 0; row < 4; row++) {
    for (int col = 0; col < 4; col++) {
      double sum = 0;
      for (int q = 0; q < 4; q++) {
        sum += a.mm[col][q] * b.mm[q][row];
      }
      result.mm[row][col] = sum;
    }
  }

  return result;
}

mat4x4 mat4x4_translate(vec3 offset) {
  mat4x4 m = {
      (vec4){1, 0, 0, offset.x},
      (vec4){0, 1, 0, offset.y},
      (vec4){0, 0, 1, offset.z},
      (vec4){0, 0, 0, 1},
  };

  return m;
}

mat4x4 mat4x4_rotate_x(double theta) {
  mat4x4 m = {
      (vec4){1, 0, 0, 0},
      (vec4){0, cosf(theta), -sinf(theta), 0},
      (vec4){0, sinf(theta), cosf(theta), 0},
      (vec4){0, 0, 0, 1},
  };

  return m;
}

mat4x4 mat4x4_rotate_y(float theta) {
  mat4x4 m = {
      (vec4){cosf(theta), 0, sinf(theta), 0},
      (vec4){0, 1, 0, 0},
      (vec4){-sinf(theta), 0, cosf(theta), 0},
      (vec4){0, 0, 0, 1},
  };

  return m;
}

mat4x4 mat4x4_rotate_z(float theta) {
  mat4x4 m = {
      (vec4){cosf(theta), -sinf(theta), 0, 0},
      (vec4){sinf(theta), cosf(theta), 0, 0},
      (vec4){0, 0, 1, 0},
      (vec4){0, 0, 0, 1},
  };

  return m;
}

vec3 mat4x4_mul_vec3(mat4x4 a, vec3 v) {
  vec3 result = {0, 0, 0};

  result.x = (a.m00 * v.x) + (a.m10 * v.y) + (a.m20 * v.z) + (a.m30);
  result.y = (a.m01 * v.x) + (a.m11 * v.y) + (a.m21 * v.z) + (a.m31);
  result.z = (a.m02 * v.x) + (a.m12 * v.y) + (a.m22 * v.z) + (a.m32);
  double w = (a.m03 * v.x) + (a.m13 * v.y) + (a.m23 * v.z) + (a.m33);

  if (w != 0) {
    result.x /= w;
    result.y /= w;
    result.z /= w;
  }

  return result;
}

typedef struct vec2i {
  int x;
  int y;
} vec2i;

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

  m.verts = calloc(m.verts_cap, sizeof(vec3));
  assert(m.verts);

  m.lines = calloc(m.lines_cap, sizeof(vec2i));
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
    m->verts = realloc(m->verts, m->verts_cap * 1.4);
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
    m->lines = realloc(m->lines, m->lines_cap * 1.4);
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

    vec3 first = mat4x4_mul_vec3(*mp, m->verts[k0]);
    vec3 next = mat4x4_mul_vec3(*mp, m->verts[k1]);

    first = screen_to_world_space(first);
    next = screen_to_world_space(next);

    DrawLine(first.x, first.y, next.x, next.y, RED);
  }
}

mesh load_wavefront(const char *filepath) {
  FILE *file = fopen(filepath, "r");
  if (!file) {
    perror("failed to load file");
  }

  mesh m = mesh_init(1024, 3 * 1024);

  char line[1024];
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

// Nesh
static mesh geometry;
// Matricies
static mat4x4 model;
static mat4x4 perspective;
static mat4x4 MP;

void setup(void) {
  geometry = load_wavefront("models/isosphere.obj");

  model = (mat4x4){
      (vec4){1, 0, 0, 0},
      (vec4){0, 1, 0, 0},
      (vec4){0, 0, 1, 0},
      (vec4){0, 0, 0, 1},
  };

  perspective = (mat4x4){
      (vec4){1, 0, 0, 0},
      (vec4){0, 1, 0, 0},
      (vec4){0, 0, 1, 1},
      (vec4){0, 0, 1, 0},
  };
}

void update(void) {
  mat4x4 translate = mat4x4_translate((vec3){sinf(GetTime()),cosf(GetTime()),-5});
  mat4x4 rotate = mat4x4_rotate_z(GetTime());
  mat4x4 scale = mat4x4_identity();
  model = mat4x4_mul(translate, rotate);
  model = mat4x4_mul(model, scale);
  MP = mat4x4_mul(perspective, model);
}

void draw(void) { mesh_draw(&geometry, &MP); }

void cleanup(void) { mesh_free(&geometry); }
