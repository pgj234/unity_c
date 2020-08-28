#include <stdio.h>
#include <string.h>
#include <SDL2/SDL.h>

int main(int argc, char *argv[]) {
    //char pNames[5][32] = {0};
    char *pNames[5] = {0};
    int _index = 0;

    SDL_bool bLoop = SDL_TRUE;
    while(bLoop) {
        char _buf[32];
        gets(_buf);
        
        if (!strcmp(_buf, "#end")) {
            printf("end of input \n");
            bLoop = SDL_FALSE;
        }
        else {
            int _str_size = strlen(_buf);
            pNames[_index] = (char *)SDL_malloc(_str_size +1);
            strcpy(pNames[_index], _buf);
            _index++;
        }
    }

    for (int i=0; i<_index; i++) {
        printf("%s \n", pNames[i]);
    }

    for (int i=0; i<_index; i++) {
        SDL_free(pNames[i]);
    }

    return 0;
}