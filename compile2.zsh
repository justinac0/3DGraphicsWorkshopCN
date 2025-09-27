# !/bin/zsh
# Compile from source method
mkdir -p bin/

RL="raylib/src"

comp() {
  clang $@ -I$RL -L$RL -lraylib -lm -framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo
}

comp src/2D/scratch.c src/2D/main.c -o bin/2D
comp src/3D/scratch.c src/3D/main.c -o bin/3D
comp src/model_loading/*.c -o bin/obj
