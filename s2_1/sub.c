#include <stdio.h>
#include <stdlib.h>
void text() { }
int main(void)
{
  //text
  printf("%p\n", &text);

  //data
  char *data;
  printf("%p\n", &data);

  //heap
  char *heap;
  heap = malloc(100);
  printf("%p\n", &heap);
  free(heap);

  //stack
  int stack;
  printf("%p\n", &stack);
}
