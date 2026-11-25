extern void sub_08003A6C(void *a, s32 b, void *c);
extern void sub_08003740(void *a, void *b);
extern void sub_0806D588(void *a);
extern void sub_080C31E0(void *a, void *b);
extern void sub_080C31E4(void *a, void *b, void *c);
extern u32 D_08671BB0;
struct P38
{
  u8 _0[2];
  u16 f2;
  u8 _4[0x20];
  u32 f24;
};
void sub_08088D1C(void *arg0)
{
  u8 *obj = *((u8 **) (((u8 *) arg0) + 0x6C));
  u8 *obj4 = obj + 4;
  struct P38 *p38 = *((struct P38 **) (((u8 *) arg0) + 0x38));
  u8 *r4;
  s16 idx;
  u8 *base18;
  p38->f24 = 0x08509598;
  r4 = obj + 0x20;
  sub_08003A6C(r4, 0, (void *) 0x08509680);
  sub_08003740(r4, p38);
  p38->f2 |= 0x10;
  *((u32 *) (obj + 4)) = 0x01080000;
  *((u32 *) (obj4 + 4)) = 0x007F0000;
  *((u32 *) (obj4 + 8)) = 0xFFFE0000;
  *((vu32 *) (obj4 + 0x0C)) = 0;
  sub_0806D588(p38);
  *((u8 *) ((((u8 *) arg0) + ((*((s16 *) (((u8 *) arg0) + 0x22))) * 2)) + 0x19)) = 0;
  {
    u32 *pBB0 = &D_08671BB0;
    base18 = ((u8 *) arg0) + 0x18;
    sub_080C31E4(base18, ((u8 *) arg0) + 0x22, (void *) (*pBB0));
    idx = *((s16 *) (((u8 *) arg0) + 0x22));
    (*((u8 *) (((idx * 2) + ((u8 *) arg0)) + 0x19)))++;
    idx = *((s16 *) (base18 + 0x0A));
    base18 += idx * 2;
    {
      u8 b = *base18;
      void **tbl = *((void ***) (((u8 *) arg0) + 0x14));
      sub_080C31E0((u8 *) arg0, tbl[b]);
    }
  }
}
