#include <stdio.h>
#include <string.h>
#include <SDL2/SDL.h>

int main(int argc, char *argv[]) {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        printf("error initializing SDL : %s \n", SDL_GetError());
        return 1;
    }

    char data[256] = "Happy BirthDay";

    printf("length : %d \n", strlen(data));
    printf("length : %d \n", sizeof(data) -1);

    char _buffer[256];
    strcpy(_buffer, data);
/*
    for (int i=0; i<strlen(data); i++) {
        _buffer[i] = data[i];
    }
    _buffer[strlen(data)] = 0;
*/
    printf("%s \n", _buffer);

    strcat(_buffer, " to you");

    printf("%s \n", _buffer);

    _buffer[5] = 0;
    printf("%s \n", _buffer);

    SDL_Quit();
    return 0;
}