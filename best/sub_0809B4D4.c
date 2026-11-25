extern void sub_0800168C(void *, s32, s32, s32);
extern void *sub_0800355C(void);
extern void sub_0801131C(void *, void *, void *);
extern void sub_08011368(void *, void *, s32, s32);
extern s32 sub_08013C2C(void);
extern void sub_08014288(void *, void *, void *);
extern void sub_080C31E0(void *, s32);
extern void sub_080C31E4(void *, void *, s32);
extern void sub_08097DC8(void);
struct S_02025FF0
{
  u8 _0[0x18C2];
  u16 w;
};
extern struct S_02025FF0 D_02025FF0;
void sub_0809B4D4(void *arg0)
{
  void *r6;
  void *r4;
  void *r7;
  s32 w16;
  u8 *r4b;
  void **pp;
  s32 *fb;
  u8 *q;
  r6 = sub_0800355C();
  if (r6 == NULL)
  {
    sub_080C31E0(arg0, *((s32 *) (((char *) arg0) + 0x24)));
    return;
  }
  *((void **) (((char *) arg0) + 0x38)) = r6;
  sub_0800168C(arg0, 0, 0x48, 0);
  if ((*((void * volatile *) (((char *) arg0) + 0x3C))) == 0)
  {
    sub_080C31E0(arg0, *((s32 *) (((char *) arg0) + 0x24)));
    return;
  }
  *((s32 *) (((char *) r6) + 0x1C)) = 0x8000000B;
  r4 = *((void * volatile *) (((char *) arg0) + 0x3C));
  r7 = (char *) r4;
  r7 = r7 + 0x34;
  sub_08014288(arg0, r4, sub_08097DC8);
  *((s16 *) (((char *) r4) + 0x1C)) = 0x44;
  w16 = sub_08013C2C();
  *((s16 *) (((char *) r4) + 0x22)) = (s16) w16;
  if (((s32) (((u32) w16) << 16)) < 0)
  {
    sub_080C31E0(arg0, *((s32 *) (((char *) arg0) + 0x24)));
    return;
  }
  w16 = *((s16 *) (((char *) r4) + 0x22));
  w16 <<= 6;
  w16 += 0x200;
  w16 &= 0xFC0;
  *((u16 *) r6) = w16;
  *((u16 *) r6) = w16 | D_02025FF0.w;
  sub_0801131C(r6, r7, (void *) ((((s32) (*((s16 *) (((char *) r4) + 0x1C)))) * 0xC) + 0x080CD400));
  sub_08011368(r6, r7, 9, 0);
  *((u16 *) (((char *) arg0) + 0x02)) |= 0x1000;
  {
    u8 *p = (u8 *) ((((s16) (*((s16 *) (((char *) arg0) + 0x22)))) * 2) + ((u32) arg0));
    p[0x19] = 0;
  }
  pp = (void **) 0x08671BB0;
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

