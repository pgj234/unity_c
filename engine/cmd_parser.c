#include "core.h"

#define MAX_TOKEN_SIZE 32

// extern Sint16 g_worldMap_Layer_1[];

// Sint16 *g_worldMap_Layer[8];

// void setup_cmd_parser(Sint16 * pWorldMap) {
//   g_worldMap_Layer[0] = pWorldMap;
// }

int doTokenize(char *szBuf, char szBufToken[8][MAX_TOKEN_SIZE]) {
    //change 10
    //[change,10]
    char *szpTemp;
    char *pNextToken = NULL;
    const char *pszDelimiter = " ";
    szpTemp = strtok(szBuf, pszDelimiter);

    int _nTokenIndex = 0;
    while (szpTemp != NULL) {
      strcpy(szBufToken[_nTokenIndex],szpTemp);
      _nTokenIndex++;
      szpTemp = strtok(NULL, pszDelimiter);
    }

    return _nTokenIndex;
}

void parseCmd(char *_szCmd) {
    static char szCmd[225];
    static char szTokens[8][32];

    strcpy(szCmd,_szCmd);

    printf("token count %s\n",szCmd);
    int _numToken = doTokenize(szCmd, szTokens);

    printf("token count %d\n",_numToken);

    if (strcmp(szTokens[0], "quit") == 0) {
      SDL_Event evt;
      evt.type = SDL_QUIT;
      evt.quit.timestamp = SDL_GetTicks();
      SDL_PushEvent(&evt);
    }
    else if (strcmp(szTokens[0], "save") == 0) {
      //save file.map
      char *pFileName = szTokens[1];
      // SDL_RWops *rw = SDL_RWFromFile(pFileName, "wb");
      // SDL_RWwrite(rw, g_worldMap_Layer[0], sizeof(Uint16), 225);
      // SDL_RWclose(rw);

      static char pMsg[32];
      strcpy(pMsg, "save");
      strcpy(pMsg +16, pFileName);
      SDL_Event evt;
      evt.type = SDL_USEREVENT;
      evt.user.data1 = pMsg;
      evt.user.timestamp = SDL_GetTicks();
      SDL_PushEvent(&evt);
    }
    else if (strcmp(szTokens[0], "load") == 0) {
      char *pFileName = szTokens[1];

      static char pMsg[32];
      strcpy(pMsg, "load");
      strcpy(pMsg +16, pFileName);
      SDL_Event evt;
      evt.type = SDL_USEREVENT;
      evt.user.data1 = pMsg;
      evt.user.timestamp = SDL_GetTicks();
      SDL_PushEvent(&evt);

      // SDL_RWops *rw = SDL_RWFromFile(pFileName, "rb");
      // SDL_RWread(rw, g_worldMap_Layer[0], sizeof(Uint16), 225);
      // SDL_RWclose(rw);
    }
    else if (strcmp(szTokens[0], "new") == 0) {
      // memset(g_worldMap_Layer[0],-1,256);

      static char *pMsg = "new";
      SDL_Event evt;
      evt.type = SDL_USEREVENT;
      evt.user.data1 = pMsg;
      evt.user.timestamp = SDL_GetTicks();
      SDL_PushEvent(&evt);
    }
    else if (strcmp(szTokens[0], "brush") == 0) {     //brush change (attr)
        if (strcmp(szTokens[1], "change") == 0) {
            static char *pMsg = "brush change";
            int attr = atoi(szTokens[2]);

            // 브러쉬 알림
            // switch (attr) {
            //   case 0 : 
            //       break;
            //   case 1 : 
            //       break;
            //   case 2 : 
            //       break;
            //   case 3 : 
            //       break;
            //   case 4 : 
            //       break;
            //   case 5 : 
            //       break;
            // }

            SDL_Event evt;
            evt.type = SDL_USEREVENT;
            evt.user.data1 = pMsg;
            evt.user.code = attr;
            evt.user.timestamp = SDL_GetTicks();

            SDL_PushEvent(&evt);
        }
    }
}