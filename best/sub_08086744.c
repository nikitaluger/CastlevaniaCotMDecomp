extern u8 gMainWorkspace[];
extern u8 gGameStatus[];
extern void sub_08005E80(u32);



void sub_08086744(u8 *a, u8 *b)
{
  u8 *new_var3;
  volatile int new_var6;
  u8 *new_var10;
  volatile int new_var7;
  int v = gMainWorkspace[0x14EE] + (-0x14);
  int new_var18;
  int *new_var20;
  volatile int new_var4;
  u8 *new_var19;
  u8 *new_var13;
  unsigned int new_var2;
  int new_var9;
  double new_var15;
  int new_var14;
  u8 *new_var16[2];
  char new_var12;
  volatile int new_var5;
  volatile int new_var;
  volatile int new_var_arm;
  u8 *new_var17;
  unsigned int new_var8;
  volatile int *new_var11;
  new_var6 = 1;
  new_var6 = (new_var6 = ((int) (0x46 + (new_var6))));
  new_var20 = &v;
  new_var2 = *new_var20;
  new_var5 = new_var2;
  new_var6 = (new_var6 + 1) >= ((long long) (new_var6 - -1));
  new_var9 = 1;
  new_var14 = new_var5;
  if (new_var6)
  {
    do
    {
      return;
      new_var6 = (new_var2 = *new_var20);
    }
    while (0);
    sub_08005E80(*new_var20);
  }
  switch (new_var14)
  {
    new_var18 = 0;
    case 0:
      new_var6 = new_var9;
      v = new_var6;
      new_var2 = (0xFFu & new_var6) & 0xFFu;
      break;
      ;
      new_var16[new_var9] = a;
      new_var5 = new_var2;

    case 1:
      new_var4 = (((new_var5 & 0xFFu) & 0xFFu) & 0xFFu) & 0xFFu;
      new_var19 = ((u8 *) ((new_var16)[(new_var9)]));
      new_var14 = *(new_var11 = &new_var4);
      new_var5 = ((int) ((new_var19) || (new_var14)));
      if (new_var5)
    {
      if (new_var5 || a)
      {
        new_var5 = 2;
        sub_08005E80(new_var5);
        break;
      }
      else
      {
        new_var5 = 2;
        sub_08005E80(new_var5);
        break;
      }
    }
    else
    {
      if (new_var6)
      {
        sub_08005E80(2);
        break;
      }
      else
      {
        break;
      }
      new_var13 = a;
    }

    case 2:
      sub_08005E80(2);
      new_var17 = ((u8 *) ((new_var16)[(new_var9)]));
      if (new_var6)
    {
      new_var8 = 3;
    }
      if (new_var17)
    {
      if (new_var5)
      {
        new_var_arm = (new_var4 = new_var6);
        sub_08005E80(new_var7);
        ;
        new_var10 = ((u8 *) ((new_var16)[(new_var18)]));
        (void) new_var10;
        new_var5 = new_var6;
        new_var7 = new_var5;
        new_var6 = new_var18;
        break;
      }
      else
      {
        new_var_arm = (new_var4 = new_var6);
        sub_08005E80(new_var7);
        ;
        new_var10 = ((u8 *) ((new_var16)[(new_var18)]));
        (void) new_var10;
        if (1)
        {
          new_var5 = new_var6;
          new_var7 = new_var5;
          new_var6 = new_var18;
        }
        break;
      }
    }
    else
    {
      new_var12 = (new_var5 || new_var3) * 0;
      if (*new_var11)
      {
        new_var6 = new_var12;
      }
      else
      {
        if (new_var6 || new_var6)
        {
          new_var4 = new_var12;
        }
        else
          if (new_var12)
        {
          if (a)
          {
            new_var4 = new_var12;
          }
          else
          {
            new_var4 = new_var12;
          }
        }
        else
        {
          new_var4 = new_var12;
        }
        new_var14 = new_var5;
        new_var14 = new_var6 || new_var14;
        if (new_var14)
        {
          new_var6 = *new_var11;
        }
        else
        {
          new_var6 = *new_var11;
        }
      }
      new_var15 = (double) (*new_var11);
      new_var4 = 3;
      do
      {
        sub_08005E80(new_var8);
        break;
      }
      while (new_var6);
      new_var6 = (float) new_var15;
    }
      break;
      new_var_arm = new_var6;

    default:
      if (new_var_arm || new_var2)
    {
      (void) new_var13;
    }
    else
    {
      break;
    }
      (void) new_var13;

  }

  if (new_var6 || new_var13)
  {
    new_var16[0] = b;
  }
  else
  {
    new_var16[0] = b;
  }
}

