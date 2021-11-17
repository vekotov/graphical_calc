#include "rpn.h"
#include "structs.h"
#include "defines.h"
#include <stdio.h>
#include <string.h>

Queue *input_to_rpn(char *input) {
    Queue *tokens = input_to_tokens(input);
    Stack *stack = init_stack();
    Queue *exit = init_queue();

    int op;
    double value;
    int i = 0;
    while (!pop_queue(tokens, &op, &value)) {
        consume(op, value, stack, exit, i);
        i++;
    }

    while (!pop_stack(stack, &op, &value)) {
        push_queue(exit, op, value);
    }

    destroy_stack(stack);
    destroy_queue(tokens);
    return exit;
}

Queue *input_to_tokens(char *input) {
    Queue *q = init_queue();
    int is_unary = 1;
    for (int i = 0; input[i] != 0; i++) {
        i = parse_step(input, i, &is_unary, q);
    }
    return q;
}

int get_priority(int op) {
    int ret_v = -1;
    if (op == SUM || op == SUB) {
        ret_v = 1;
    } else if (op == MUL || op == DIV) {
        ret_v = 2;
    } else if (op == POW) {
        ret_v = 3;
    }
    return ret_v;
}

void consume(int op, double value, Stack *stack, Queue *exit, int i) {
    if (is_num_op(op)) {
        push_queue(exit, op, value);
    } else if (is_prefix_op(op)) {
        push_stack(stack, op, value);
    } else if (is_close_bracket(op)) {
        close_bracket(stack, exit, i);
    } else if (is_binary_op(op)) {
        restack_binary_op(op, stack, exit);
        push_stack(stack, op, value);
    } else {
        printf("ERROR ON RPNing TOKEN %i\n", i);
    }
}

int is_num_op(int op) {
    return op == NUM || op == X;
}

int is_close_bracket(int op) {
    return op == CLOSE_BRACKET;
}

int is_prefix_op(int op) {
    return op == SIN
        || op == COS
        || op == TAN
        || op == CTAN
        || op == SQRT
        || op == LOGN
        || op == UNARY_MINUS
        || op == OPEN_BRACKET;
}

int is_binary_op(int op) {
    return op == MUL
        || op == DIV
        || op == SUB
        || op == SUM
        || op == POW;
}

void close_bracket(Stack *stack, Queue *exit, int i) {
    int op;
    double value;
    while (!pop_stack(stack, &op, &value) && op != OPEN_BRACKET) {
        push_queue(exit, op, value);
    }
    if (op != OPEN_BRACKET) {
        printf("NOT FOUND OPEN BRACKET AT TOKEN %d\n", i);
    }
}

void restack_binary_op(int op, Stack *stack, Queue *exit) {
    while (stack->last && get_priority(stack->last->op) >= get_priority(op)) {
        int s_op;
        double s_value;
        pop_stack(stack, &s_op, &s_value);
        push_queue(exit, s_op, s_value);
    }
}

int one_char_op_to_int(char op) {
    int ret_v = -1;
    if (op == 'x') {
        ret_v = X;
    } else if (op == '+') {
        ret_v = SUM;
    } else if (op == '-') {
        ret_v = SUB;
    } else if (op == '/') {
        ret_v = DIV;
    } else if (op == '*') {
        ret_v = MUL;
    } else if (op == '^') {
        ret_v = POW;
    } else if (op == '(') {
        ret_v = OPEN_BRACKET;
    } else if (op == ')') {
        ret_v = CLOSE_BRACKET;
    }
    return ret_v;
}

int check_multichar_ops(char *input) {
    int ret_v = -1;
    if (check_sin(input)) {
        ret_v = SIN;
    } else if (check_cos(input)) {
        ret_v = COS;
    } else if (check_tan(input)) {
        ret_v = TAN;
    } else if (check_ctan(input)) {
        ret_v = CTAN;
    } else if (check_sqrt(input)) {
        ret_v = SQRT;
    } else if (check_log(input)) {
        ret_v = LOGN;
    }
    return ret_v;
}

int check_sin(char *input) {
    return !strncmp(input, "sin(", lenof(SIN) + 1);
}

int check_cos(char *input) {
    return !strncmp(input, "cos(", lenof(COS) + 1);
}

int check_tan(char *input) {
    return !strncmp(input, "tg(", lenof(TAN) + 1);
}

int check_ctan(char *input) {
    return !strncmp(input, "ctg(", lenof(CTAN) + 1);
}

int check_sqrt(char *input) {
    return !strncmp(input, "sqrt(", lenof(SQRT) + 1);
}

int check_log(char *input) {
    return !strncmp(input, "ln(", lenof(LOGN) + 1);
}

int lenof(int op) {
    int ret_v = 0;
    if (op == TAN || op == LOGN) {
        ret_v = 2;
    } else if (op == SIN || op == COS || op == CTAN) {
        ret_v = 3;
    } else if (op == SQRT) {
        ret_v = 4;
    }
    return ret_v;
}

int is_number(char input) {
    return input >= '0' && input <= '9';
}

int skip_number(char *input) {
    int dot_readed = 0;
    int i = 0;
    while (is_number(input[i]) || (input[i] == '.' && !dot_readed)) {
        if (input[i] == '.') dot_readed = 1;
        i++;
    }
    return i;
}

int parse_step(char *input, int i, int *is_unary, Queue *q) {
    if (is_number(input[i])) {
        double value = 0;
        sscanf(input + i, "%lf", &value);
        i = i + skip_number(input + i) - 1;
        push_queue(q, NUM, value);
        *is_unary = 0;
    } else if (input[i] == '-' && (*is_unary)) {
        push_queue(q, UNARY_MINUS, 0);
    } else if (one_char_op_to_int(input[i]) != -1) {
        push_queue(q, one_char_op_to_int(input[i]), 0);
        *is_unary = 1;
    } else if (check_multichar_ops(input + i) != -1) {
        int op = check_multichar_ops(input + i);
        push_queue(q, op, 0);
        push_queue(q, OPEN_BRACKET, 0);
        i += lenof(op);
        *is_unary = 1;
    } else if (input[i] != ' ') {
        printf("PARSING ERROR AT i = %d\n", i);
    }
    return i;
}
