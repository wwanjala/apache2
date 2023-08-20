#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    enum TypeTag {
        ADD,
        SUB,
        MUL,
        FIBO
    } type;
    int arg1;
    int arg2;
    struct Node *func1;
    struct Node *func2;
} Node;

int add(int a, int b) { return a + b; }
int sub(int a, int b) { return a - b; }
int mul(int a, int b) { return a * b; }
int fibo(int n) {
    if (n <= 0) return 0;
    if (n == 1) return 1;

    int prev = 0;
    int curr = 1;

    for (int i = 2; i < n; ++i) {
        int next = prev + curr;
        prev = curr;
        curr = next;
    }

    return curr;
}

Node* makeFunc(enum TypeTag type) {
    Node *node = (Node *)malloc(sizeof(Node));
    node->type = type;
    node->arg1 = 0;
    node->arg2 = 0;
    node->func1 = NULL;
    node->func2 = NULL;
    return node;
}

void calc(Node *node) {
    switch (node->type) {
        case ADD:
            printf("add : %d\n", add(node->arg1, node->arg2));
            break;
        case SUB:
            printf("sub : %d\n", sub(node->func1->func1->arg1, node->func2->func1->arg1));
            break;
        case MUL:
            printf("mul : %d\n", mul(node->arg1, node->arg2));
            break;
        case FIBO:
            printf("fibo : %d\n", fibo(node->func1->func1->func1->arg1));
            break;
    }
}

int main() {
    Node *add = makeFunc(ADD);
    add->arg1 = 10;
    add->arg2 = 6;

    Node *mul = makeFunc(MUL);
    mul->arg1 = 5;
    mul->arg2 = 4;

    Node *sub = makeFunc(SUB);
    sub->func1 = mul;
    sub->func2 = add;

    Node *fibo = makeFunc(FIBO);
    fibo->func1 = sub;
    fibo->func1->func1 = makeFunc(SUB);
    fibo->func1->func1->func1 = makeFunc(ADD);
    fibo->func1->func1->func1->arg1 = 20;
    fibo->func1->func1->func1->arg2 = 16;
    fibo->func1->func1->func2 = makeFunc(MUL);
    fibo->func1->func1->func2->arg1 = 6;
    fibo->func1->func1->func2->arg2 = 4;

    calc(add);
    calc(mul);
    calc(sub);
    calc(fibo);

    free(add);
    free(mul);
    free(sub);
    free(fibo);

    return 0;
}
