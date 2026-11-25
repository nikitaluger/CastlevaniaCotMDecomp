extern void sub_0800168C(void *, s32, s32, s32);
extern void *sub_0800355C(void);
extern void sub_0801131C(void *, void *, void *);
extern void sub_08011368(void *, void *, s32, s32);
extern s16 sub_08013C2C(s32);
extern void sub_080C31E0(void *, s32);
extern void sub_080C31E4(void *, void *, s32);
struct S_02025FF0
{
  u8 _0[0x18C2];
  u16 w;
};
extern struct S_02025FF0 D_02025FF0;
void sub_080AE5C0(void *arg0)
{
  unsigned char new_var3;
  void *r6;
  void *r4;
  s16 *new_var4;
  char *new_var;
  void *r7;
  unsigned int new_var2;
  s16 r1;
  u8 *p;
  u8 *p2;
  u8 idx2;
  u8 *r4b;
  r6 = sub_0800355C();
  if (r6 == NULL)
  {
    sub_080C31E0(arg0, *((s32 *) (((char *) arg0) + 0x24)));
    return;
  }
  do
  {
    *((void **) (((char *) arg0) + 0x38)) = r6;
    sub_0800168C(arg0, 0, 0x48, 0);
    r4 = *((void **) (((char *) arg0) + 0x3C));
    if ((*((void **) (((char *) arg0) + 0x3C))) == NULL)
    {
      sub_080C31E0(arg0, *((s32 *) (((char *) arg0) + 0x24)));
      return;
    }
    *((s32 *) (((char *) r6) + 0x1C)) = 1;
    r7 = ((char *) r4) + 0x34;
    *((s16 *) (((char *) (*((void **) (((char *) arg0) + 0x3C)))) + 0x1C)) = 0x64;
    *((s32 *) (((char *) (*((void **) (((char *) arg0) + 0x3C)))) + 0x08)) = *((s32 *) (((char *) arg0) + 0x4C));
  }
  while (0);
  *((s32 *) (((char *) (*((void **) (((char *) arg0) + 0x3C)))) + 0x0C)) = *((s32 *) (((char *) arg0) + 0x5C));
  r1 = sub_08013C2C(0x64);
  *((s16 *) (((char *) r4) + 0x22)) = r1;
  if (((s32) (r1 << 16)) <= (0 - 1))
  {
    sub_080C31E0(arg0, *((s32 *) (((char *) arg0) + 0x24)));
    return;
  }
  {
    int v = ((*((s16 *) (((char *) r4) + 0x22))) << 6) + 0x200;
    v = v & (new_var3 = 0xFC0);
    p = *((void **) (((char *) arg0) + 0x3C));
    *((s16 *) (((char *) r6) + 0x00)) = v;
    *((s16 *) (r6 + 0x00)) = v | D_02025FF0.w;
  }
  sub_0801131C(r6, r7, (void *) ((((s32) (*((s16 *) (((char *) p) + 0x1C)))) * 0xC) + 0x080CD400));
  sub_08011368(r6, r7, 9, 0);
  *((u16 *) (((char *) r6) + 0x02)) = (*((u16 *) (((char *) r6) + 0x02))) | 0x0400;
  *((u16 *) (((char *) arg0) + 0x02)) = (*((u16 *) (((char *) arg0) + 0x02))) | 0x1000;
  ;
  ((u8 *) ((((s16) (*((s16 *) (((char *) arg0) + 0x22)))) * 2) + ((u32) arg0)))[0x19] = (r1 = 0);
  new_var2 = *((s32 *) 0x08671BB0);
  p = ((char *) arg0) + 0x14;
  new_var4 = (s16 *) (((char *) arg0) + 0x22);
  r4b = ((char *) arg0) + 0x18;
  sub_080C31E4(r4b, ((char *) arg0) + 0x22, new_var2);
  p2 = (u8 *) ((((s16) (*new_var4)) * 2) + ((u32) arg0));
  p2[0x19] = p2[0x19] + 1;
  idx2 = *((u8 *) ((((char *) arg0) + 0x18) + (((s16) (*new_var4)) * 2)));
  sub_080C31E0(arg0, *((s32 *) ((new_var = p) + (idx2 * 4))));
}

