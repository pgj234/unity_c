#include <SDL2/SDL.h>

SDL_bool checkPointInRect(SDL_Rect *pRect, Sint32 point_x, Sint32 point_y) {
    SDL_Point _pt = {point_x, point_y};

    return SDL_PointInRect(&_pt, pRect);

    // return SDL_FALSE;
}