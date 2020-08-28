#include <stdio.h>

typedef struct {
    char szName[32];
    int kor;
    int eng;
    int math;
} score_Data;

void setScoreData(score_Data *pScore) {
    scanf("%s %d %d %d\n",
        //(*pScore).szName,
        pScore->szName,
        &pScore->kor,        //(*pScore).kor
        &pScore->eng,
        &pScore->math);
}

void main() {
    score_Data score;

    setScoreData(&score);

    printf("name : %s \n", score.szName);
    printf("kor : %d \n", score.kor);
    printf("eng : %d \n", score.eng);
    printf("math : %d \n", score.math);
}