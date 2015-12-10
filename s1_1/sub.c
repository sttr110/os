#include <stdio.h>
#include <string.h>

char name[] = "kawamura";
int age = 20;

void func(char *fname) {
  FILE *fp;
  fp = fopen(fname, "w");
  fprintf(fp, "%s\n", name);
  fprintf(fp, "%d\n", age);
  fclose(fp);
}

int main(void) {
  char fname[124];

  scanf("%s", fname);
  func(fname);
  return 0;
}

