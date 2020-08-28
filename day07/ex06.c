#include <stdio.h>
#include <SDL2/SDL.h>

int counter() {
    static int counter = 0;     //static이 붙어서 대입이 아니고 초기화이다.  그리고 static은 디스어셈블링 했을 때 값이 안나온다. 숨기기
    return ++counter;
}

int main(int argc, char *argv[]) {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        printf("error initializing SDL : %s \n", SDL_GetError());
        return 1;
    }

    printf("%d \n", counter());
    printf("%d \n", counter());
    printf("%d \n", counter());

    SDL_Quit();
    return 0;
}