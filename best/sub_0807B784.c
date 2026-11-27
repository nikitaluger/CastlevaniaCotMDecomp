extern void stepDelayTimer(void *, void *);
extern void playSound(s32);
extern void *sub_08016A2C(void);
extern void cullOffscreenEntity(void *, void *);
extern s32 checkGlobalStateChange(void *, void *, void *);
extern void setSpriteScreenPosition(void *, void *);
extern void sub_080C31E0(void *, s32);
extern void sub_080C31E8(void *, void *, s32, s32);
extern s16 divInt32(s32, s16);
extern u8 gMainWorkspace[];
void sub_0807B784(void *arg0)
{
  void *r9;
  void *r6;
  void *r8;
  s32 tr;
  s32 t;
  void *r4;
  s16 idx;
  u8 *ptr;
  s16 idx2;
  u8 *p;
  s16 idx3;
  u8 *r4b;
  u8 byte;
  void *p14;
  s32 fn;
  void *r3;
  u16 h;
  s16 sh;
  void *r5;
  s16 val;
  void *r5b;
  s16 val2;
  s32 v;
  s32 m;
  s32 v2;
  s32 m2;
  void *t0;
  u8 b1;
  u8 b2;
  u8 byte2;
  s32 *dp1;
  s32 *dp2;
  u32 a1;
  u32 a2;
  u32 a3;
  r9 = *((void **) (((u8 *) arg0) + 0x6C));
  r6 = ((u8 *) r9) + 4;
  r8 = *((void **) (((u8 *) arg0) + 0x38));
  tr = checkGlobalStateChange(arg0, r8, r6);
  if (tr != 0)
  {
    return;
  }
  t = (*((s32 *) (((u8 *) r6) + 0x14))) - 1;
  *((s32 *) (((u8 *) r6) + 0x14)) = t;
  if (t == 0)
  {
    playSound(0x144);
  }
  t = (*((s32 *) (((u8 *) r6) + 0x48))) - 1;
  *((s32 *) (((u8 *) r6) + 0x48)) = t;
  if (t == 0)
  {
    *((u8 *) (((u8 *) (*((void **) (((u8 *) r6) + 0x2C)))) + 1)) = tr;
    a1 = (s16)(*((s16 *) (((u8 *) arg0) + 0x22)));
    a1 <<= 1;
    a1 += (u32)arg0;
    ptr = (u8 *)a1;
    ptr[0x19] = tr;
    dp1 = (s32 *) 0x08671BD0;
    r4 = ((u8 *) arg0) + 0x18;
    sub_080C31E8(r4, ((u8 *) arg0) + 0x22, 4, *dp1);
    a2 = (s16)(*((s16 *) (((u8 *) arg0) + 0x22)));
    a2 <<= 1;
    a2 += (u32)arg0;
    p = (u8 *)a2;
    p[0x19] = p[0x19] + 1;
    idx3 = *((s16 *) (((u8 *) arg0) + 0x22));
    r4b = (idx3 * 2) + r4;
    byte = *r4b;
    p14 = *((void **) (((u8 *) arg0) + 0x14));
    fn = *((s32 *) (((u8 *) p14) + (byte * 4)));
    goto do_call;
  }
  r3 = r8;
  h = *((u16 *) (((u8 *) r3) + 4));
  sh = *((s16 *) (((u8 *) r3) + 4));
  if (sh > 0x100)
  {
    *((u16 *) (((u8 *) r3) + 4)) = h - 0x40;
    r5 = *((void **) (((u8 *) r6) + 0x2C));
    *((u16 *) (((u8 *) r3) + 6)) = (*((u16 *) (((u8 *) r3) + 6))) - 0x40;
    val = *((s16 *) (((u8 *) r3) + 4));
    *((s16 *) (((u8 *) r5) + 6)) = divInt32(0x1600, val);
    r5b = *((void **) (((u8 *) r6) + 0x2C));
    val2 = *((s16 *) (((u8 *) r3) + 6));
    *((s16 *) (((u8 *) r5b) + 8)) = divInt32(0x1600, val2);
  }
  v = (*((s32 *) (((u8 *) r6) + 0x40))) >> 8;
  m = (*((s32 *) (((u8 *) r6) + 0x08))) * v;
  if (m < 0)
  {
    m += 0xFF;
  }
  *((s32 *) (((u8 *) r9) + 4)) = (*((s32 *) (((u8 *) r9) + 4))) + (m >> 8);
  v2 = (*((s32 *) (((u8 *) r6) + 0x40))) >> 8;
  m2 = v2 * (*((s32 *) (((u8 *) r6) + 0x0C)));
  if (m2 < 0)
  {
    m2 += 0xFF;
  }
  *((s32 *) (((u8 *) r6) + 4)) = (*((s32 *) (((u8 *) r6) + 4))) + (m2 >> 8);
  setSpriteScreenPosition(r8, r6);
  stepDelayTimer(((u8 *) r9) + 0x20, r8);
  t0 = sub_08016A2C();
  if (t0 != NULL)
  {
    *((void **) (((u8 *) r6) + 0x4C)) = t0;
    byte2 = *((u8 *) (((u8 *) t0) + 1));
    *((u8 *) (((u8 *) r9) + 0x54)) = byte2;
    *((u8 *) (((u8 *) r9) + 0x49)) = 2;
    a3 = (s16)(*((s16 *) (((u8 *) arg0) + 0x22)));
    a3 <<= 1;
    a3 += (u32)arg0;
    ptr = (u8 *)a3;
    ptr[0x19] = 0;
    dp2 = (s32 *) 0x08671BD0;
    sub_080C31E8(((u8 *) arg0) + 0x18, ((u8 *) arg0) + 0x22, 3, *dp2);
  }
  b1 = gMainWorkspace[0x173A];
  if (b1 == 0x1C)
  {
    goto do_call2;
  }
  b2 = gMainWorkspace[0x14ED];
  if (b2 == 0)
  {
    if ((*((s32 *) (gMainWorkspace + 0x10))) != 0)
    {
      goto do_call2;
    }
  }
  goto do_success;
  do_call2:
  fn = *((s32 *) (((u8 *) arg0) + 0x24));

  do_call:
  sub_080C31E0(arg0, fn);
  return;
  do_success:
  cullOffscreenEntity(arg0, r8);

}
