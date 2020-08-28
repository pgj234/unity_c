#include <stdio.h>
#include <SDL2/SDL.h>

int c = 8;
int main(int argc, char *argv[]) {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        printf("error initializing SDL : %s \n", SDL_GetError());
        return 1;
    }

    int b=3;
    {
        int  a = 1;
        int b = a+1;
        printf("%d \n", b);
    }
    
    {
        int  a = 3;
        int b = a+1;
        printf("%d \n", b);
        printf("%d \n", c);
    }

    printf("%d \n", b);

    printf("%d \n", c);

    SDL_Quit();
    return 0;
}