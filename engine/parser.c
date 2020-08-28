#include <stdio.h>
#include <string.h>
#define MAX_TOKEN_SIZE 32

int doTokenize(char *szBuf, char szBufToken[8][MAX_TOKEN_SIZE])
{
  //change 10
  //[change,10]
  char *szpTemp;
  char *pNextToken = NULL;
  const char *pszDelimiter = " ";
  szpTemp = strtok(szBuf, pszDelimiter);

  int _nTokenIndex = 0;
  while (szpTemp != NULL)
  {
    strcpy(szBufToken[_nTokenIndex],szpTemp);
    _nTokenIndex++;
    szpTemp = strtok(NULL, pszDelimiter);
  }
  return _nTokenIndex;
}