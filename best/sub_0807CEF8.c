extern u8 D_02025FF0[];
extern u8 D_02023130[];
extern u8 D_000018A8[];
extern u8 D_000018C2[];
extern u8 D_0000173A[];
extern u8 D_000014ED[];
extern s32 sub_0806D518(void *, void *, void *);
extern void sub_0808DBF8(s32, s32, s32);
extern s16 sub_080C364C(s32, s16);
extern void sub_08003740(void *, void *);
extern void sub_0806D588(void *, void *);
extern void sub_0806D2F8(void *, void *);
extern void _call_via_r1(u32, u32);
extern s32 sub_08007DD8(u32, s32);
void sub_0807CEF8(void *arg0)
{
  u8 *r9 = (u8 *) arg0;
  u8 *r8 = *((u8 **) (r9 + 0x6C));
  u32 *new_var3;
  u8 *r6 = r8 + 4;
  long long new_var2;
  u8 *r7 = *((u8 **) (r9 + 0x38));
  u8 *r5;
  s32 r2;
  s32 *new_var;
  if (sub_0806D518(arg0, r7, r6) != 0)
  {
    return;
  }
  if ((*((s16 *) (r7 + 4))) > 0x100)
  {
    *((u16 *) (r7 + 4)) -= 0x80;
    *((u16 *) (r7 + 6)) -= 0x80;
    {
      s16 v = *((s16 *) (r7 + 4));
      u32 c = 0x80 << 3;
      r5 = *((u8 **) (r6 + 0x2C));
      *((u16 *) (r5 + 6)) = sub_080C364C(c, v);
    }
    {
      s16 v = *((s16 *) (r7 + 6));
      r5 = *((u8 **) (r6 + 0x2C));
      *((u16 *) (r5 + 8)) = sub_080C364C(0x80 << 3, v);
    }
  }
  new_var = (s32 *) (r6 + 4);
  *((s32 *) (r6 + 0xC)) += 0x4000;
  if ((*((s32 *) (r6 + 0xC))) > 0x80000)
  {
    *((s32 *) (r6 + 0xC)) = 0x80000;
  }
  *((s32 *) (r8 + 4)) += *((s32 *) (r6 + 8));
  new_var3 = (s32 *) (r6 + 0xC);
  r2 = *new_var;
  r2 = r2 + (*new_var3);
  *new_var = r2;
  new_var2 = 0;
  if (*((u16 *) ((*((u8 **) (r6 + 0x2C))) + 0x14)))
  {
    sub_0808DBF8(*((s32 *) (r8 + 4)), r2, 0);
    _call_via_r1((u32) r9, *(new_var3 = (u32 *) (r9 + 0x24)));
    return;
  }
  r2 = ((u32) D_02025FF0) + ((u32) D_000018A8);
  r2 = ((*((u8 *) r2)) << 6) + ((u32) D_02023130);
  if ((sub_08007DD8(r2, *((s32 *) (r8 + 4))) << 0x10) != 0)
  {
    sub_0808DBF8(*((s32 *) (r8 + 4)), *new_var, 0);
    _call_via_r1((u32) r9, *new_var3);
  }
  else
  {
    r2 = (u32) D_000018C2;
    *((u16 *) (r7 + new_var2)) = *((u16 *) (((u32) D_02025FF0) + r2));
    sub_08003740(r8 + 0x20, r7);
    sub_0806D588(r7, r6);
    if (((*((u8 *) (((u32) D_02025FF0) + ((u32) D_0000173A)))) == 0x1C) || (((*((u8 *) (((u32) D_02025FF0) + ((u32) D_000014ED)))) == 0) && ((*((u32 *) (((u8 *) D_02025FF0) + 0x10))) != 0)))
    {
      _call_via_r1((u32) r9, *new_var3);
      return;
    }
    sub_0806D2F8(arg0, r7);
  }
}

