#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>


int my_write (int fd, void *buf, int size)
{
  int count = 0;
  char *buffer = buf;
  char *endp = buf + size;

  while (buffer < endp)
  {
    count = write (fd, buffer, endp - buffer);
    if (count < 0)
    {
      if (errno == EINTR)
        continue;
      else
        return -1;
    }
    buffer += count;
  }
  return size;
}

void myItoa (int n,char *s) {
  if(n){
    int i = 0;
    int l = n;
    while(l/=10){ i++; }
    myItoa(n/10,s);
    s[i] = n % 10 + '0';
    s[i+1] = '\0';
  }
}


main()
{
  int fd, size;
  int age = 21;
  char *name =  "kawamura";
  char *age_str;
  char fname[124];

  scanf("%s", fname);

  //数値を文字列に変換
  myItoa(age, age_str);

  fd = open(fname, O_WRONLY|O_CREAT|O_TRUNC, 0666);
  if (fd == -1)
  {
    printf("ファイルオープンエラー\n");
    return;
  }

  //名前の書き込み
  size = my_write (fd, name, sizeof (name));
  if (size != sizeof (name))
  {
    close (fd);
    return -1;
  }

  //年齢の書き込み
  size = my_write (fd, age_str, sizeof (age_str));
  if (size != sizeof (age_str))
  {
    close (fd);
    return -1;
  }

  if (fsync (fd) < 0)
  {
    close (fd);
    return -1;
  }

  close(fd);
}
