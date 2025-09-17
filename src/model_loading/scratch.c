#include "scratch.h"

#include <assert.h>
#include <math.h>
#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mesh.h"
#include "math.h"

static mat4x4 model;
static mat4x4 view;
static mat4x4 perspective;
static mat4x4 MVP;

static mesh geometry;

void setup(void) {
  geometry = load_wavefront("models/keytruck.obj");

  model = mat4x4_identity();
  view = mat4x4_identity();
  perspective = mat4x4_perspective(100, 0.01, 90, 1);
}

void camera(void) {
  

  view = mat4x4_lookat(
    vec3_set(0, 0, 3),
    vec3_set(0, 0, 0),
    vec3_set(0, -1, 0)
  );
}

void update(void) {
  camera();

  // mat4x4 translate = mat4x4_translate(vec3_set(sinf(GetTime()), cosf(GetTime()), 0));
  // mat4x4 rotate = mat4x4_rotate_z(GetTime());
  // mat4x4 scale = mat4x4_scale(vec3_set(1, 1, 1));

  // model = mat4x4_mul(translate, scale);
  // model = mat4x4_mul(model, rotate);
  
  MVP = mat4x4_mul(perspective, view);
  MVP = mat4x4_mul(MVP, model);
}

void draw(void) { mesh_draw(&geometry, &MVP); }

void cleanup(void) { mesh_free(&geometry); }
