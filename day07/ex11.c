#include <stdio.h>
#include <SDL2/SDL.h>

int GetStrLeength(char data[]){
    int _count=0;
    while (data[_count] != 0) {
        //data[_count] = '*';
        _count++;
    }
    return _count;
}

int main(int argc, char *argv[]) {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        printf("error initializing SDL : %s \n", SDL_GetError());
        return 1;
    }

    char data[6] = {'h', 'a', 'p', 'p', 'y', 0};
    char data2[] = "birth day";

    printf("length : %d \n", GetStrLeength(data2));

    printf("%s %s \n", data, data2);

    SDL_Quit();
    return 0;
}