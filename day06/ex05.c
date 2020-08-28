#include <SDL2/SDL.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        printf("error initializing SDL : %s \n", SDL_GetError());
        return 1;
    }
    else {
        printf("success SDL INIT\n");
    }

    for (int j = 1; j<=9; j++) {
        for (int i=1; i<=9; i++) {
            printf("[%4d *%4d =%4d] \r", j, i, j*i);
            SDL_Delay(200);
        }
    }

    return 0;
}