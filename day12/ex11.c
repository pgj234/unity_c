#include <stdio.h>
#include <SDL2/SDL.h>

int main(int argc, char *argv[]) {
    SDL_Rect rect;
    rect.x = 10;
    rect.y = 20;
    rect.w = 100;
    rect.h = 150;

    SDL_RWops *rw = SDL_RWFromFile("test2.bin", "wb");
    SDL_RWwrite(rw, &rect, sizeof(SDL_Rect), 1);

    SDL_RWclose(rw);

    return 0;
}