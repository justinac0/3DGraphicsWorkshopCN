# !/bin/bash
mkdir -p bin/
gcc src/2D/scratch.c src/2D/main.c -o bin/2D  -lraylib -lm
gcc src/3D/scratch.c src/3D/main.c -o bin/3D -lraylib -lm
gcc src/model_loading/*.c -o bin/obj -lraylib -lm
