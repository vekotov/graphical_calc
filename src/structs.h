#ifndef SRC_STRUCTS_H_
#define SRC_STRUCTS_H_

/**************************************************************************************************
 *  Generic-нода для стэка и очереди лексем
 *  
 *          Поля:
 *  struct QNode *next - ссылка на следующую ноду (NULL если её нет)
 *  int op - ID лексемы
 *  double value - значение лексемы (в случае если лексема хранит число)
**************************************************************************************************/
struct QNode {
    struct QNode *next;
    int op;
    double value;
};

/**************************************************************************************************
 *  Функция создания ноды
 *
 *          Аргументы:
 *  int op - ID лексемы (см. defines.h)
 *  double value - значение лексемы (в случае если лексема хранит число)
**************************************************************************************************/
struct QNode *create_node(int op, double value);

/**************************************************************************************************
 *  Тип данных: Очередь
 *
 *          Поля:
 *  struct QNode *first - первый на выход элемент очереди
**************************************************************************************************/
typedef struct {
    struct QNode *first;
} Queue;

/**************************************************************************************************
 *  Функция создания очереди
 *
 *          Возвращает:
 *  Queue *result - пустая очередь без нод
**************************************************************************************************/
Queue *init_queue();

/**************************************************************************************************
 *  Функция вставки лексемы в конец очереди
 *
 *          Аргументы:
 *  Queue *q - очередь в конец которой надо вставить лексему
 *  int op - ID лексемы (см. defines.h)
 *  double value - значение лексемы (в случае если лексема хранит число)
**************************************************************************************************/
void push_queue(Queue *q, int op, double value);

/**************************************************************************************************
 *  Функция получения лексемы из начала очереди
 *
 *          Аргументы:
 *  Queue *q - очередь из начала которой нужно получить лексему
 *  int *op - указатель на переменную, в которую надо записать ID лексемы (см. defines.h)
 *  double value - указатель на переменную, в которую надо записать значение лексемы
 *      (в случае если лексема хранит число)
 *          Возвращает:
 *  int result - 1 если лексема была получена успешно, 0 если очередь была пуста
**************************************************************************************************/
int pop_queue(Queue *q, int *op, double *value);

/**************************************************************************************************
 *  Функция уничтожения очереди (освобождает память)
 *
 *          Аргументы:
 *  Queue *q - очередь которую надо уничтожить
**************************************************************************************************/
void destroy_queue(Queue *q);

/**************************************************************************************************
 *  Функция уничтожения очереди (освобождает память)
 *
 *          Аргументы:
 *  Queue *q - очередь которую надо уничтожить
**************************************************************************************************/
Queue *clone_queue(Queue *from);

/**************************************************************************************************
 *  Тип данных: Стэк
 *
 *          Поля:
 *  struct QNode *last - первый на выход элемент стэка
**************************************************************************************************/
typedef struct {
    struct QNode *last;
} Stack;

/**************************************************************************************************
 *  Функция создания стэка
 *
 *          Возвращает:
 *  Stack *result - пустой стэк без нод
**************************************************************************************************/
Stack *init_stack();

/**************************************************************************************************
 *  Функция вставки лексемы в конец стэка
 *
 *          Аргументы:
 *  Stack *s - стэк в конец которого надо вставить лексему
 *  int op - ID лексемы (см. defines.h)
 *  double value - значение лексемы (в случае если лексема хранит число)
**************************************************************************************************/
void push_stack(Stack *s, int op, double value);

/**************************************************************************************************
 *  Функция получения лексемы из конца стэка
 *
 *          Аргументы:
 *  Stack *s - стэк из конца которого нужно получить лексему
 *  int *op - указатель на переменную, в которую надо записать ID лексемы (см. defines.h)
 *  double value - указатель на переменную, в которую надо записать значение лексемы
 *      (в случае если лексема хранит число)
 *          Возвращает:
 *  int result - 1 если лексема была получена успешно, 0 если стэк был пуст
**************************************************************************************************/
int pop_stack(Stack *s, int *op, double *value);

/**************************************************************************************************
 *  Функция уничтожения стэка (освобождает память)
 *
 *          Аргументы:
 *  Stack *s - стэк который надо уничтожить
**************************************************************************************************/
void destroy_stack(Stack *s);

#endif  // SRC_STRUCTS_H_
