#include <stdio.h>
#include <SDL2/SDL.h>

//8, 16, 32 선택해서 값을 받아오는 함수
int GetData(void *p, Uint8 type) {
    Uint32 _rt = 0;

    switch (type) {
        case 'c':
            _rt = *((Uint8 *)p);
        case 's':
            _rt = *((Uint16 *)p);
            break;
        case 'i':
            _rt = *((Uint32 *)p);
            break;
        default:
            break;
    }

    return _rt;
}

int main(int argc, char *argv[]) {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        printf("error initializing SDL : %s \n", SDL_GetError());
        return 1;
    }

    int data = 0x12345678;
    printf("%x \n", GetData(&data, 'c'));
    printf("%x \n", GetData(&data, 's'));
    printf("%x \n", GetData(&data, 'i'));

    SDL_Quit();
    return 0;
}