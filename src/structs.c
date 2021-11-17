#include <stdlib.h>
#include <stdio.h>
#include "structs.h"

struct QNode *create_node(int op, double value) {
    struct QNode *ret = malloc(sizeof(struct QNode));
    if (ret != NULL) {
        ret->op = op;
        ret->value = value;
        ret->next = NULL;
    }
    return ret;
}

Queue *init_queue() {
    Queue *ret = malloc(sizeof(Queue));
    if (ret != NULL) {
        ret->first = NULL;
    }
    return ret;
}

void push_queue(Queue *q, int op, double value) {
    struct QNode *n = create_node(op, value);
    if (q->first == NULL) {
        q->first = n;
    } else {
        struct QNode *last_node = q->first;
        while (last_node->next != NULL) {
            last_node = last_node->next;
        }
        last_node->next = n;
    }
}

int pop_queue(Queue *q, int *op, double *value) {
    int ret_v = 0;
    if (q->first != NULL) {
        *op = q->first->op;
        *value = q->first->value;
        struct QNode *next = q->first->next;
        free(q->first);
        q->first = next;
    } else {
        ret_v = 1;
    }
    return ret_v;
}

void destroy_queue(Queue *q) {
    struct QNode *next = q->first;
    while (next != NULL) {
        struct QNode *t = next->next;
        free(next);
        next = t;
    }
    free(q);
}

Queue *clone_queue(Queue *from) {
    Queue *ret = init_queue();
    if (ret != NULL) {
        struct QNode *node = from->first;
        while (node != NULL) {
            push_queue(ret, node->op, node->value);
            node = node->next;
        }
    }
    return ret;
}

Stack *init_stack() {
    Stack *ret = malloc(sizeof(Queue));
    if (ret != NULL) {
        ret->last = NULL;
    }
    return ret;
}

void push_stack(Stack *s, int op, double value) {
    struct QNode *new_node = create_node(op, value);
    if (new_node != NULL) {
        new_node->next = s->last;
        s->last = new_node;
    }
}

int pop_stack(Stack *s, int *op, double *value) {
    int ret_v = 0;
    if (s->last != NULL) {
        *op = s->last->op;
        *value = s->last->value;
        struct QNode *t = s->last->next;
        free(s->last);
        s->last = t;
    } else {
        ret_v = 1;
    }
    return ret_v;
}

void destroy_stack(Stack *s) {
    struct QNode *cur = s->last;
    while (cur != NULL) {
        struct QNode *t = cur->next;
        free(cur);
        cur = t;
    }
    free(s);
}
