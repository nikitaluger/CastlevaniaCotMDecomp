extern s32 sub_080C36E4(s32, s32);
extern void *sub_08016238(void *);
extern s32 sub_080133EC(s32, s32, s32);
extern u16 sub_0806D5C4(s32, s32);
extern u16 sub_0806D5F8(s32, s32);
extern void sub_0808D7BC(s32, s32, s32, s32);
extern void sub_080158BC(void *, void *);
void *sub_08014F14(u16 *arg0, u8 *arg1, u8 *arg2, u8 *arg3)
{
  u16 cnt16;
  s32 r;
  u8 *new_var;
  s32 idx;
  u16 n;
  void *e;
  u8 *o;
  s32 t4;
  s32 t1 = 0;
  *((u16 *) arg1) &= 0xFFFD;
  *((u16 *) (arg2 + 4)) &= 0xFDFF;
  *((u16 *) (arg3 + 4)) &= 0xFDFF;
  if ((*((u16 *) arg1)) & 1)
  {
    *((u8 *) (arg2 + 1)) &= 0xFA;
    *((u8 *) (arg3 + 1)) &= 0xFA;
    return NULL;
  }
  idx = *((s16 *) (arg1 + 0x20));
  cnt16 = *((u16 *) (arg1 + 0x20));
  if (idx > 0)
  {
    r = sub_080C36E4(idx, 3);
    {
      s32 rs = (s16) r;
      r = rs;
    }
    if (r == 0)
    {
      *arg0 = ((*arg0) & 0xFFF) | 0xD000;
    }
    else
      if (r == 1)
    {
      *arg0 = ((*arg0) & 0xFFF) | 0xC000;
    }
    *((u16 *) (arg1 + 0x20)) = cnt16 - 1;
    *((u16 *) (arg2 + 4)) |= 0x200;
    *((u16 *) (arg3 + 4)) |= 0x200;
    sub_08016238(arg2);
    sub_08016238(arg3);
    return NULL;
  }
  if ((!((*((u8 *) (arg2 + 1))) & 4)) && (!((*((u8 *) (arg3 + 1))) & 4)))
  {
    return NULL;
  }
  ;
  if ((((((*((s16 *) (0x02025FF0 + 0x18BE))) != 0) && ((*((s16 *) ((0x080CBDD0 + (((*((s16 *) (arg1 + 0x1C))) * 10) * 4)) + 2))) != 0)) && ((*((void **) (arg1 + 0x30))) != NULL)) && ((*((u16 *) ((*((u32 *) (arg1 + 0x30))) + 2))) & 1)) && (sub_080133EC(*((s32 *) (arg1 + 8)), (*((s32 *) (arg1 + 0xC))) + 0x10000, 0x10000) == 1))
  {
    n = sub_0806D5C4(*((u16 *) (0x02025FF0 + 0x18BE)), *((u16 *) ((0x080CB2B8 + (idx * 20)) + 6)));
    if (((s32) n) <= 0)
    {
      n = 1;
    }
    *((s32 *) (arg1 + 0x18)) -= n;
    *((u16 *) arg1) |= ((*((s32 *) (arg1 + 0x18))) <= 0) ? (1) : (2);
    new_var = arg1 + 0x20;
    *((u16 *) new_var) = 0x1E;
    return NULL;
  }
  e = sub_08016238(arg2);
  if (e == NULL)
  {
    e = sub_08016238(arg3);
    if (e == NULL)
    {
      return NULL;
    }
    o = arg3;
  }
  else
  {
    o = arg2;
  }
  t4 = (*((u16 *) (((u8 *) e) + 0x2A))) & 0xF;
  t1 = (*((u16 *) (((u8 *) o) + 0x2A))) & 0xF;
  n = sub_0806D5F8(*((u16 *) (((u8 *) e) + 0x2C)), *((u16 *) ((0x080CB2B8 + (idx * 20)) + 6)));
  if ((t1 != 0) && (t4 == t1))
  {
    n = ((u16) n) >> 1;
  }
  if (n == 0)
  {
    n = 1;
  }
  if (n > 0x270F)
  {
    n = 0x270F;
  }
  *((s32 *) (arg1 + 0x18)) -= n;
  {
    s32 p30 = *((s16 *) (((u8 *) o) + 0x30));
    u32 tab = *((u32 *) ((0x02021E90 + 0x1278) + (((*((u8 *) (0x02025FF0 + 0x18A8))) + 1) << 6)));
    s32 x = ((p30 << 16) + 0x8000) + tab;
    long long tab2 = *((u32 *) ((0x02021E90 + 0x127C) + (((*((u8 *) (0x02025FF0 + 0x18A8))) + 1) << 6)));
    s32 y = ((((*((s16 *) (((u8 *) o) + 0x32))) << 16) - 0x8000) + tab2) - ((*((s16 *) (((u8 *) o) + 0x28))) << 16);
    if ((*((s16 *) (((u8 *) e) + 0x30))) >= p30)
    {
 do { x += (*((s16 *) (((u8 *) o) + 0x26))) << 16; } while (0);
    }
    else
    {
      x -= (*((s16 *) (((u8 *) o) + 0x26))) << 16;
    }
    sub_0808D7BC(x, y, n, 0);
  }
  if ((*((void **) (arg1 + 0x30))) != NULL)
  {
    *((void **) ((*((u32 *) (arg1 + 0x30))) + 8)) = e;
  }
  if ((*((s32 *) (arg1 + 0x18))) <= 0)
  {
    u32 fl = 1;
    if (t4 == 2)
    {
      if ((!((*((u16 *) arg1)) & 0xC)) && (t1 != 2))
      {
        *((s32 *) (arg1 + 0x18)) = 1;
        fl = 4;
      }
      else
      {
        *((s32 *) (arg1 + 0x18)) = 0;
        fl = 1;
      }
    }
    else
      if (t4 == 5)
    {
      if ((!((*((u16 *) arg1)) & 0xC)) && (t1 != 5))
      {
        *((s32 *) (arg1 + 0x18)) = 1;
        fl = 8;
      }
      else
      {
        fl = 1;
      }
      *((s32 *) (arg1 + 0x18)) = 0;
    }
    else
    {
      *((s32 *) (arg1 + 0x18)) = 0;
    }
    *((u16 *) arg1) |= fl;
  }
  else
  {
    *((u16 *) arg1) |= 2;
  }
  {
    s16 v = *((s16 *) (((u8 *) e) + 0x2E));
    *((u16 *) (arg1 + 0x20)) = (v) ? (v) : (0x1E);
  }
  sub_080158BC(arg1, e);
  return e;
}
