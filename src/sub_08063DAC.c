extern s32 sub_0806C4B4(u8 *, u8 *);
extern void sub_0806C5EC(u8 *, s32, u8 *, u8 *);
extern void sub_08086744(u8 *, u8 *, u8 *, s32);
extern void sub_0806AB04(u8 *, s32, u8 *, u8 *);
extern void sub_0806A884(s32, u8 *);
extern s32 sub_08003740(u8 *, s32);
extern void sub_0806A7AC(s32, u8 *, s32);
extern void sub_08085398(u8 *, u8 *);
extern void sub_08086648(s32, u8 *, s32);
extern void sub_08086D58(u8 *, s32);
extern u16 sub_0806BCD8(u8 *, s32, u8 *, u8 *);
extern s32 _call_via_r3(u8 *, u8 *, s32, s32);
extern void sub_0806C6B0(u8 *, s32, u8 *, u8 *);
struct S_02025FF0 { u8 _0[0x24]; u32 f24; u8 _28[2]; u16 f2A; u8 _2C[0x1514-0x2C]; u32 f1514; };
extern struct S_02025FF0 D_02025FF0;
struct S_02021E90 { u8 _0[0x146E]; u16 f146E; };
extern struct S_02021E90 D_02021E90;
struct S_02025368 { u8 _0[0x3BC]; u16 f3BC; };
extern struct S_02025368 D_02025368;
inline static u32 zeroU32(void) { u32 v = 0; return v; }
inline static u8 zeroU8(void) { u8 v = 0; return v; }
void sub_08063DAC(u8 *arg0)
{
  u8 *r6; s32 r7; u8 *r8; s32 r4; u8 *r9; u8 *q28; s32 ret; u16 r0; u8 *b53; s32 v4c; s32 z;
  r6 = *(u8 **)(arg0 + 0x6C) + 4;
  r7 = *(s32 *)(arg0 + 0x38);
  r8 = r6;
  b53 = (u8 *)&D_02025368;
  if (sub_0806C4B4(r8, r8) != 0) return;
  sub_0806C5EC(arg0, r7, r8, r8);
  if (D_02025FF0.f24 != 0) {
    if ((D_02025FF0.f2A & *(u16 *)(b53 + 0x3BC)) != 0) goto mask_done;
  } else {
    if ((D_02021E90.f146E & *(u16 *)(b53 + 0x3BC)) != 0) goto mask_done;
  }
  *(u32 *)(r6 + 0x70) = zeroU32();
mask_done:
  sub_08086744(arg0, r6, r8, 0xA);
  sub_0806AB04(arg0, r7, r6, r8);
  if (*(s32 *)(r6 + 0x40) == 0 && (v4c = *(s32 *)(r6 + 0x4C)) == 0 && arg0[0x18] == 0xA) {
    *(u8 *)(arg0 + 2 * *(s16 *)(arg0 + 0x22) + 0x19) = (u8)v4c;
    { u32 *fp = (u32 *)0x08671BD0; _call_via_r3(arg0 + 0x18, arg0 + 0x22, 0xC, *fp); }
  }
  sub_0806A884(r7, r8);
  q28 = r6 + 0x28;
  ret = sub_08003740(q28, r7);
  r9 = q28;
  if (ret == 0 || D_02025FF0.f1514 != 0) {
    r4 = *(s32 *)(r6 + 0x70);
    if (r4 != 0) {
      sub_0806A7AC(r7, r6, 0x15);
      sub_08085398(arg0, r6);
      sub_08003740(r9, r7);
      *(u32 *)(r6 + 0x74) = zeroU32();
      z = 0;
      *(u16 *)(*(u8 **)(r6 + 0x130) + 0x16) = (u16)(0x0F | z);
      *(u8 *)(arg0 + 2 * *(s16 *)(arg0 + 0x22) + 0x19) = (u8)z;
      { u32 *fp = (u32 *)0x08671BD0; _call_via_r3(arg0 + 0x18, arg0 + 0x22, 0xE, *fp); }
    } else {
      sub_0806A7AC(r7, r6, 5);
      sub_08003740(r9, r7);
      *(u8 *)(arg0 + 2 * *(s16 *)(arg0 + 0x22) + 0x19) = (u8)r4;
      { u32 *fp = (u32 *)0x08671BD0; _call_via_r3(arg0 + 0x18, arg0 + 0x22, 8, *fp); }
    }
  }
  sub_08086648(r7, r6, 0xA);
  sub_08086D58(r6, 0xA);
  *(u32 *)(r6 + 0xC4) = (r0 = sub_0806BCD8(arg0, r7, r6, r8));
  if (r0 != 0) {
    sub_08003740(r9, r7);
    *(u8 *)(arg0 + 2 * *(s16 *)(arg0 + 0x22) + 0x19) = (u8)(r0 * 0);
    { u32 *fp = (u32 *)0x08671BD0; _call_via_r3(arg0 + 0x18, arg0 + 0x22, *(s32 *)(r6 + 0xC4), *fp); }
  }
  sub_0806C6B0(arg0, r7, r6, r8);
}
