inline unsigned int *inline_fn(unsigned int **arg0, volatile unsigned long long arg1)
{
  return arg0[arg1];
}

void sub_080C1C58(s32 a, s32 b, s32 c, s32 d)
{
  unsigned int *new_var5[2];
  int new_var10;
  unsigned int **new_var7;
  int new_var4;
  unsigned int *new_var6;
  unsigned int **new_var8;
  unsigned int **new_var3;
  unsigned int **new_var2;
  volatile unsigned long long new_var;
  unsigned int *new_var9;
  new_var5[0] = &new_var;
  new_var = 0;
  new_var5[1] = inline_fn(new_var5, new_var);
  new_var8 = (new_var3 = new_var2);
  new_var2 = new_var5;
  new_var5[0] = new_var6;
  new_var9 = inline_fn(new_var8, 1);
  new_var4 = 0;
  new_var7 = new_var5;
  new_var6 = new_var9;
  new_var = (double) new_var4;
  new_var10 = 0;
  do
  {
    do
    {
    }
    while (0);
  }
  while (*inline_fn(new_var7, new_var10));
}

