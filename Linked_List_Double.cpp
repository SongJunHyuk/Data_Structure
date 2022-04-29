#include<stdio.h>
#include<stdlib.h>

typedef int element;
typedef struct DListNode {
    element data;
    struct DListNode* llink;
    struct DListNode* rlink;
} DListNode;

void init(DListNode* phead) {
    phead->llink = phead;
    phead->rlink = phead;
}

void print_dlist(DListNode* phead) {
    DListNode* p;
    for (p = phead->rlink; p != phead; p = p->rlink)
        printf("<-| |%d| |-> ", p->data);
    printf("\n");
}

void dinsert(DListNode* before, element data)
{ // data를 가지는 새로운 노드를 before 노드 오른쪽에 삽입
    DListNode* newnode = (DListNode*)malloc(sizeof(DListNode));
    newnode->data = data;
    newnode->llink = before;		// (1)
    newnode->rlink = before->rlink;	// (2)
    before->rlink->llink = newnode;	// (3)
    before->rlink = newnode;		// (4)
}

void ddelete(DListNode* head, DListNode* removed)
{ // removed 노드를 head가 가리키는 리스트에서 삭제
    if (removed == head) return;
    removed->llink->rlink = removed->rlink;    // (1)
    removed->rlink->llink = removed->llink;    // (2)
    free(removed);
}

int main(void) {
    DListNode* head = (DListNode*)
        malloc(sizeof(DListNode));
    init(head);
    printf("추가 단계\n");
    for (int i = 0; i < 5; i++) {
        // 헤드 노드의 오른쪽에 삽입
        dinsert(head, i);
        print_dlist(head);
    }
    printf("\n삭제 단계\n");
    for (int i = 0; i < 5; i++) {
        print_dlist(head);
        ddelete(head, head->rlink);
    }
    free(head);
    return 0;
}
