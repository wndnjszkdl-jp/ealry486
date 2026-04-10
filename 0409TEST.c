//#include <stdio.h>
//#include <stdlib.h>
//
//// 1. 노드 구조체 정의
//typedef struct Node {
//    int data;              // 데이터
//    struct Node* link;     // 다음 노드 주소
//} Node;
//
//// head 포인터 (리스트 시작점)
//Node* head = NULL;
//
//// 2. 노드 생성 함수
//Node* create_node(int data) {
//    Node* p = (Node*)malloc(sizeof(Node));
//    p->data = data;
//    p->link = NULL;
//    return p;
//}
//
//// 3. 맨 앞에 삽입
//void insert_first(int data) {
//    Node* p = create_node(data);
//
//    p->link = head;  // 새 노드가 기존 첫 노드를 가리킴
//    head = p;        // head를 새 노드로 변경
//}
//
//// 4. 특정 위치에 삽입
//void insert(int pos, int data) {
//    Node* p = create_node(data);
//
//    // 맨 앞 삽입
//    if (pos == 0) {
//        p->link = head;
//        head = p;
//        return;
//    }
//
//    // pos-1 위치 찾기
//    Node* before = head;
//    for (int i = 0; i < pos - 1; i++) {
//        before = before->link;
//    }
//
//    // 연결 변경 (핵심)
//    p->link = before->link;
//    before->link = p;
//}
//
//// 5. 삭제
//void delete_node(int pos) {
//    Node* temp;
//
//    // 맨 앞 삭제
//    if (pos == 0) {
//        temp = head;
//        head = head->link;
//        free(temp);
//        return;
//    }
//
//    // pos-1 위치 찾기
//    Node* before = head;
//    for (int i = 0; i < pos - 1; i++) {
//        before = before->link;
//    }
//
//    // 삭제 대상
//    temp = before->link;
//
//    // 연결 건너뛰기 (핵심)
//    before->link = temp->link;
//
//    free(temp);
//}
//
//// 6. 리스트 출력
//void print_list() {
//    Node* p = head;
//
//    while (p != NULL) {
//        printf("%d -> ", p->data);
//        p = p->link;
//    }
//
//    printf("NULL\n");
//}
//
//// 7. 메인 함수 (테스트)
//int main() {
//
//    insert_first(10);
//    insert_first(20);
//    insert_first(30);
//
//    print_list();
//    // 30 -> 20 -> 10 -> NULL
//
//    insert(1, 99);
//
//    print_list();
//    // 30 -> 99 -> 20 -> 10 -> NULL
//
//    delete_node(2);
//
//    print_list();
//    // 30 -> 99 -> 10 -> NULL
//
//    return 0;
//}