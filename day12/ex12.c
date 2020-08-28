#include <stdio.h>
#include <SDL2/SDL.h>

int main(int argc, char *argv[]) {
    SDL_Rect rect;

    SDL_RWops *rw = SDL_RWFromFile("test2.bin", "rb");
    SDL_RWread(rw, &rect, sizeof(SDL_Rect), 1);

    SDL_RWclose(rw);

    printf("x : %d, y : %d, w : %d, h : %d\n", rect.x, rect.y, rect.w, rect.h);

    return 0;
}