#include "scratch.h"

#include <assert.h>
#include <math.h>
#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mesh.h"
#include "math.h"

static mat4x4 view;
static mat4x4 perspective;
static mat4x4 MVP;

static mat4x4 model0;
static mesh geometry0;
static mat4x4 model1;
static mesh geometry1;

void setup(void) {
  geometry0 = load_wavefront("models/monkey.obj");
  geometry1 = load_wavefront("models/text.obj");

  model0 = mat4x4_identity();
  model1 = mat4x4_mul(mat4x4_translate((vec3){0, -10, -8}), mat4x4_rotate_x(-0.75));

  perspective = mat4x4_perspective(100, 0.001, 70, 1);
}

void update(void) {}

void draw(void) {
  mat4x4 translate = mat4x4_translate(vec3_set(0, 0, -1));
  model0 = mat4x4_mul(translate, mat4x4_rotate_y(GetTime()));

  mesh_draw(&geometry0, mat4x4_mul(perspective, model0));
  mesh_draw(&geometry1, mat4x4_mul(perspective, model1));
}

void cleanup(void) { mesh_free(&geometry0); }
