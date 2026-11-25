extern void sub_0800168C(void *, s32, s32, s32);
extern void *sub_0800355C(void);
extern void sub_0801131C(void *, void *, void *);
extern s32 sub_08013C2C(void);
extern void sub_08014288(void *, void *, void *);
extern void sub_080C31E0(void *, s32);
extern void sub_080C31E4(void *, void *, s32);
struct S_02025FF0 { u8 _0[0x18C2]; u16 w; };
extern struct S_02025FF0 D_02025FF0;
extern u8 D_080CD400[];

void sub_0809E860(void *arg0)
{
  void *r4;
  void *r6;
  void *r7;
  s32 w16;
  u8 *r4b;
  void **pp;
  s32 *fb;
  u8 *q;
  u8 zero;
  r4 = sub_0800355C();
  if (r4 == NULL)
  {
    sub_080C31E0(arg0, *((s32 *) (((char *) arg0) + 0x24)));
    return;
  }
  *((void **) (((char *) arg0) + 0x38)) = r4;
  sub_0800168C(arg0, 0, 0x48, 0);
  if ((*((vu32 *) (((char *) arg0) + 0x3C))) == 0)
  {
    sub_080C31E0(arg0, *((s32 *) (((char *) arg0) + 0x24)));
    return;
  }
  *((s32 *) (((char *) r4) + 0x1C)) = 0x80000009;
  r6 = *((void **) (((char *) arg0) + 0x3C));
  r7 = ((char *) r6) + 0x34;
  sub_08014288(arg0, r6, (void *)0x08097DC9);
  zero = 0;
  *((s16 *) (((char *) r6) + 0x1C)) = 0x4C;
  w16 = sub_08013C2C();
  *((s16 *) (((char *) r6) + 0x22)) = (s16) w16;
  if (((s32) (((u32) w16) << 16)) < 0)
  {
    sub_080C31E0(arg0, *((s32 *) (((char *) arg0) + 0x24)));
    return;
  }
  w16 = *((s16 *) (((char *) r6) + 0x22));
  w16 <<= 6;
  w16 += 0x200;
  w16 &= 0xFC0;
  *((u16 *) r4) = w16;
  *((u16 *) r4) = w16 | (&D_02025FF0)->w;
  *((u16 *) (((char *) r4) + 2)) |= 0x400;
  sub_0801131C(r4, r7, (void *) ((((s32) (*((s16 *) (((char *) r6) + 0x1C)))) * 0xC) + 0x080CD400));
  *((u8 *) (((char *) arg0) + 0x7C)) = zero;
  *((u8 *) (((char *) arg0) + 0x80)) = 0xFF;
  *((u16 *) (((char *) arg0) + 0x02)) |= 0x1000;
  {
    u8 *p = (u8 *) ((((s16) (*((s16 *) (((char *) arg0) + 0x22)))) * 2) + ((u32) arg0));
    p[0x19] = zero;
  }
  pp = (void **)0x08671BB0;
  r4b = ((char *) arg0) + 0x18;
  sub_080C31E4(r4b, ((char *) arg0) + 0x22, (s32) (*pp));
  {
    u8 *p = (u8 *) ((((s16) (*((s16 *) (((char *) arg0) + 0x22)))) * 2) + ((u32) arg0));
    p[0x19] = p[0x19] + 1;
  }
  q = r4b + (((s16) (*((s16 *) (((char *) arg0) + 0x22)))) * 2);
  {
    u8 idx2 = *q;
    fb = *((s32 **) (((char *) arg0) + 0x14));
    sub_080C31E0(arg0, fb[idx2]);
  }
}
