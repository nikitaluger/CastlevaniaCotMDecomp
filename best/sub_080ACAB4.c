struct E
{
  u8 _0[0x5C];
  s32 f5C;
  u8 _60[0x6C - 0x60];
  s32 f6C;
  u8 _70[0x7C - 0x70];
  s32 f7C;
};
struct Ctx
{
  u8 _0[4];
  struct E *ptrs[2];
  u8 _c[0x18 - 0xc];
  s32 vel[2];
  u8 _20[0x28 - 0x20];
  u8 flag28[4];
  u8 flag2C[1];
};
void sub_080ACAB4(u32 arg0, struct Ctx *arg1)
{
  u32 i;
  u32 j;
  s32 x1;
s32 __repair_phase_x1;
  
  s32 v;
  s32 delta;
  s32 tmp;
  u8 *temp;
  i = (u8) arg0;
  j = (i + 1) & 1;
  if (arg1->flag2C[i] == 0)
  {
    goto other;
  }
  do { x1 = arg1->ptrs[i]->f5C;
  if (x1 < (-0x1000))
  {
    goto other;
  } } while (0);
  temp = (u8 *) arg1 + j * 4;
  __repair_phase_x1 = (*(struct E **)(temp + 4))->f5C;
  if (__repair_phase_x1 < (-0x1000))
  {
    goto other;
  }
  
  if (arg1->flag28[j] != 0)
  {
    goto other;
  }
  delta = 0;
  v = arg1->vel[j];
  if (v > 0)
  {
    if (arg1->vel[i] < 0)
    {
      s32 tmp_a1;
      do { tmp_a1 = (-0x1000) - x1; } while (0);
      if (tmp_a1 < 0)
      {
        do { do { do { tmp_a1 = x1 + (0x80 << 5); } while (0); } while (0); } while (0);
      }
      do { __repair_phase_x1 = (*(struct E **)((u8 *) arg1 + (4 + j * 4)))->f5C + (0x80 << 5); } while (0);
      if (__repair_phase_x1 >= 0)
      {
        delta = (tmp_a1 + (0x80 << 5)) + (*(struct E **)((u8 *) arg1 + (4 + j * 4)))->f5C;
      }
      else
      {
        delta = (tmp_a1 - 0x1000) - (*(struct E **)((u8 *) arg1 + (4 + j * 4)))->f5C;
      }
      goto check;
    }
  }
  if (arg1->vel[j] < 0)
  {
    if (arg1->vel[i] > 0)
    {
      delta = (0x80 << 5) - arg1->ptrs[i]->f5C;
      if (delta < 0)
      {
        delta = arg1->ptrs[i]->f5C - 0x1000;
      }
      __repair_phase_x1 = (*(struct E **)((u8 *) arg1 + (4 + j * 4)))->f5C;
      tmp = __repair_phase_x1 - 0x1000;
      if (tmp >= 0)
      {
        delta = (delta - 0x1000) + __repair_phase_x1;
      }
      else
      {
        delta = (delta + (0x80 << 5)) - __repair_phase_x1;
      }
    }
  }
  check:
  if (((delta + (0x80 << 5)) - __repair_phase_x1) > 0x1FFF)
  {
    arg1->flag2C[i] = 0;
  }

  goto tail;
  other:
  arg1->ptrs[i]->f5C += arg1->vel[i];

  { v = arg1->vel[i]; }
  if (v > 0)
  {
    if (arg1->ptrs[i]->f5C > (0x80 << 5))
    {
      arg1->ptrs[i]->f5C = 0x80 << 5;
      do { arg1->vel[i] = -v; } while (0);
      goto tail;
    }
  }
  do { v = arg1->vel[i]; } while (0);
  if (v >= 0)
  {
    goto tail;
  }
  if (arg1->ptrs[i]->f5C < (-0x1000))
  {
do {
    arg1->ptrs[i]->f5C = -0x1000;
    do { arg1->vel[i] = -v; } while (0);
} while (0);
}
  tail:
  x1 = arg1->ptrs[i]->f6C;

  if (x1 < (-0x3800))
  {
    arg1->ptrs[i]->f6C = x1 + (0x80 << 1);
    if (arg1->ptrs[i]->f6C > (-0x3800))
    {
      arg1->ptrs[i]->f6C = -0x3800;
    }
  }
  else
    if (x1 > (-0x3800))
  {
    arg1->ptrs[i]->f6C = x1 - (0x80 << 1);
    if (arg1->ptrs[i]->f6C < (-0x3800))
    {
      arg1->ptrs[i]->f6C = -0x3800;
    }
  }
  do { __repair_phase_x1 = arg1->ptrs[i]->f7C; } while (0);
  do { if (__repair_phase_x1 <= 0x2FFF)
  {
    arg1->ptrs[i]->f7C = __repair_phase_x1 + (0x80 << 1);
    if (arg1->ptrs[i]->f7C > (0xC0 << 6))
    {
      arg1->ptrs[i]->f7C = 0xC0 << 6;
    }
  }
  else
  {
    if (__repair_phase_x1 > (0xC0 << 6))
    {
      arg1->ptrs[i]->f7C = __repair_phase_x1 - (0x80 << 1);
      if (arg1->ptrs[i]->f7C > 0x2FFF)
      {
        arg1->ptrs[i]->f7C = 0xC0 << 6;
      }
    }
  } } while (0);
}
