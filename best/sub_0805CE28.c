extern u8 D_02025368[];
extern u16 D_080D0014[];
extern void sub_0805D92C(s32, s32, u16);
extern void sub_0808DBF8(s32, s32, u16);
extern void sub_080C31E0(void *, s32);
void sub_0805CE28(u8 *arg0)
{
  u8 *base = D_02025368;
  u8 *r7 = *((u8 **) (arg0 + 0xAC));
  u8 *r4 = *((u8 **) (arg0 + 0x3C));
  u16 *p = (u16 *) (*((u8 **) (r7 + 4)));
  u32 r2 = p[3];
  u16 r5 = (u16) r2;
  u32 m = 4;
  if (r5 <= 4)
  {
    u8 *r3 = base + 0x2D8;
    u8 t = *r3;
 do { if (t != 0) { u16 val = D_080D0014[t - 1]; if (r5 == val) { s16 x = *((s16 *) (base + 0x8C)); if ((x != 1) || ((*((u16 *) r3)) != 1)) { r2 = 6; } } } } while (0);
  }
  sub_0805D92C(*((s32 *) r4), *((s32 *) (r4 + 4)), r2);
  *((u16 *) r7) = m | *((u16 *) r7);
  sub_0808DBF8(*((s32 *) r4), *((s32 *) (r4 + 4)), 0xD);
  sub_080C31E0(arg0, *((s32 *) (arg0 + 0x24)));
}
