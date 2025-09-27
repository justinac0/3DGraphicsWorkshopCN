# !/bin/zsh
# Homebrew method
mkdir -p bin/

RAYLIB_FLAGS=$(pkg-config --libs --cflags raylib)

comp() {
  clang $@ $RAYLIB_FLAGS -lm
}

comp src/2D/scratch.c src/2D/main.c -o bin/2D
comp src/3D/scratch.c src/3D/main.c -o bin/3D
comp src/model_loading/*.c -o bin/obj

