struct S_02025FF0
{
  u8 _0[0x10];
  s32 f10;
  u8 _1[0x14ED - 0x14];
  u8 f14ED;
  u8 _2[0x173A - 0x14EE];
  u8 f173A;
  u8 _3[0x18C2 - 0x173B];
  u16 f18C2;
};
extern struct S_02025FF0 gMainWorkspace;
s32 checkGlobalStateChange(void *, void *, void *);
extern void setSpriteScreenPosition(void *, void *);
extern void sub_0806D330(void *, void *);
extern void setDirectionVector(void *, u8);
extern void sub_080C31E0(void *, s32);
void sub_080762E0(void *arg0)
{
  void *r5v;
  void *r4v;
  void *r6v;
  s32 r8v;
  s32 r9v;
  s32 var_r0;
  u8 *new_var;
  s32 t;
  void *r2;
  struct S_02025FF0 *p;
  r5v = *((void **) (((u8 *) arg0) + 0x6C));
  r4v = ((u8 *) r5v) + 4;
  r6v = *((void **) (((u8 *) arg0) + 0x38));
  if (checkGlobalStateChange(arg0, r6v, r4v) != 0)
  {
    return;
  }
  var_r0 = (*((s32 *) (((u8 *) r4v) + 0xC))) + 0x4000;
  *((s32 *) (((u8 *) r4v) + 0xC)) = var_r0;
  if (var_r0 > 0x80000)
  {
    *((s32 *) (((u8 *) r4v) + 0xC)) = 0x80000;
  }
  *((s32 *) (((u8 *) r5v) + 0x4)) = (*((s32 *) (((u8 *) r5v) + 0x4))) + (*((s32 *) (((u8 *) r4v) + 0x8)));
  *((s32 *) (((u8 *) r4v) + 0x4)) = (*((s32 *) (((u8 *) r4v) + 0x4))) + (*((s32 *) (((u8 *) r4v) + 0xC)));
  p = &gMainWorkspace;
  *((u16 *) r6v) = p->f18C2;
  t = (*((u16 *) (((u8 *) r6v) + 0x8))); *((u16 *) (((u8 *) r6v) + 0x8)) = t + 0x800;
  r8v = *((s32 *) (((u8 *) r4v) + 0x8));
  r9v = *((s32 *) (((u8 *) r4v) + 0xC));
  setDirectionVector(r4v, (u8) (0 - ((*((u16 *) (((u8 *) r6v) + 0x8))) >> 8)));
  r2 = *((void **) (((u8 *) r4v) + 0x2C));
  t = *((s32 *) (((u8 *) r4v) + 0x8));
  var_r0 = (t << 1) + t;
  var_r0 = var_r0 << 3;
  if (var_r0 < 0)
  {
    var_r0 += 0xFFFF;
  }
  *((s16 *) (((u8 *) r2) + 0xA)) = (s16) (var_r0 >> 16);
  new_var = (u8 *) r4v;
  r2 = *((void **) (new_var + 0x2C));
  t = *((s32 *) (new_var + 0xC));
  var_r0 = (t << 1) + t;
  var_r0 = var_r0 << 3;
  if (var_r0 < 0)
  {
    var_r0 += 0xFFFF;
  }
  *((s16 *) (((u8 *) r2) + 0xC)) = (s16) (var_r0 >> 16);
  r2 = *((void **) (((u8 *) r4v) + 0x30));
  t = *((s32 *) (((u8 *) r4v) + 0x8));
  var_r0 = (t << 1) + t;
  var_r0 = var_r0 << 2;
  if (var_r0 < 0)
  {
    var_r0 += 0xFFFF;
  }
  *((s16 *) (((u8 *) r2) + 0xA)) = (s16) (var_r0 >> 16);
  r2 = *((void **) (((u8 *) r4v) + 0x30));
  t = *((s32 *) (((u8 *) r4v) + 0xC));
  var_r0 = (t << 1) + t;
  var_r0 = var_r0 << 2;
  if (var_r0 < 0)
  {
    var_r0 += 0xFFFF;
  }
  *((s16 *) (((u8 *) r2) + 0xC)) = (s16) (var_r0 >> 16);
  r2 = *((void **) (((u8 *) r4v) + 0x38));
  t = *((s32 *) (((u8 *) r4v) + 0x8));
  var_r0 = (t << 1) + t;
  var_r0 = var_r0 << 2;
  var_r0 = -var_r0;
  if (var_r0 < 0)
  {
    var_r0 += 0xFFFF;
  }
  *((s16 *) (((u8 *) r2) + 0xA)) = (s16) (var_r0 >> 16);
  r2 = *((void **) (((u8 *) r4v) + 0x38));
  t = *((s32 *) (((u8 *) r4v) + 0xC));
  var_r0 = (t << 1) + t;
  var_r0 = var_r0 << 2;
  var_r0 = -var_r0;
  if (var_r0 < 0)
  {
    var_r0 += 0xFFFF;
  }
  *((s16 *) (((u8 *) r2) + 0xC)) = (s16) (var_r0 >> 16);
  r2 = *((void **) (((u8 *) r4v) + 0x3C));
  t = *((s32 *) (((u8 *) r4v) + 0x8));
  var_r0 = (t << 1) + t;
  var_r0 = var_r0 << 3;
  var_r0 = -var_r0;
  if (var_r0 < 0)
  {
    var_r0 += 0xFFFF;
  }
  *((s16 *) (((u8 *) r2) + 0xA)) = (s16) (var_r0 >> 16);
  r2 = *((void **) (((u8 *) r4v) + 0x3C));
  t = *((s32 *) (new_var + 0xC));
  var_r0 = (t << 1) + t;
  var_r0 = var_r0 << 3;
  var_r0 = -var_r0;
  if (var_r0 < 0)
  {
    var_r0 += 0xFFFF;
  }
  *((s16 *) (((u8 *) r2) + 0xC)) = (s16) (var_r0 >> 16);
  *((s32 *) (((u8 *) r4v) + 0x8)) = r8v;
  *((s32 *) (((u8 *) r4v) + 0xC)) = r9v;
  setSpriteScreenPosition(r6v, r4v);
  sub_0806D330(arg0, r6v);
  if (p->f173A == 0x1C)
  {
    goto call;
  }
  if (p->f14ED != 0)
  {
    goto end;
  }
  if (p->f10 == 0)
  {
    goto end;
  }
  call:
  sub_080C31E0(arg0, *((s32 *) (((u8 *) arg0) + 0x24)));

  end:
  return;

}

