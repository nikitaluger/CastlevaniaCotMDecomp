extern u8 gMainWorkspace[];
extern s32 sub_0806D450(void *, void *, void *);
extern void *sub_0806D2A0(s32, s32, s32, s32);
extern void sub_08003740(void *, void *);
extern void sub_08005E80(s32);
extern void _call_via_r1(void *, void *);
void sub_08081AE8(void *arg0)
{
  u8 *r5;
  u8 *r8;
  u8 *r6;
  u8 *r4;
  unsigned char off;
  s32 v;
  void *obj;
  u8 *new_var;
  s32 temp;
  r5 = (u8 *) arg0;
  r8 = (*((u8 **) (r5 + 0x6C))) + 4;
  r6 = *((u8 **) (r5 + 0x38));
  r4 = r8;
  if (sub_0806D450(r5, r6, r4) > 0)
  {
    _call_via_r1(r5, *((void **) (r5 + 0x24)));
    return;
  }
  *((s32 *) (r4 + 0x10)) -= 1;
  *((s32 *) (r6 + 0x14)) += 0xFFFE8000;
  if (((*((s32 *) (r4 + 0x10))) & 3) == 0)
  {
    obj = sub_0806D2A0(*((s32 *) (r5 + 0x28)), 0x6D, 0x0A, 0x12);
    if (obj != NULL)
    {
      temp = (*((s32 *) (r4 + 0x10))) >> 2;
      *((s32 *) (((u8 *) obj) + 0x9C)) = temp;
    }
  }
  new_var = gMainWorkspace;
  if ((*((s32 *) (r4 + 0x10))) == 0)
  {
    _call_via_r1(r5, *((void **) (r5 + 0x24)));
    return;
  }
  off = 0x18C2;
  *((u16 *) r6) = *((u16 *) (new_var + off));
  do { sub_08003740(r8 + 0x1C, r6); } while (0);
  *((s32 *) (r4 + 0x14)) -= 1;
  if ((*((s32 *) (r4 + 0x14))) == 0)
  {
    sub_08005E80(0x15E);
    *((s32 *) (r4 + 0x14)) = 0x1E;
  }
  off = 0x173A;
  if ((*((u8 *) (gMainWorkspace + off))) != 0x1C)
  {
    off = 0x14ED;
    if ((*((u8 *) (new_var + off))) != 0)
    {
      return;
    }
    if ((*((u32 *) (new_var + 0x10))) == 0)
    {
      return;
    }
  }
  _call_via_r1(r5, *((void **) (r5 + 0x24)));
}

