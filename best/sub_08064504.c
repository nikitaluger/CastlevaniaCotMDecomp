extern s32 sub_0806C4B4(void *, void *);
extern void sub_0806C5EC(void *, void *, void *, void *);
extern void sub_08005E80(s32);
extern void sub_0806A7AC(void *, void *, s32);
extern void sub_0806AB04(void *, void *, void *, void *);
extern void sub_0806A884(void *, void *);
extern u16 sub_0806BCD8(void *, void *, void *, void *);
extern s32 sub_08003740(void *, void *);
extern void sub_0806C6B0(void *, void *, void *, void *);
extern void sub_080C31E8(void *, void *, s32, s32);
extern u8 gGameStatus[];
extern u8 gMainWorkspace[];
extern u8 gCameraState[];
extern u16 D_080DFC3C[];
extern s32 D_08671BD0[];
void sub_08064504(u8 *arg0)
{
  u8 *r6;
  u8 *r8ptr;
  u8 *r7;
  u8 *r5base;
  s32 off146E = 0x146E;
  r6 = (*((u8 **) (arg0 + 0x6C))) + 4;
  r8ptr = *((u8 **) (arg0 + 0x38));
  r7 = r6;
  r5base = (u8 *) 0x02025368;
  if (sub_0806C4B4(r7, r7) != 0)
  {
    return;
  }
  sub_0806C5EC(arg0, r8ptr, r7, r7);
  if (((*((u32 *) (r7 + 0x74))) & 7) == 0)
  {
    s32 off = 0x14EE;
    u8 val = *((u8 *) (gMainWorkspace + off));
    s32 s = 0x6C;
    if (val == 0x58)
    {
      s = 0xEE;
    }
    sub_08005E80(s);
  }
  *((u32 *) (r7 + 0x74)) = (*((u32 *) (r7 + 0x74))) + 1;
  {
    u16 *tbl = D_080DFC3C + ((*((u16 *) (r6 + 0x2C))) << 2);
    u8 * volatile *pp = (u8 * volatile *) (r6 + 0x130);
    *((u16 *) ((*pp) + 0x06)) = tbl[0];
    *((u16 *) ((*pp) + 0x08)) = tbl[1];
    *((u16 *) ((*pp) + 0x0A)) = tbl[2];
    *((u16 *) ((*pp) + 0x0C)) = tbl[3];
    {
      s32 off1510 = 0x1510;
      *((u8 *) ((*pp) + 0x01)) = (*((u8 *) (gMainWorkspace + off1510))) & 1;
    }
  }
  if (((*((u32 *) (gMainWorkspace + 0x24))) != 0) ? (((*((u16 *) (gMainWorkspace + 0x2A))) & (*((u16 *) (r5base + 0x3BC)))) == 0) : (((*((u16 *) (gCameraState + off146E))) & (*((u16 *) (r5base + 0x3BC)))) == 0))
  {
    s32 *nv;
    sub_0806A7AC(r8ptr, r6, 5);
    {
      s16 idx = *((s16 *) (arg0 + 0x22));
      *((u8 *) ((arg0 + (idx * 2)) + 0x19)) = 0;
    }
    nv = D_08671BD0;
    sub_080C31E8(arg0 + 0x18, arg0 + 0x22, 8, *nv);
  }
  sub_0806AB04(arg0, r8ptr, r6, r7);
  if (((*((u32 *) (r6 + 0x40))) == 0) && ((*((u32 *) (r6 + 0x4C))) == 0))
  {
    s32 *nv;
    sub_0806A7AC(r8ptr, r6, 0x10);
    {
      s16 idx = *((s16 *) (arg0 + 0x22));
      *((u8 *) ((arg0 + (idx * 2)) + 0x19)) = 0;
    }
    nv = D_08671BD0;
    sub_080C31E8(arg0 + 0x18, arg0 + 0x22, 3, *nv);
  }
  sub_0806A884(r8ptr, r7);
  {
    u32 res = sub_0806BCD8(arg0, r8ptr, r6, r7);
    *((u32 *) (r6 + 0xC4)) = (u16) res;
    if (((u16) res) != 0)
    {
      s32 *nv;
      s16 idx = *((s16 *) (arg0 + 0x22));
      *((u8 *) ((arg0 + (idx * 2)) + 0x19)) = 0;
      nv = D_08671BD0;
      sub_080C31E8(arg0 + 0x18, arg0 + 0x22, *((u32 *) (r6 + 0xC4)), *nv);
    }
  }
  sub_08003740(r6 + 0x28, r8ptr);
  sub_0806C6B0(arg0, r8ptr, r6, r7);
}
