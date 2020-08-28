#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>

#include <stdio.h>

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480
int main(int argc, char *argv[])
{
    // retutns zero on success else non-zero
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        printf("error initializing SDL: %s\n", SDL_GetError());
    }
    SDL_Window *win = SDL_CreateWindow("GAME", // creates a window
                                       SDL_WINDOWPOS_CENTERED,
                                       SDL_WINDOWPOS_CENTERED,
                                       WINDOW_WIDTH, WINDOW_HEIGHT, 0);

    // triggers the program that controls
    // your graphics hardware and sets flags
    Uint32 render_flags = SDL_RENDERER_ACCELERATED;

    // creates a renderer to render our images
    SDL_Renderer *rend = SDL_CreateRenderer(win, -1, render_flags);

    // creates a surface to load an image into the main memory
    SDL_Surface *surface;

    // please provide a path for your image
    surface = IMG_Load("../res/dungeontiles.png");

    // loads image to our graphics hardware memory.
    SDL_Texture *tex = SDL_CreateTextureFromSurface(rend, surface);

    // clears main-memory
    SDL_FreeSurface(surface);

    // let us control our image position
    // so that we can move it with our keyboard.
    SDL_Rect dest;

    // 이미지 원본 크기 구하기
    SDL_QueryTexture(tex, NULL, NULL, &dest.w, &dest.h);

    printf("orignal size %d,%d \n", dest.w, dest.h);

    // 두배로 늘리기
    dest.w *= 2;
    dest.h *= 2;
    dest.x = 0;
    dest.y = 0;

    // controls annimation loop
    int close = 0;
    // annimation loop
    while (!close)
    {
        SDL_Event event;

        // Events mangement
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                // handling of close button
                printf("now quit app \n");
                close = 1;
                break;
            case SDL_KEYDOWN:
                printf("key down %d \n", event.key.keysym.scancode);

                //esc 키 누름
                if (event.key.keysym.scancode == 41)
                {
                    close = 1;
                }
                break;
            }
        }
        // clears the screen
        SDL_RenderClear(rend);

        //원본 이미지
        SDL_RenderCopy(rend, tex, NULL, &dest);

        //0,0 첫번째 타일
        {
            SDL_Rect _tmpDstRt;
            _tmpDstRt.x = 250;
            _tmpDstRt.y = 0;
            _tmpDstRt.w = 48;
            _tmpDstRt.h = 48;
            SDL_Rect _tmpSrcRt;
            _tmpSrcRt.x = 0;
            _tmpSrcRt.y = 0;
            _tmpSrcRt.w = 24;
            _tmpSrcRt.h = 24;

            SDL_RenderCopy(rend, tex, &_tmpSrcRt, &_tmpDstRt);
        }

        //1,0 타일 출력
        {
            SDL_Rect _tmpDstRt;
            _tmpDstRt.x = 250;
            _tmpDstRt.y = 48;
            _tmpDstRt.w = 48;
            _tmpDstRt.h = 48;
            SDL_Rect _tmpSrcRt;
            _tmpSrcRt.x = 24;
            _tmpSrcRt.y = 0;
            _tmpSrcRt.w = 24;
            _tmpSrcRt.h = 24;

            SDL_RenderCopy(rend, tex, &_tmpSrcRt, &_tmpDstRt);
        }
        //1,2 타일출력
        {
            SDL_Rect _tmpDstRt;
            _tmpDstRt.x = 250 + 48;
            _tmpDstRt.y = 48;
            _tmpDstRt.w = 48;
            _tmpDstRt.h = 48;
            SDL_Rect _tmpSrcRt;
            _tmpSrcRt.x = 24;
            _tmpSrcRt.y = 48;
            _tmpSrcRt.w = 24;
            _tmpSrcRt.h = 24;

            SDL_RenderCopy(rend, tex, &_tmpSrcRt, &_tmpDstRt);
        }

        // triggers the double buffers
        // for multiple rendering
        SDL_RenderPresent(rend);

        // calculates to 60 fps
        SDL_Delay(1000 / 60);
    }

    // destroy texture
    SDL_DestroyTexture(tex);

    // destroy renderer
    SDL_DestroyRenderer(rend);

    // destroy window
    SDL_DestroyWindow(win);
    return 0;
}