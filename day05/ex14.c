#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

int main(int argc, char *argv[])
{
    if (SDL_Init(SDL_INIT_VIDEO) == 0)
    {
        SDL_Window *window = NULL;
        SDL_Renderer *renderer = NULL;

        if (SDL_CreateWindowAndRenderer(640, 480, 0, &window, &renderer) == 0)
        {

            // creates a surface to load an image into the main memory
            SDL_Surface *surface;

            // please provide a path for your image
            surface = IMG_Load("../res/basictiles.png");

            // loads image to our graphics hardware memory.
            SDL_Texture *tex = SDL_CreateTextureFromSurface(renderer, surface);

            // clears main-memory
            SDL_FreeSurface(surface);

            SDL_bool done = SDL_FALSE;

            while (!done)
            {
                SDL_Event event;

                SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
                SDL_RenderClear(renderer);

            /*
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);

                SDL_RenderDrawLine(renderer, 320, 200, 300, 240);
                SDL_RenderDrawLine(renderer, 300, 240, 340, 240);
                SDL_RenderDrawLine(renderer, 340, 240, 320, 200);

                SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
                SDL_RenderDrawLine(renderer, 320, 0, 320, 480);

                SDL_SetRenderDrawColor(renderer, 0, 255, 0, SDL_ALPHA_OPAQUE);
                SDL_RenderDrawLine(renderer, 0, 240, 640, 240);
            */
        
           SDL_Rect _srcRt;
           SDL_Rect _dstRt;

           // 바닥 잔디 깔기
           for (int i = 0; i < 20; i++) {
               for (int j = 0; j < 15; j++) {
                    _srcRt.x = 0;
                    _srcRt.y = 16 * 8;
                    _srcRt.w = 16;
                    _srcRt.h = 16;

                    _dstRt.x = 16 * i * 2;
                    _dstRt.y = 16 * j * 2;
                    _dstRt.w = 16 * 2;
                    _dstRt.h = 16 * 2;

                    SDL_RenderCopy(renderer, tex, &_srcRt, &_dstRt);
               }
           }

           int ran_I = rand() %20;
           int ran_J = rand() %15;

           _srcRt.x = 16 * 3;
           _srcRt.y = 16 * 7;
           _srcRt.w = 16;
           _srcRt.h = 16;

           _dstRt.x = 16 * ran_I * 2;
           _dstRt.y = 16 * ran_J * 2;
           _dstRt.w = 16 * 2;
           _dstRt.h = 16 * 2;

           SDL_RenderCopy(renderer, tex, &_srcRt, &_dstRt);

           SDL_Delay(1000 / 2);

                //Draw(1, 1, renderer, tex);

                /*
                {
                    SDL_Rect _srcRt;
                    _srcRt.x = 0;
                    _srcRt.y = 0;
                    _srcRt.w = 16;
                    _srcRt.h = 16;

                    SDL_Rect _dstRt;
                    _dstRt.x = 0;
                    _dstRt.y = 0;
                    _dstRt.w = 16 * 4;
                    _dstRt.h = 16 * 4;

                    SDL_RenderCopy(renderer, tex, &_srcRt, &_dstRt);
                }
                */

                SDL_RenderPresent(renderer);

                while (SDL_PollEvent(&event))
                {
                    if (event.type == SDL_QUIT)
                    {
                        done = SDL_TRUE;
                    }
                }
            }

            // destroy texture
            SDL_DestroyTexture(tex);
        }

        if (renderer)
        {

            SDL_DestroyRenderer(renderer);
        }
        if (window)
        {
            SDL_DestroyWindow(window);
        }
    }
    SDL_Quit();
    return 0;
}

/*
void DrawF(int x, int y, ren, tex) {
    SDL_Rect _srcRt;
    _srcRt.x = 16 * x - 16;
    _srcRt.y = 16 * y - 16;
    _srcRt.w = 16;
    _srcRt.h = 16;

    SDL_Rect _dstRt;
    _dstRt.x = 16 * x * 4 - 16;
    _dstRt.y = 16 * x * 4 - 16;
    _dstRt.w = 16 * 4;
    _dstRt.h = 16 * 4;

    SDL_RenderCopy(ren, tex, &_srcRt, &_dstRt);
}
*/