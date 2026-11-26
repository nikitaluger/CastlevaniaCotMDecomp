extern void sub_08003740(void *, s32);
extern unsigned short sub_08007B3C(s32, s32, s32);
extern void sub_0806A7AC(s32, void *, s32);
extern s32 sub_0806B2C8(s32, s32, void *, void *);
extern void sub_0806C49C(s32, void *);
struct S_02025FF0 {
  u8 _0[0x24];
  u32 f24;
  u8 _1[0x2A - 0x28];
  u16 f2A;
  u8 _2[0x18A8 - 0x2C];
  u8 f18A8;
};
extern struct S_02025FF0 gMainWorkspace;
struct S_02021E90 { u8 _0[0x146E]; u16 f146E; };
extern struct S_02021E90 gCameraState;
extern u8 gTilemapPages[];
struct S_arg2 {
  u8 _0[0x38];
  s32 f38;
  u8 _1[4];
  s32 f40;
  u8 _2[4];
  s32 f48;
  u8 _3[0xC4 - 0x4C];
  s32 fC4;
};
struct S_arg3 { s32 f0; s32 f4; s32 f8; };
static inline u32 and80(u32 b)
{
  u32 m = 0x80;
  m &= b;
  return m;
}
u16 sub_08065CC8(s32 arg0, s32 arg1, struct S_arg2 *arg2, struct S_arg3 *arg3)
{
  u32 v;
  s32 r;
  s32 *pC4;
  arg2->f48 = 0;
  if (gMainWorkspace.f24 != 0) v = gMainWorkspace.f2A;
  else v = gCameraState.f146E;
  if (and80(v)) goto fail;
  if ((sub_08007B3C((s32)(gTilemapPages + gMainWorkspace.f18A8 * 0x40), arg3->f0, arg3->f4 + 0x10000) & 0x4000) ||
      (sub_08007B3C((s32)(gTilemapPages + gMainWorkspace.f18A8 * 0x40), arg3->f0 - arg2->f38, arg3->f4 + 0x10000) & 0x4000) ||
      (sub_08007B3C((s32)(gTilemapPages + gMainWorkspace.f18A8 * 0x40), arg3->f0 + arg2->f38, arg3->f4 + 0x10000) & 0x4000)) goto fail;
  arg2->f40 = 1;
  sub_0806C49C(arg1, arg2);
  r = sub_0806B2C8(arg0, arg1, arg2, arg3);
  pC4 = (s32 *)((u8 *)arg2 + 0xC4);
  *pC4 = r;
  if (r != 0) {
    sub_08003740((u8 *)arg2 + 0x28, arg1);
    return (u16)*pC4;
  }
  sub_08003740((u8 *)arg2 + 0x28, arg1);
  return 4;
fail:
  arg2->f40 = 2;
  sub_0806A7AC(arg1, arg2, 5);
  sub_08003740((u8 *)arg2 + 0x28, arg1);
  arg3->f8 = 0;
  return 8;
}
