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

typedef struct {
    vec3 position;
    vec3 forward;
    vec3 right;
    vec3 up;
} camera;

static camera cam;

void camera_move_forward(camera *cam, double dist) {
    cam->position.x += cam->forward.x * dist;
    cam->position.y += cam->forward.y * dist;
    cam->position.z += cam->forward.z * dist;
}

void camera_move_right(camera *cam, double dist) {
    cam->position.x += cam->right.x * dist;
    cam->position.y += cam->right.y * dist;
    cam->position.z += cam->right.z * dist;
}

void camera_move_up(camera *cam, double dist) {
    cam->position.x += cam->up.x * dist;
    cam->position.y += cam->up.y * dist;
    cam->position.z += cam->up.z * dist;
}

void camera_yaw(camera *cam, double angle) {
    double c = cos(angle), s = sin(angle);
    vec3 f = cam->forward;
    cam->forward.x = f.x * c + f.z * s;
    cam->forward.z = -f.x * s + f.z * c;
    cam->forward = vec3_norm(cam->forward);

    // recompute right = forward × worldUp
    cam->right = vec3_norm(vec3_cross(cam->forward, (vec3){0,1,0}));
    cam->up    = vec3_cross(cam->right, cam->forward);
}

void camera_pitch(camera *cam, double angle) {
    double c = cos(angle), s = sin(angle);
    vec3 f = cam->forward, u = cam->up;

    cam->forward.x = f.x * c + u.x * s;
    cam->forward.y = f.y * c + u.y * s;
    cam->forward.z = f.z * c + u.z * s;
    cam->forward = vec3_norm(cam->forward);

    // recompute up
    cam->up = vec3_norm(vec3_cross(cam->right, cam->forward));
}

void setup(void) {
  cam.position = vec3_set(0, 0, 3);
  cam.forward  = vec3_set(0, 0, -1);
  cam.right    = vec3_set(1, 0, 0);
  cam.up       = vec3_set(0, 1, 0);

  geometry = load_wavefront("models/keytruck.obj");

  model = mat4x4_identity();
  view = mat4x4_identity();
  perspective = mat4x4_perspective(100, 0.01, 90, 4/3);
}

void camera_update(void) {
    double moveSpeed = 0.01f;
    double sensitivity = 0.001f;

    cam.position.x += -(IsKeyDown(KEY_D) - IsKeyDown(KEY_A)) * moveSpeed;
    cam.position.y += (IsKeyDown(KEY_W) - IsKeyDown(KEY_S)) * moveSpeed;
    cam.position.z += -(IsKeyDown(KEY_SPACE) - IsKeyDown(KEY_LEFT_SHIFT)) * moveSpeed;  

  view = mat4x4_lookat(
    cam.position,
    (vec3){ cam.position.x + cam.forward.x,
            cam.position.y + cam.forward.y,
            cam.position.z + cam.forward.z },
    cam.up
  );
}

void update(void) {
  camera_update();

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
