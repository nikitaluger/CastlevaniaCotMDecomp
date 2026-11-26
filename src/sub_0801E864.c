extern s32 sub_0805F9B4(s32, s32);
extern s32 sub_08013B5C(void *, void *);
extern void sub_080113A8(void *, void *);
extern void sub_0801165C(void *, s32);
extern void sub_0801EF8C(void *, void *);
extern s32 sub_08016238(void *);
extern void sub_080C31E0(void *, s32);
extern void sub_080C31E8(void *, void *, s32, s32);
extern void sub_08005E80(s32);
extern u32 D_08671BDC[];
extern u32 D_0866D778[];
struct S28
{
  u8 a;
  u8 flag;
};
struct S3C
{
  u16 f0;
};
struct S_02021E90
{
  u8 _0[0x1278];
  u32 f1278;
  u32 f127C;
};
struct S_02025FF0
{
  u8 _0[0x18A8];
  u8 f18A8;
};
extern struct S_02021E90 gCameraState;
extern struct S_02025FF0 gMainWorkspace;
void sub_0801E864(u8 *arg0)
{
  u8 *v38;
  u8 *p3C;
  u8 *p34;
  u8 *p48;
  u8 *r1;
  s32 idx2;
  u8 *base18;
  u8 b;
  u8 *base;
  u32 k;
  u32 *lp;
  s16 i;
  u16 *arr;
  v38 = *((u8 **) (arg0 + 0x38));
  p3C = *((u8 **) (arg0 + 0x3C));
  p34 = p3C + 0x34;
  p48 = p3C + 0x48;
  ((struct S28 *) (*((u32 *) (p3C + 0x28))))->flag |= 5;
  if ((*((s16 *) p48)) <= 0)
  {
    if (sub_0805F9B4(*((s32 *) (p3C + 0x08)), *((s32 *) (p3C + 0x0C))) == 1)
    {
      sub_080C31E0(arg0, *((u32 *) (arg0 + 0x24)));
      return;
    }
  }
  if (sub_08016238(*((u8 **) (p3C + 0x28))) != 0)
  {
    ((struct S3C *) p3C)->f0 |= 0x01;
  }
  if (((*((u16 *) ((*((u32 *) (p3C + 0x28))) + 0x14))) & 1) || ((*((u16 *) (arg0 + 0x5C))) & 2))
  {
    ((struct S3C *) p3C)->f0 |= 0x01;
  }
  else
    if ((*((u16 *) (arg0 + 0x5C))) & 2)
  {
    ((struct S3C *) p3C)->f0 |= 0x01;
  }
  if ((*((u16 *) p3C)) & 0x01)
  {
    ((struct S28 *) (*((u32 *) (p3C + 0x28))))->flag &= 0xFB;
    if ((*((u8 *) ((((*((s16 *) (arg0 + 0x22))) * 2) + ((u32) arg0)) + 0x1A))) != 2)
    {
      sub_08005E80(0x18A);
      *((u8 *) ((((*((s16 *) (arg0 + 0x22))) * 2) + ((u32) arg0)) + 0x1B)) = 0;
      lp = D_08671BDC;
      sub_080C31E8(arg0 + 0x18, arg0 + 0x22, 2, *lp);
    }
  }
  if (sub_08013B5C(v38, p3C) != 0)
  {
    goto common;
  }
  *((u32 *) (arg0 + 0x14)) = (u32) D_0866D778;
  *((u16 *) (arg0 + 0x22)) = (*((u16 *) (arg0 + 0x22))) + 1;
  i = *((s16 *) (arg0 + 0x22));
  arr = (u16 *) arg0;
  ((u8 *) (&arr[i]))[0x19] = ((u8 *) (&arr[i]))[0x19] + 1;
  idx2 = (*((s16 *) (arg0 + 0x22))) * 2;
  base18 = arg0 + 0x18;
  b = base18[idx2];
  sub_080C31E0(arg0, *((u32 *) ((*((u32 *) (arg0 + 0x14))) + (b * 4))));
  *((u16 *) (arg0 + 0x22)) = (*((u16 *) (arg0 + 0x22))) - 1;
  if (((*((u16 *) (arg0 + 2))) & 0x8000) != 0)
  {
    goto end;
  }
  sub_080113A8(v38, p34);
  sub_0801165C(p3C, 0);
  common:
  sub_0801EF8C(v38, p3C);

  r1 = *((u8 **) (p3C + 0x28));
  *((u16 *) (r1 + 0x14)) = 0;
  base = (u8 *) (&gCameraState);
  k = 0x1278;
  *((u32 *) (v38 + 0x14)) = (*((u32 *) (p3C + 8))) - (((*((u32 *) ((base + k) + ((gMainWorkspace.f18A8 + 1) << 6)))) + 0x8000) & 0xFFFF0000);
  k = 0x127C;
  *((u32 *) (v38 + 0x18)) = (*((u32 *) (p3C + 0x0C))) - (((*((u32 *) ((base + k) + ((gMainWorkspace.f18A8 + 1) << 6)))) + 0xFFFF8000) & 0xFFFF0000);
  end:
  ;

  ;
}
