#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <string.h>

SDL_Window *g_pWindow;
SDL_Renderer *g_pRenderer;

const Uint16 WINDOW_WIDTH = 640;
const Uint16 WINDOW_HEIGHT = 480;

SDL_bool g_bLoop = SDL_TRUE;

enum EM_INPUTSTATUS{
    INPUT_ENABLE = 0,
    INPUT_STOP
};

Uint16 g_uInputFsm = INPUT_STOP;

int main(int argc, char *argv[]) {
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_CreateWindow("GAME", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);

    while(g_bLoop) {
        static char strInputBuf[64] = {0,};

        SDL_Event _event;
        while (SDL_PollEvent(&_event)) {
            switch (_event.type) {
                case SDL_TEXTINPUT:
                {
                    strcat(strInputBuf, _event.text.text);
                    printf("%s \r", strInputBuf);
                }
                    break;
                case SDL_QUIT:
                {
                    g_bLoop = SDL_FALSE;
                }
                    break;
                case SDL_KEYDOWN:
                {
                    if (g_uInputFsm == INPUT_STOP) {
                        if (_event.key.keysym.sym == SDLK_RETURN) {
                            SDL_StartTextInput();
                            printf("input msg : \n");
                            g_uInputFsm = INPUT_ENABLE;
                        }
                    }
                    else if (g_uInputFsm == INPUT_ENABLE) {
                        if (_event.key.keysym.sym == SDLK_RETURN) {
                            SDL_StopTextInput();
                            g_uInputFsm = INPUT_STOP;
                            printf("input result : %s\n", strInputBuf);
                            strInputBuf[0] = 0x00;
                        }
                        else if (_event.key.keysym.sym == SDLK_BACKSPACE) {
                            //printf("back space\n");
                            strInputBuf[strlen(strInputBuf) -1] = 0x00;
                            printf("%s \r", strInputBuf);
                        }
                    }
                }
                    break;
                default:
                    break;
            }
        }
    }

    SDL_DestroyWindow(g_pWindow);

    return 0;
}
