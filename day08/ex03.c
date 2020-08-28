#include <stdio.h>
#include <SDL2/SDL.h>

Uint16 map_layer1[8][8] = {
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 1, 2, 0, 0, 0, 0},
    {0, 0, 1, 2, 0, 0, 0, 0},
    {0, 0, 3, 0, 0, 0, 0, 0},
    {0, 0, 3, 0, 0, 0, 0, 0},
    {0, 2, 1, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0}
};

const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;

SDL_Window *gWindow;
SDL_Renderer *gRenderer;

void _drawDot(int x, int y, Uint8 _r, Uint8 _g, Uint8 _b)
{
    SDL_Rect _dotInfo;
    _dotInfo.x = x * 16;
    _dotInfo.y = y * 16;
    _dotInfo.w = 16;
    _dotInfo.h = 16;

    SDL_SetRenderDrawColor(gRenderer, _r, _g, _b, SDL_ALPHA_OPAQUE);
    SDL_RenderFillRect(gRenderer, &_dotInfo);
}

int main(int argc, char *argv[]) {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        printf("error initializing SDL : %s \n", SDL_GetError());
        return 1;
    }

    gWindow = SDL_CreateWindow("Game",
                                SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED,
                                WINDOW_WIDTH, WINDOW_HEIGHT, 0);

    Uint32 render_flags = SDL_RENDERER_ACCELERATED;

    gRenderer = SDL_CreateRenderer(gWindow, -1, render_flags);

    //게임루프
    SDL_bool bLoop = SDL_TRUE;
    while (bLoop) {
        //입력처리
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    bLoop = SDL_FALSE;
                    break;
                default:
                    break;
            }
        }

        // 출력(렌더링)
        SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(gRenderer);

        for (int iy = 0; iy < 8; iy++) {
            for (int ix = 0; ix < 8; ix++) {
                Uint16 _dot = map_layer1[iy][ix];
                int _x, _y;
                _x = ix + 5;
                _y = iy + 5;

                switch (_dot) {
                    case 0:
                        _drawDot(_x, _y, 255, 255, 255);
                        break;
                    case 1:
                        _drawDot(_x, _y, 255, 0, 0);
                        break;
                    case 2:
                        _drawDot(_x, _y, 0, 255, 0);
                        break;
                    case 3:
                        _drawDot(_x, _y, 0, 0, 255);
                        break;
                    default :
                        _drawDot(_x, _y, 0, 0, 0);
                        break;
                }
            }
        }

        //_drawDot(5, 5, 255, 255, 255);
        //_drawDot(6, 5, 255, 0, 0);
        //_drawDot(7, 5, 0, 255, 0);
        //_drawDot(8, 5, 0, 0, 255);

        SDL_RenderPresent(gRenderer);
    }

    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    SDL_Quit();
    return 0;
}