#include "../engine/core.h"
#include "../engine/graph.h"
#include "../engine/entity/sprite.h"

SDL_Rect g_sheet_rects[] = {
    {730, 340, 75, 70},
    {671, 0, 75, 70},
    {671, 70, 75, 70}
};

tDE_S_Core *g_pEngineCore;

void callBack_render(void *pNode, void *param) {
    tDE_S_Node *_pNode = pNode;
    tDE_S_ObjectBase *pEntity = _pNode->m_pEntity;

    pEntity->m_fpRender(pEntity, g_pEngineCore->m_pRender);
}

void callBack_event(void *pNode, void *param) {
    tDE_S_Node *_pNode = pNode;
    tDE_S_ObjectBase *pEntity = _pNode->m_pEntity;

    pEntity->m_fpDoEvent(pEntity, param);
}

void callBack_freeNode(void *pNode, void *param) {
    tDE_S_Node *_pNode = pNode;
    tDE_S_ObjectBase *pEntity = _pNode->m_pEntity;
    pEntity->m_fpDestroy(pEntity);
    SDL_free(pNode);
}

void mouseDownCallBack(void *ptr) {
    tDE_S_ObjectBase *pEntity = ptr;

    tDE_S_Node *pFindNode = tDE_graph_FindNodeById(NULL, pEntity->m_nId);

    tDE_graph_remove_node(pFindNode);

    pEntity->m_fpDestroy(pEntity);
    SDL_free(pFindNode);

    printf("[%8d] \r", pEntity->m_nId);
}

int main(int argc, char *argv[]) {
    tDE_graph_init();

    tDE_S_Core *pEngineCore = tDE_setup_1("example2", 640, 480, 0);
    g_pEngineCore = pEngineCore;
    SDL_Texture *pSprTex = tDE_util_loadTexture(pEngineCore, "../res/tanks/sheet_tanks.png");

    for (int i=0; i<100; i++) {
        tDE_S_ObjectBase *pSprEntity = tDE_Entity_createSprite(rand()%640, rand()%480, 0, g_sheet_rects[0], pSprTex, mouseDownCallBack, NULL, NULL);

        tDE_S_Node *pNode = SDL_calloc(sizeof(tDE_S_Node), 1);
        pNode->m_pEntity = pSprEntity;

        pSprEntity->m_nId = tDE_graph_add_node(pNode, NULL);
    }

    SDL_bool bLoop = SDL_TRUE;

    while (bLoop) {
        SDL_SetRenderDrawColor(pEngineCore->m_pRender, 0, 0, 0, 0xff);
        SDL_RenderClear(pEngineCore->m_pRender);

        // pSpr->m_fpRender(pSpr, pEngineCore->m_pRender);
        tDE_graph_Traverse(NULL, NULL, NULL);

        SDL_RenderPresent(pEngineCore->m_pRender);

        SDL_Event event;

        while (SDL_PollEvent(&event)) {
            tDE_graph_Traverse(NULL, callBack_event, &event);

            switch(event.type) {
                case SDL_QUIT:
                    bLoop = SDL_FALSE;
                    break;
            }
        }
    }

    tDE_graph_Traverse(NULL, callBack_freeNode, NULL);

    SDL_DestroyTexture(pSprTex);
    tDE_closeCore(pEngineCore);

    tDE_graph_close();

    return 0;
}