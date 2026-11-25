struct S_02025FF0
{
  u8 _[0x1728];
  u32 f1728;
  u32 f172C;
};
extern struct S_02025FF0 D_02025FF0;
s32 sub_08005910(s32, s32);
void sub_080146D0(void *, s32, s32);
s32 sub_08014938(s32);
void sub_080C31E4(void *, void *, s32);
void sub_080555E0(void *arg0)
{
  s32 new_var;
  void *r6;
  void *r4;
  u8 *r7;
  s32 v;
  s32 r;
  r6 = *((void **) (((u8 *) arg0) + 0x38));
  r4 = *((void **) (((u8 *) arg0) + 0x3C));
  r7 = ((u8 *) r4) + 0x48;
  if (sub_08014938(*((s32 *) (((u8 *) r4) + 8))) > 0)
  {
    v = D_02025FF0.f1728 + 0xFFE00000;
  }
  else
  {
    v = D_02025FF0.f1728 + (0x80 << 14);
  }
  new_var = sub_08005910(D_02025FF0.f172C - (*((s32 *) (((u8 *) r4) + 0xC))), v - (*((s32 *) (((u8 *) r4) + 8))));
  sub_080146D0(r4, ((0x80 << 5) + new_var) & (0xF0 << 8), 0x80 << 8);
  *((u16 *) (((u8 *) r7) + 6)) = 0x96;
  r = sub_08014938(*((s32 *) (((u8 *) r4) + 8)));
  *((u16 *) (((u8 *) r6) + 2)) = (r > 0) ? ((*((u16 *) (((u8 *) r6) + 2))) | 0x10) : ((*((u16 *) (((u8 *) r6) + 2))) & 0xFFEF);
  new_var = (*((s16 *) (((u8 *) arg0) + 0x22))) * 2;
  *((u8 *) ((((u8 *) arg0) + new_var) + 0x19)) = 0;
  {
    s32 *lit = (s32 *) 0x08671BB0;
    sub_080C31E4(((u8 *) arg0) + 0x18, ((u8 *) arg0) + 0x22, *lit);
 do { } while (0);
  }
}
