#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>

// const int  STUDENT_MAX = 1000;
#define STUDENT_MAX 1000

typedef struct {
    int score[STUDENT_MAX][3];      //성적
    char name[STUDENT_MAX][8];      //이름
    int stu_Num[STUDENT_MAX][1];    //학번
} info;

int tail_Index = -1;

int main(int argc, char *argv[])
{
  info info;

  // 학번 초기화
  for (int i=0; i<STUDENT_MAX; i++) {
    info.stu_Num[i][0] = 0;
  }

  SDL_bool bLoop = SDL_TRUE;
  while (bLoop)
  {
    char _sel_menu;

    printf("\n1. input score \n");
    printf("2. del score \n");
    printf("3. edit score \n");
    printf("4. get total score \n");
    printf("5. get average \n");
    printf("p. print score \n");
    printf("q. quit \n");
    printf("------------------------------ \n");

    _sel_menu = getchar();
    rewind(stdin);

    switch (_sel_menu)
    {
    case '1':
      printf("input score [name,kor,eng,math,student_Num] \n");
      {
        char _tokenBuffer[32][8];
        int _tokenIndex = 0;
        int _index = 0;

        char _c;
        do {
          _c = getchar();
          
          if(_c == ',') {
            _tokenBuffer[_tokenIndex][_index] = 0x00;
            _tokenIndex++;
            _index = 0;
          }
          else 
          {
            _tokenBuffer[_tokenIndex][_index++] = _c;
          }

        } while(_c != '\n');

        _tokenBuffer[_tokenIndex][_index] = 0x00;

        {
          SDL_bool chk = SDL_FALSE;

          for (int i=0; i<STUDENT_MAX; i++) {
            //0포함 음수 판단
            if (atoi(_tokenBuffer[4]) <= 0) {
                printf("zero OR negative number \n");
                chk = SDL_TRUE;
                break;
            }

            //중복 확인
            if (info.stu_Num[i][0] == atoi(_tokenBuffer[4])) {
                printf("already have the same student number \n");
                chk = SDL_TRUE;
                break;
            }
          }

          if (chk == SDL_FALSE) {
              printf("[%s] %s %s %s  %s \n", _tokenBuffer[0], _tokenBuffer[1], _tokenBuffer[2], _tokenBuffer[3], _tokenBuffer[4]);

              tail_Index++;
              strcpy(info.name[tail_Index],_tokenBuffer[0]);
              info.score[tail_Index][0] = atoi(_tokenBuffer[1]);
              info.score[tail_Index][1] = atoi(_tokenBuffer[2]);
              info.score[tail_Index][2] = atoi(_tokenBuffer[3]);
              info.stu_Num[tail_Index][0] = atoi(_tokenBuffer[4]);
          }

          chk = SDL_FALSE;
        }
      }
      break;
    case '2':
      {
          int stNum;
          printf("------------------------------\n");
          printf("delete score student number : \n");

          scanf("%d", &stNum);
          rewind(stdin);

          for (int i=0;i<=tail_Index;i++) {
                if (tail_Index == -1) {
                    printf("\nno data\n");
                    break;
                }
                else if (info.stu_Num[i][0] == stNum) {
                    // 인덱스 i번째 학생 정보 가져오기
                    printf("---------------------------------------- \n");
                    printf("NAME, kor, eng, math, STUDENT_NUM \n");
                    printf("[%s] %d %d %d  %d \n", info.name[i], info.score[i][0], info.score[i][1], info.score[i][2], stNum);
                    printf("---------------------------------------- \n");
                    printf("input the subject name to delete : ");

                    char delStr[16];
                    gets(delStr);

                    if (strcmp(delStr, "kor") == 0) {
                        info.score[i][0] = 0;
                        printf("\n score delete complete [%d]", info.score[i][0]);
                    }
                    else if (strcmp(delStr, "eng") == 0) {
                        info.score[i][1] = 0;
                        printf("\n score delete complete [%d]", info.score[i][1]);
                    }
                    else if (strcmp(delStr, "math") == 0) {
                        info.score[i][2] = 0;
                        printf("\n score delete complete [%d]", info.score[i][2]);
                    }
                    
                    break;
                }
          }
      }
      rewind(stdin);
      break;
    case '3':
        {
            int stNum;
            printf("---------------------------\n");
            printf("edit student number : \n");

            scanf("%d", &stNum);
            rewind(stdin);

            for (int i=0;i<=tail_Index;i++) {
                if (tail_Index == -1) {
                    printf("\nno data\n");
                    break;
                }
                else if (info.stu_Num[i][0] == stNum) {
                    // 인덱스 i번째 학생 정보 가져오기
                    printf("---------------------------------------- \n");
                    printf("NAME, kor, eng, math, STUDENT_NUM \n");
                    printf("[%s] %d %d %d  %d \n", info.name[i], info.score[i][0], info.score[i][1], info.score[i][2], stNum);
                    printf("---------------------------------------- \n");
                    printf("input the subject name to edit : ");

                    char editStr[16];
                    gets(editStr);

                    if (strcmp(editStr, "kor") == 0) {
                        printf("\n'kor' edit score : ");

                        scanf("%d", &info.score[i][0]);
                        printf("\n score edit complete [%d]", info.score[i][0]);
                    }
                    else if (strcmp(editStr, "eng") == 0) {
                        printf("\n'eng' edit score : ");

                        scanf("%d", &info.score[i][1]);
                        printf("\n score edit complete [%d]", info.score[i][1]);
                    }
                    else if (strcmp(editStr, "math") == 0) {
                        printf("\n'math' edit score : ");

                        scanf("%d", &info.score[i][2]);
                        printf("\n score edit complete [%d]", info.score[i][2]);
                    }
                    
                    break;
                }
            }
        }
        rewind(stdin);
        break;
    case '4':
      {
          for (int i=0;i<=tail_Index;i++) {
                if (tail_Index == -1) {
                    printf("\nno data\n");
                    break;
                }
                else {
                    printf("---------------------------------------- \n");
                    printf("Total_Score\n");
                    printf("---------------------------------------- \n");
                    printf("kor, eng, math \n");

                    int kor_Total = 0;
                    int eng_Total = 0;
                    int math_Total = 0;

                    for (int j=0; j<=tail_Index; j++) {
                        kor_Total += info.score[j][0];
                        eng_Total += info.score[j][1];
                        math_Total += info.score[j][2];
                    }

                    printf("%d, %d, %d\n", kor_Total, eng_Total, math_Total);
                    break;
                }
          }
      }
        rewind(stdin);
        break;
    case '5':
        {
            for (int i=0;i<=tail_Index;i++) {
                if (tail_Index == -1) {
                    printf("\nno data\n");
                    break;
                }
                else {
                    printf("---------------------------------------- \n");
                    printf("Average_Score\n");
                    printf("---------------------------------------- \n");
                    printf("kor, eng, math \n");

                    float kor_Total = 0.0;
                    float eng_Total = 0.0;
                    float math_Total = 0.0;

                    for (int j=0; j<=tail_Index; j++) {
                        kor_Total += info.score[j][0];
                        eng_Total += info.score[j][1];
                        math_Total += info.score[j][2];
                    }

                    printf("%f, %f, %f\n", kor_Total/(tail_Index +1), eng_Total/(tail_Index +1), math_Total/(tail_Index +1));
                    break;
                }
          }
        }
        rewind(stdin);
        break;
    case 'p':
      {
        printf("---------------------------\n");
        for(int i=0;i<=tail_Index;i++)
        {
            printf("NAME, KOR, ENG, MATH, STUDENT_NUM \n");
            printf("%8s%4d%4d%4d%4d\n", info.name[i], info.score[i][0], info.score[i][1], info.score[i][2], info.stu_Num[i][0]);
        }
        printf("press any key......");
        getchar();
        rewind(stdin);
      }
      break;
    case 'q':
      bLoop = SDL_FALSE;
      break;

    default:
      break;
    }
  }

  return 0;
}