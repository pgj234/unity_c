#include <stdio.h>
#include <malloc.h>

typedef struct _node {
    int number;
    struct _node *p_next;
} NODE;

int main() {
    NODE *phead = NULL;
    phead = (NODE *)malloc(sizeof(NODE));
    phead->number = 12;
    phead->p_next = NULL;

//노드 추가
    {
        NODE *p = phead;

        while (p->p_next != NULL) {
            p = p->p_next;
        }
        p->p_next = (NODE *)malloc(sizeof(NODE));
        p = p->p_next;

        p->number = 13;
        p->p_next = NULL;
    }

    {
        NODE *p = phead;

        while (p->p_next != NULL) {
            p = p->p_next;
        }
        p->p_next = (NODE *)malloc(sizeof(NODE));
        p = p->p_next;
        
        p->number = 14;
        p->p_next = NULL;
    }

    {
        NODE *p = phead;

        while (p->p_next != NULL) {
            p = p->p_next;
        }
        p->p_next = (NODE *)malloc(sizeof(NODE));
        p = p->p_next;
        
        p->number = 15;
        p->p_next = NULL;
    }

    {
        NODE *p = phead;

        while (p->p_next != NULL) {
            p = p->p_next;
        }
        p->p_next = (NODE *)malloc(sizeof(NODE));
        p = p->p_next;
        
        p->number = 16;
        p->p_next = NULL;
    }

//순회
    {
        NODE *p = phead;

        while (p != NULL) {
            printf("%d \n", p->number);
            p = p->p_next;
        }
    }

    {
        NODE *p = phead;
        NODE *_p_pre;
        NODE *_p_next;

        while (p != NULL) {
            _p_pre = p->p_next;

            if (p->number == 13) {
                printf("remove : %d \n", p->number);
                _p_pre->p_next = _p_next;
                free(p);
                break;
            }

            _p_pre = p;
            p = p->p_next;
        }
    }

//pop
    {
        NODE *p = phead;
        NODE *_p_pre = NULL;
//get tail
        while (p->p_next != NULL) {
            _p_pre = p;
            p = p->p_next;
        }
        printf("pop : %d \n", p->number);
        free(p);
        _p_pre->p_next = NULL;
    }

//del
    {
        NODE *p = phead;
        NODE *_p_next = p->p_next;
        printf("del : %d \n", p->number);
        free(p);
        phead = _p_next;
    }

    {
        NODE *p = phead;

        while (p != NULL) {
            printf("free %d \n", p->number);
            NODE *_p_next = p->p_next;
            free(p);
            p = _p_next;
        }
    }

    return 0;
}