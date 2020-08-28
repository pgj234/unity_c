#ifndef __UI_BASE_H__
#define __UI_BASE_H__

enum {
    MYUI_TEXT_LABLE = 1,
    MYUI_BUTTON,
    MYUI_TEXT_INPUT,
    MYUI_CHECK_BUTTON
};

typedef struct ui_base {

    Uint16 m_nType;
    SDL_bool m_bVisible;
    Uint16 m_nID;
    void (*m_fpDestroy)(void *pObj);
    void (*m_fpRender)(void *pObj, SDL_Renderer *pRender);
    void (*m_fpDoEvent)(void *pObj, SDL_Event *pEvt);
    void (*m_fpApply)(void *pObj, Uint32 tick);

} S_UIBase;

#endif