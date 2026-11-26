struct S_02025FF0 { u8 _0[0x18A8]; u8 b; };
extern struct S_02025FF0 gMainWorkspace;
extern u8 gTilemapPages[];
extern u8 gGameStatus[];
extern u8 gCameraState[];
extern s32 sub_0805F9B4(s32, s32);
extern s32 sub_08016238(void *);
extern void sub_0800479C(void *, s32, s32, u16);
extern void sub_08007E24(u16);
extern void sub_08005E80(s32);
extern void sub_080C31E0(void *, void *);
extern void sub_080C31E8(void *, void *, s32, s32);
extern void *D_08671BDC;
void sub_08090C78(u8 *arg0)
{
  u8 *base;
  s16 v;
  u8 *self = arg0;
  u8 *p;
  u16 *w;
  u32 zero;
  u8 *r10;
  void *sp0;
  s16 *new_var;
  sp0 = *((void **) (self + 0x38));
  w = *((u16 **) (self + 0xAC));
  p = *((u8 **) (self + 0x3C));
  if (sub_0805F9B4(*((s32 *) (p + 8)), *((s32 *) (p + 0xC))) == 1)
  {
    *((u8 *) ((*((u8 **) p)) + 1)) = 0;
    return;
  }
  *((u8 *) ((*((u8 **) p)) + 1)) = 4;
  if (sub_08016238(*((void **) p)) != 0)
  {
    *((u16 *) (p + 0x10)) = 1;
  }
  {
    u8 q = *((u8 *) (((((u32) (*((s16 *) (self + 0x22)))) * 2) + ((u32) self)) + 0x1A));
    r10 = self + 0x18;
    if (q != 1)
    {
      v = *((s16 *) (p + 0x10));
      if (v == 1)
      {
        u32 *e;
        u16 t;
        u8 *pb = (u8 *) (&gMainWorkspace);
        base = gGameStatus;
        t = *w;
        zero = 0;
        *w = (t | 4) | zero;
        sub_0800479C(gTilemapPages + (((u32) (*(pb + 0x18A8))) << 6), (*((s32 *) (p + 8))) >> 21, (*((s32 *) (p + 0xC))) >> 21, *((u16 *) ((*((u8 **) (p + 0x14))) + 2)));
        sub_08007E24(*((u16 *) ((*((u8 **) (p + 0x14))) + 4)));
        e = (u32 *) ((base + 0xB0) + (((u32) ((*((u16 *) (*((u8 **) (p + 0x14))))) >> 5)) << 2));
        *e |= (u32) (v << ((*((u16 *) (*((u8 **) (p + 0x14))))) & 0x1F));
        sub_08005E80(0x70);
        *((u8 *) (((((u32) (*(new_var = &(*((s16 *) (self + 0x22)))))) * 2) + ((u32) self)) + 0x1B)) = zero;
        sub_080C31E8(r10, self + 0x22, 1, *((s32 *) 0x08671BDC));
      }
    }
  }
  *((void **) (self + 0x14)) = (void *) 0x0866F988;
  *((u16 *) (self + 0x22)) = (*((u16 *) (self + 0x22))) + 1;
  *((u8 *) (((((u32) (*((s16 *) (self + 0x22)))) * 2) + ((u32) self)) + 0x19)) += 1;
  {
    u8 *q2 = r10 + (((u32) (*((s16 *) (self + 0x22)))) * 2);
    sub_080C31E0(self, *((void **) ((*((u8 **) (self + 0x14))) + ((*((u8 *) q2)) * 4))));
  }
  *((u16 *) (self + 0x22)) = (*((u16 *) (self + 0x22))) - 1;
  if (((*((u16 *) (self + 2))) & 0x8000) == 0)
  {
    u8 *pt = gCameraState;
    u8 *pb = (u8 *) (&gMainWorkspace);
    u8 *base1;
    u8 *base2;
    u32 idx;
    u32 mask;
    pb += 0x18A8;
    mask = 0xFFFF0000;
    idx = (((u32) (*pb)) + 1) * 0x40;
    base1 = pt + 0x1278;
    *((s32 *) (((u8 *) sp0) + 0x14)) = (*((s32 *) (p + 8))) - (((*((s32 *) (base1 + idx))) + 0x8000) & mask);
    idx = (((u32) (*pb)) + 1) * 0x40;
    base2 = pt + 0x127C;
    *((s32 *) (((u8 *) sp0) + 0x18)) = (*((s32 *) (p + 0xC))) - (((*((s32 *) (base2 + idx))) + 0xFFFF8000) & mask);
  }
}
