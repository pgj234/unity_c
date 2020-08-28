//선택 정렬
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

const int numCnt = 100;         //총 숫자 갯수
const int numLength = 1000;     //최대 자릿수 *10

void Sort(int arr[], int arrLength) {

    int sel_Index;  //인덱스 선택
    int tmp_Num;    //값 임시 저장소

    for (int i = 0; i < arrLength; i++) {
        sel_Index = i;

        for (int j = i +1; j < arrLength; j++) {
            if (arr[i] > arr[j] && arr[sel_Index] > arr[j]) {
                sel_Index = j;
            }
        }

        tmp_Num = arr[i];
        arr[i] = arr[sel_Index];
        arr[sel_Index] = tmp_Num;
    }

    printf("\n\n------------------------------------------------------------ After ------------------------------------------------------------- \n\n");
    for (int i=0; i < numCnt; i++) {
        printf("[%3d] ",arr[i]);
    }
}

void main() {
    srand(time(NULL));

    int arr[numCnt];

    printf("------------------------------------------------------------ Before ------------------------------------------------------------ \n");
    for (int i=0; i<numCnt; i++) {
        arr[i] = rand()%numLength;
        printf("[%3d] ",arr[i]);
    }

    Sort(arr, sizeof(arr) / sizeof(arr[0]));
}