#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

// ===============================
// 웨이팅 정보 구조체
// ===============================
typedef struct Waiting {
    int id;             // 대기번호
    int nperson;        // 인원수
    char info[32];      // 전화번호
} Element;

// ===============================
// 이중연결 리스트 노드
// ===============================
typedef struct DNode {
    Element data;
    struct DNode* prev;
    struct DNode* next;
} DNode;

// 헤드 노드(더미 노드)
DNode org;

// ===============================
// 공통 함수
// ===============================
void error(const char* message) {
    printf("%s\n", message);
    exit(1);
}

DNode* alloc_dnode(Element e) {
    DNode* p = (DNode*)malloc(sizeof(DNode));
    if (p == NULL) {
        error("메모리 할당 실패!");
    }
    p->data = e;
    p->prev = NULL;
    p->next = NULL;
    return p;
}

Element free_dnode(DNode* p) {
    Element e = p->data;
    free(p);
    return e;
}

// ===============================
// 리스트 초기화 / 비우기
// ===============================
void init_list() {
    org.prev = NULL;
    org.next = NULL;
}

int is_empty() {
    return org.next == NULL;
}

void destroy_list() {
    while (!is_empty()) {
        DNode* p = org.next;
        org.next = p->next;
        if (org.next != NULL) {
            org.next->prev = &org;
        }
        free(p);
    }
}

// ===============================
// 리스트 크기 구하기
// ===============================
int size() {
    int count = 0;
    DNode* p = org.next;
    while (p != NULL) {
        count++;
        p = p->next;
    }
    return count;
}

// ===============================
// pos 위치 노드 가져오기
// pos = -1 이면 헤드 노드(&org) 반환
// ===============================
DNode* get_node(int pos) {
    DNode* p = &org;

    if (pos < -1) return NULL;

    for (int i = -1; i < pos; i++) {
        p = p->next;
        if (p == NULL) return NULL;
    }
    return p;
}

// ===============================
// pos 위치의 데이터 가져오기
// ===============================
Element get_entry(int pos) {
    DNode* p = get_node(pos);
    if (p == NULL) {
        error("get_entry: 잘못된 위치입니다.");
    }
    return p->data;
}

// ===============================
// 삽입
// pos 위치에 e 삽입
// 예: pos=0 -> 맨 앞 삽입
// ===============================
void insert(int pos, Element e) {
    DNode* before = get_node(pos - 1);

    if (before == NULL) {
        error("insert: 잘못된 위치입니다.");
    }

    DNode* p = alloc_dnode(e);

    p->next = before->next;
    p->prev = before;
    before->next = p;

    if (p->next != NULL) {
        p->next->prev = p;
    }
}

// ===============================
// 삭제
// pos 위치의 노드 삭제 후 데이터 반환
// ===============================
Element delete(int pos) {
    DNode* p = get_node(pos);

    if (pos < 0 || p == NULL) {
        error("delete: 잘못된 위치입니다.");
    }

    p->prev->next = p->next;

    if (p->next != NULL) {
        p->next->prev = p->prev;
    }

    return free_dnode(p);
}

// ===============================
// 웨이팅 기능
// ===============================

// 새로운 웨이팅 등록
void reserve(int nperson, const char info[]) {
    static int id = 0;
    Element e;

    e.id = ++id;                 // 대기번호 자동 증가
    e.nperson = nperson;
    strncpy(e.info, info, sizeof(e.info) - 1);
    e.info[sizeof(e.info) - 1] = '\0';

    insert(size(), e);           // 맨 뒤 삽입

    printf("<등록> 번호 %d: 인원 %d명 %s\n", e.id, e.nperson, e.info);
}

// 웨이팅 순서 확인
void find_waiting(int wid) {
    int nTeam = 0;
    int nPeople = 0;

    for (int pos = 0; pos < size(); pos++) {
        Element e = get_entry(pos);

        if (e.id == wid) {
            printf("<확인> 번호 %d번 앞 대기팀: %d팀 %d명\n", wid, nTeam, nPeople);
            return;
        }

        nTeam += 1;
        nPeople += e.nperson;
    }

    printf("<확인 실패> %d번 웨이팅을 찾을 수 없습니다.\n", wid);
}

// 웨이팅 취소
void cancel(int wid) {
    for (int pos = 0; pos < size(); pos++) {
        Element e = get_entry(pos);

        if (e.id == wid) {
            delete(pos);
            printf("<취소> %d번 웨이팅이 취소되었습니다.\n", wid);
            return;
        }
    }

    printf("<취소 실패> %d번 웨이팅을 찾을 수 없습니다.\n", wid);
}

// 순서를 한 칸 뒤로 밀기
void delay(int wid) {
    for (int pos = 0; pos < size() - 1; pos++) {
        Element e = get_entry(pos);

        if (e.id == wid) {
            delete(pos);
            insert(pos + 1, e);
            printf("<연기> %d번 웨이팅이 한 칸 연기되었습니다.\n", wid);
            return;
        }
    }

    printf("<연기 실패> %d번 웨이팅을 한 칸 뒤로 밀 수 없습니다.\n", wid);
}

// 전체 출력
void print_waiting() {
    printf("[현재 대기 상황]\n");

    if (size() == 0) {
        printf("대기팀이 없습니다.\n\n");
        return;
    }

    for (int pos = 0; pos < size(); pos++) {
        Element e = get_entry(pos);
        printf("번호 %2d : %d명 %s\n", e.id, e.nperson, e.info);
    }
    printf("\n");
}

// 손님 입장시키기 (맨 앞 삭제)
void service() {
    if (size() == 0) {
        printf("<입장 실패> 대기팀이 없습니다.\n");
        return;
    }

    Element e = delete(0);
    printf("<입장> %d번 손님 입장 (%d명, %s)\n", e.id, e.nperson, e.info);
}

// ===============================
// 메인 함수 (테스트)
// ===============================
int main(void) {
    init_list();

    print_waiting();

    reserve(2, "010-xxxx-8762");
    reserve(2, "010-xxxx-3303");
    reserve(5, "010-xxxx-1212");
    reserve(1, "010-xxxx-2305");
    print_waiting();

    service();
    print_waiting();

    reserve(3, "010-xxxx-4949");
    reserve(4, "010-xxxx-7345");
    print_waiting();

    find_waiting(4);

    delay(3);
    delay(3);
    print_waiting();

    cancel(5);
    print_waiting();

    destroy_list();
    return 0;
}