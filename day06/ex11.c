#include <stdio.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>

int main(int argc, char *argv[]) {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        printf("error initializing SDL : %s \n", SDL_GetError());
        return 1;
    }
    else {
        printf("success SDL INIT\n");
    }

    SDL_Window *gWindow = SDL_CreateWindow("Gam",
                                            SDL_WINDOWPOS_CENTERED,
                                            SDL_WINDOWPOS_CENTERED,
                                            640, 480, 0);

    Uint32 render_flags = SDL_RENDERER_ACCELERATED;

    SDL_Renderer *gRenderer = SDL_CreateRenderer(gWindow, -1, render_flags);

    SDL_Surface *surface;

    surface = IMG_Load("../res/basictiles.png");

    if (!surface) {
        printf("error msg %s \n", IMG_GetError());
        return 1;
    }

    SDL_Texture  *tex = SDL_CreateTextureFromSurface(gRenderer, surface);

    SDL_FreeSurface(surface);

    SDL_bool bLoop = SDL_TRUE;

    while (bLoop) {
        SDL_RenderClear(gRenderer);

        //바닥 깔기
        int x_Floor = 1;
        int y_Floor = 9;
        for (int ix=0; ix<10; ix++) {
            for (int iy=0; iy<8; iy++) {
                if (ix == 3 || ix == 4) {
                    SDL_Rect src = {16*2, 16*9, 16, 16};
                    SDL_Rect dest = {ix*64, iy*64, 64, 64};
                
                    SDL_RenderCopy(gRenderer, tex, &src, &dest);
                }
                else if (ix == 6 || ix == 7) {
                    if (iy > 2 && iy <= 4) {
                        SDL_Rect src = {16*5, 16*1, 16, 16};
                        SDL_Rect dest = {ix*64, iy*64, 64, 64};
                
                        SDL_RenderCopy(gRenderer, tex, &src, &dest);
                    }
                    else if (iy > 4) {
                        SDL_Rect src = {16*5, 16*2, 16, 16};
                        SDL_Rect dest = {ix*64, iy*64, 64, 64};
                
                        SDL_RenderCopy(gRenderer, tex, &src, &dest);
                    }
                    else {
                        SDL_Rect src = {16*x_Floor, 16*y_Floor, 16, 16};
                        SDL_Rect dest = {ix*64, iy*64, 64, 64};
                
                        SDL_RenderCopy(gRenderer, tex, &src, &dest);
                    }
                }
                else {
                    SDL_Rect src = {16*x_Floor, 16*y_Floor, 16, 16};
                    SDL_Rect dest = {ix*64, iy*64, 64, 64};
                
                    SDL_RenderCopy(gRenderer, tex, &src, &dest);
                }
            }
        }

        //꾸미기
        {
            int ix = 3;
            int iy = 2;
            int _tile_index = 81;

            int _src_index_x = _tile_index % 8;
            int _src_index_y = _tile_index / 8;
            SDL_Rect src = {16*_src_index_x, 16*_src_index_y, 16, 16};
            SDL_Rect dest = {ix*64, iy*64, 64, 64};

            SDL_RenderCopy(gRenderer, tex, &src, &dest);
        }

        {
            int ix = 4;
            int iy = 2;
            int _tile_index = 81;

            int _src_index_x = _tile_index % 8;
            int _src_index_y = _tile_index / 8;
            SDL_Rect src = {16*_src_index_x, 16*_src_index_y, 16, 16};
            SDL_Rect dest = {ix*64, iy*64, 64, 64};

            SDL_RenderCopy(gRenderer, tex, &src, &dest);
        }

        {
            int ix = 0;
            int iy = 6;
            int _tile_index = 57;

            int _src_index_x = _tile_index % 8;
            int _src_index_y = _tile_index / 8;
            SDL_Rect src = {16*_src_index_x, 16*_src_index_y, 16, 16};
            SDL_Rect dest = {ix*64, iy*64, 64, 64};

            SDL_RenderCopy(gRenderer, tex, &src, &dest);
        }

        {
            int ix = 9;
            int iy = 0;
            int _tile_index = 56;

            int _src_index_x = _tile_index % 8;
            int _src_index_y = _tile_index / 8;
            SDL_Rect src = {16*_src_index_x, 16*_src_index_y, 16, 16};
            SDL_Rect dest = {ix*64, iy*64, 64, 64};

            SDL_RenderCopy(gRenderer, tex, &src, &dest);
        }

        SDL_RenderPresent(gRenderer);

        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    bLoop = SDL_FALSE;
                    break;
            }
        }
    }

    SDL_DestroyWindow(gWindow);

    return 1;
}