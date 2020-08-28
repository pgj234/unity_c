#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "button.h"
#include "util.h"

// extern SDL_bool bLoop;
void Button_Init(S_BUTTON *pBtn, int x, int y, int w, int h, Uint16 btnID, void (*pCallbackBtnPush)(struct _S_BUTTON *)) {
  // pBtn->bCheckHitRect = SDL_FALSE;
  pBtn->m_bVisible = SDL_TRUE;
  pBtn->m_nFSM = 0;
  pBtn->m_Rect.x = x;
  pBtn->m_Rect.y = y;
  pBtn->m_Rect.w = w;
  pBtn->m_Rect.h = h;

  pBtn->m_fillColor.r = 0;
  pBtn->m_fillColor.g = 0;
  pBtn->m_fillColor.b = 0;
  pBtn->m_fillColor.a = 0;
  pBtn->m_pCallbackBtnPush = pCallbackBtnPush;
  pBtn->m_nID = btnID;
}

static void DestroyButton(S_BUTTON *pBtn) {
    SDL_DestroyTexture(pBtn->m_pLable);
    SDL_free(pBtn);
}

static void Button_Render(S_BUTTON *pBtn, SDL_Renderer *pRender) {
    if (pBtn->m_bVisible) {
        //반투명 모드 활성화
        SDL_SetRenderDrawBlendMode(pRender, SDL_BLENDMODE_BLEND);

        SDL_SetRenderDrawColor(pRender, 255, 255, 255, 255);
        SDL_RenderDrawRect(pRender, &pBtn->m_Rect);

        SDL_SetRenderDrawColor(pRender, pBtn->m_fillColor.r, pBtn->m_fillColor.g, pBtn->m_fillColor.b, pBtn->m_fillColor.a);
        SDL_RenderFillRect(pRender, &pBtn->m_Rect);

        pBtn->m_rectLabel.x = pBtn->m_Rect.x + 2;
        pBtn->m_rectLabel.y = pBtn->m_Rect.y + 2;
        pBtn->m_rectLabel.w = pBtn->m_Rect.w - 4;
        pBtn->m_rectLabel.h = pBtn->m_Rect.h - 4;

        SDL_RenderCopy(pRender, pBtn->m_pLable, NULL, &pBtn->m_rectLabel);

        //반투명 모드 비 활성화
        SDL_SetRenderDrawBlendMode(pRender, SDL_BLENDMODE_NONE);
    }
}

void Button_DoEvent(S_BUTTON *pBtn, SDL_Event *pEvt) {
    if (pBtn->m_nFSM == 0) {
        switch (pEvt->type) {
            case SDL_MOUSEMOTION:
                if (checkPointInRect(&pBtn->m_Rect, pEvt->motion.x, pEvt->motion.y)) {
                    pBtn->m_fillColor.a = 0x80;
                    pBtn->m_nFSM = 1;
                }
                break;
        }
    }
    else if (pBtn->m_nFSM == 1) {       //사각형 내부진입상태
        switch (pEvt->type) {
            case SDL_MOUSEMOTION:
                if (!checkPointInRect(&pBtn->m_Rect, pEvt->motion.x, pEvt->motion.y)) {
                pBtn->m_fillColor.a = 0xff;
                pBtn->m_nFSM = 0;
                }
                break;
            case SDL_MOUSEBUTTONDOWN:
                if (checkPointInRect(&pBtn->m_Rect, pEvt->motion.x, pEvt->motion.y)) {
                    if (pBtn->m_pCallbackBtnPush != NULL) {
                        pBtn->m_pCallbackBtnPush(pBtn);
                    }
                }
                break;
        }
    }
}

S_BUTTON *createButton(SDL_Renderer *pRenderer, int x, int y, int w, int h, Uint16 btnID, const Uint16 *text, TTF_Font *pFont, void (*pCallbackBtnPush)(struct _S_BUTTON *)) {
    S_BUTTON *pBtn;
    pBtn = SDL_malloc(sizeof(S_BUTTON));

    pBtn->m_nType = 2;

    pBtn->m_Rect.x = x;
    pBtn->m_Rect.y = y;
    pBtn->m_Rect.w = w;
    pBtn->m_Rect.h = h;

    pBtn->m_nID = btnID;
    pBtn->m_nFSM = 0;
    pBtn->m_bVisible = SDL_TRUE;

    pBtn->m_fillColor.r = 0x00;
    pBtn->m_fillColor.g = 0x96;
    pBtn->m_fillColor.b = 0xc6;
    pBtn->m_fillColor.a = 0xff;

    pBtn->m_pCallbackBtnPush = pCallbackBtnPush;

    //라벨생성
    {
        SDL_Color _whiteColor = {0xff, 0xff, 0xff, 0xff};
        SDL_Color _blackColor = {0, 0, 0, 0x00};
        SDL_Color _editColor = {0xf5, 0xf5, 0xc6, 0x00};
        SDL_Surface *textSurface = TTF_RenderUNICODE_Solid(pFont, text, _editColor);

        pBtn->m_pLable = SDL_CreateTextureFromSurface(pRenderer, textSurface);
        pBtn->m_rectLabel.x = 0;
        pBtn->m_rectLabel.y = 0;
        pBtn->m_rectLabel.w = textSurface->w;
        pBtn->m_rectLabel.h = textSurface->h;

        SDL_FreeSurface(textSurface);
    }

    pBtn->m_fpRender = Button_Render;
    pBtn->m_fpDestroy = DestroyButton;
    pBtn->m_fpDoEvent = Button_DoEvent;

    return pBtn;
}