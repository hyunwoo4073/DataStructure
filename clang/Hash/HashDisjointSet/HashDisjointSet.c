#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 해시 테이블 엔트리 구조체
typedef struct Node {
    char* key;
    char* parent;
    struct Node* next; // 체이닝
} Node;

#define TABLE_SIZE 100

Node* hashTable[TABLE_SIZE];

// 간단한 해시 함수
unsigned int hash(const char* s) {
    unsigned int h = 0;
    while (*s) h = (h << 5) + *s++;
    return h % TABLE_SIZE;
}

// 해시 테이블에서 키 찾기
Node* findNode(const char* key) {
    unsigned int idx = hash(key);
    Node* cur = hashTable[idx];
    while (cur) {
        if (strcmp(cur->key, key) == 0) return cur;
        cur = cur->next;
    }
    return NULL;
}

// 노드 삽입 (처음엔 자기 자신을 부모로)
Node* makeSet(const char* key) {
    Node* n = findNode(key);
    if (n) return n;

    n = (Node*)malloc(sizeof(Node));
    n->key = strdup(key);
    n->parent = strdup(key); // 자기 자신을 부모로
    unsigned int idx = hash(key);
    n->next = hashTable[idx];
    hashTable[idx] = n;
    return n;
}

// Find with path compression
const char* find(const char* key) {
    Node* n = makeSet(key);
    if (strcmp(n->parent, n->key) == 0) return n->key;

    const char* root = find(n->parent);
    free(n->parent);
    n->parent = strdup(root);
    return root;
}

// Union
void unionSet(const char* a, const char* b) {
    const char* rootA = find(a);
    const char* rootB = find(b);
    if (strcmp(rootA, rootB) == 0) return;

    Node* nodeA = findNode(rootA);
    free(nodeA->parent);
    nodeA->parent = strdup(rootB);
}

int main(void) {
    makeSet("Alice");
    makeSet("Bob");
    makeSet("Charlie");

    unionSet("Alice", "Bob");
    printf("Alice root: %s\n", find("Alice"));   // 같은 root
    printf("Bob root: %s\n", find("Bob"));       // 같은 root
    printf("Charlie root: %s\n", find("Charlie"));

    unionSet("Charlie", "Bob");
    printf("Alice root: %s\n", find("Alice"));   // 세 명 다 같은 root
    printf("Charlie root: %s\n", find("Charlie"));

    return 0;
}
