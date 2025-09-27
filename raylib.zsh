# !/bin/zsh
# Setup steps for compile from source method
git clone "https://github.com/raysan5/raylib"
cd raylib/src
make PLATFORM=PLATFORM_DESKTOP
