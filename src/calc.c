#include "defines.h"
#include "calc.h"
#include "structs.h"
#include <stdlib.h>
#include <stdio.h>

double calculate(double x, Queue *expression) {
    Stack *stack = init_stack();
    int op;
    double value;
    int i = 0;
    while (!pop_queue(expression, &op, &value)) {
        consume_calc(stack, op, value, i, x);
        i++;
    }
    pop_stack(stack, &op, &value);
    destroy_stack(stack);
    destroy_queue(expression);
    return value;
}

double(*get_unary_op(int op))(double) {
    double (*ret_v)(double n) = NULL;
    if (op == UNARY_MINUS) {
        ret_v = minus;
    } else if (op == COS) {
        ret_v = cos;
    } else if (op == SIN) {
        ret_v = sin;
    } else if (op == TAN) {
        ret_v = tan;
    } else if (op == CTAN) {
        ret_v = ctg;
    } else if (op == SQRT) {
        ret_v = sqrt;
    } else if (op == LOGN) {
        ret_v = log;
    }
    return ret_v;
}

double(*get_binary_op(int op))(double, double) {
    double (*ret_v)(double a, double b) = NULL;
    if (op == SUM) {
        ret_v = sum;
    } else if (op == SUB) {
        ret_v = substaction;
    } else if (op == MUL) {
        ret_v = multiply;
    } else if (op == DIV) {
        ret_v = division;
    } else if (op == POW) {
        ret_v = pow;
    }
    return ret_v;
}

double minus(double num) {
    return -num;
}

double sum(double a, double b) {
    return a + b;
}

double substaction(double a, double b) {
    return a - b;
}

double multiply(double a, double b) {
    return a * b;
}

double division(double a, double b) {
    return a / b;
}

double ctg(double num) {
    return 1 / tan(num);
}

void consume_calc(Stack *stack, int op, double value, int i, double x) {
    if (op == NUM) {
        push_stack(stack, NUM, value);
    } else if (op == X) {
        push_stack(stack, NUM, x);
    } else if (get_unary_op(op) != NULL) {
        double (*func)(double num) = get_unary_op(op);
        pop_stack(stack, &op, &value);
        value = func(value);
        push_stack(stack, op, value);
    } else if (get_binary_op(op) != NULL) {
        double value1, value2;
        double (*func)(double a, double b) = get_binary_op(op);
        pop_stack(stack, &op, &value1);
        pop_stack(stack, &op, &value2);
        value1 = func(value2, value1);
        push_stack(stack, op, value1);
    } else {
        printf("ERROR ON CALCULATING TOKEN %i\n", i);
    }
}
