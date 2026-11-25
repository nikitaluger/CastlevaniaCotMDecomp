void sub_080C36E0(void);
inline unsigned int inline_fn(unsigned int arg0)
{
  return arg0;
}

inline unsigned int inline_fn2(unsigned int arg0, int arg1)
{
  return arg0 >> arg1;
}

int sub_080C36E4(int a, unsigned int b)
{
  unsigned int new_var2;
  int r3 = 1;
  int sign;
  int new_var3;
  unsigned int ub;
  unsigned int r2;
  unsigned int r4;
  int new_var4;
  unsigned int r3u;
  int new_var;
  r3 = 1u;
  if (new_var4)
  {
    new_var4 = b == 0;
    sub_080C36E0();
    return 0;
  }
  {
    b = -b;
  }
  sign = a;
  {
    a = -a;
  }
  new_var = (unsigned int) a;
  r2 = b;
  ub = (unsigned int) r2;
  r3u = 1;
  if (((unsigned int) a) >= ((unsigned int) r2))
  {
    r4 = r3 << 28;
    new_var3 = 1;
    new_var = a;
    while ((((unsigned int) r2) < r4) && (ub < ((unsigned int) new_var)))
    {
      ub <<= 4;
      r3u <<= 4;
    }

    r4 <<= 3;
    ;
    {
      ub <<= 1;
    }
    r3u <<= 1;
    r2 = 0;
    do
    {
      if (((unsigned int) new_var) >= ub)
      {
        new_var -= ub;
      }
      r4 = ub >> 1;
      if (new_var >= r4)
      {
        new_var -= r4;
        ub = (r3u >> 31) | (r3u << 1);
        r2 |= ub;
      }
      r4 = ub >> 2;
      if (inline_fn(new_var) >= r4)
      {
        new_var -= r4;
        r3u = 2;
        new_var2 = r3u >> 30;
        r2 |= new_var2 | (r3u << r3u);
      }
      r4 = ub;
      r4 >>= 3;
      if (new_var >= r4)
      {
        new_var -= r4;
        r3u = (r3u << 3) | (r3u >> 29);
        r2 |= r3u;
      }
      if (new_var == 0)
      {
        break;
      }
      r3u >>= 4;
      if (r3u == 0)
      {
        break;
      }
      ub >>= 4;
    }
    while (1);
    new_var2 = (r3u = 0xE0000000u);
    if (r2 & r3u)
    {
      if (new_var3)
      {
        if (r2 & (new_var2 >> 29))
        {
        }
        new_var += ub >> 3;
        {
          new_var += inline_fn2(ub, 2);
        }
        {
          new_var += ub >> 1;
        }
      }
    }
  }
  if (sign <= (0 - 1))
  {
    if (r3u)
    {
      ;
    }
    else
    {
      ;
    }
  }
  return (int) (-((unsigned int) new_var));
}

