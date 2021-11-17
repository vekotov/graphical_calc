#include "stack.h"
#include <stdio.h>

#define MAXSIZE 100

static int sp = 0;              /* stack pointer */
static double values[MAXSIZE];  /* stack */

double push_queue(double number) {
  if ( sp < MAXSIZE )
    values[sp++] = number;
  else
    printf("Error: push on full stack.\n");
  return number;
}

double pop_queue() {
  if ( sp > 0 )
    return values[--sp];
  else {
    printf("Error: pop from empty stack.\n");
    destroy_queue();
    return 0;
  }
}

void destroy_queue() {
  sp = 0;
}