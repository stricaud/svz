#include <stdio.h>

#include <svz/svz.h>

int main(void)
{
  svz_t *svz;
  svz = svz_new(10, 10);
  svz_free(svz);
}
