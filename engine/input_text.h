#ifndef __INPUT_TEXT_H_
#define __INPUT_TEXT_H_

typedef struct _input_text {

    //베이스 구조체
    S_UIBase m_base;

    TTF_Font *m_pFont;
    SDL_Texture *m_pTextTexture;
  
    SDL_Rect m_Rect;
    Uint16 m_nFSM;

    SDL_Point m_textSize;

    SDL_Color m_fgColor;
    SDL_Color m_bgColor;

    char m_szBuf[256];

} S_INPUT_TEXT;

S_INPUT_TEXT *myui_createInputText(SDL_Renderer *pRenderer, int x, int y,int w,int h, Uint16 nID, TTF_Font *pFont, SDL_Color fgColor, SDL_Color bgColor);

#endif