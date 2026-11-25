extern void *sub_0800355C(void);
extern void sub_0800168C(void *, s32, s32, s32);
extern void sub_08014288(void *, void *, void *);
extern s16 sub_08013C2C(void);
extern void sub_080B05EC(void *, s32, u8, s32);
extern void sub_080114DC(void *, s32, s16, s32);
extern void *sub_08016190(void);
extern s32 sub_08005910(s16, s16);
extern s32 sub_080059DC(s32, s32);
extern void _call_via_r1(void *, void *);
extern u8 D_0810255C[];
extern u8 D_0810261C[];
extern u8 D_08102634[];
extern u8 D_08102654[];
extern u8 D_08102694[];
extern u8 D_02025FF0[];
extern u8 D_080CB2B8[];
extern u8 D_080CBDD0[];
extern u8 sub_080AFBA4;
void sub_080AF390(void *arg0)
{
  int new_var6;
  int new_var9;
  u8 *a = (u8 *) arg0;
  u8 *p0;
  u8 *p4;
  u8 *r7;
  u8 **new_var12;
  u8 *r8;
  void *new_var2;
  u8 *new_var11;
  u16 *new_var10;
  u8 *new_var7;
  u8 *t;
  u8 *new_var5;
  u8 *new_var3;
  u8 *o;
  u8 *new_var;
  s32 idx;
  u16 *new_var8;
  s32 i;
  s16 v;
  u8 *new_var4;
  u8 **new_var13;
  p0 = sub_0800355C();
  if (p0 == NULL)
  {
    _call_via_r1(arg0, *((void **) (a + 0x24)));
    return;
  }
  *((void **) (a + 0x38)) = p0;
  sub_0800168C(arg0, 0, 0x68, 0);
  r7 = *((u8 **) (a + 0x3C));
  if (r7 == NULL)
  {
    _call_via_r1(arg0, *((void **) (a + 0x24)));
    return;
  }
  idx = *((s8 *) (a + 0x5C));
  idx = (((*((u8 *) (a + 0x50))) << 2) + (idx << 4)) + ((*((u8 *) (a + 0x4C))) << 5);
  *((u32 *) (p0 + 0x1C)) = *((u32 *) (D_08102654 + idx));
  p4 = r7 + 0x34;
  new_var4 = a + 0x4C;
  r8 = r7 + 0x48;
  new_var6 = (((*((u8 *) new_var4)) * 6) * 0x10) + (((*((u8 *) (a + 0x50))) * 3) * 8);
  sub_08014288(arg0, r7, &sub_080AFBA4);
  new_var9 = 0x2;
  *((u16 *) (r7 + 0x1C)) = 0x64;
  v = sub_08013C2C();
  *((u16 *) (r7 + 0x22)) = (u16) v;
  if (((s32) (((u32) v) << 16)) < 0)
  {
    new_var5 = *((void **) (a + 0x24));
    _call_via_r1(arg0, new_var5);
    return;
  }
  new_var7 = a;
  new_var11 = D_02025FF0 + 0x18C2;
  *((u16 *) p0) = (*((u16 *) p0)) | (*((u16 *) new_var11));
  sub_080B05EC(p0, p4, *((u8 *) ((D_08102694 + ((*((u8 *) new_var4)) << 2)) + (*((u8 *) (new_var7 + 0x50))))), 2);
  sub_080114DC(p0, p4, *((s16 *) ((D_08102634 + ((*((u8 *) (new_var7 + 0x50))) << 2)) + ((*((u8 *) new_var4)) << 4))), 0);
  if (((*((u8 *) new_var4)) != 0) || ((*((u8 *) (new_var7 + 0x50))) != 3))
  {
    idx = new_var6;
    t = D_0810255C + idx;
    o = sub_08016190();
    *((u8 **) (r7 + 0x28)) = o;
    if (o == NULL)
    {
      _call_via_r1(arg0, *((void **) (new_var7 + 0x24)));
      return;
    }
    new_var = r7 + 0x1C;
    idx = ((*((u8 *) (new_var7 + 0x50))) * 3) + ((*((u8 *) new_var4)) * 0xC);
    o[1] = D_0810261C[idx];
    o[2] = 8;
    *((u16 *) (o + 4)) = *((u16 *) ((D_080CBDD0 + ((*((s16 *) new_var)) * 0x28)) + 0x10));
    o[3] = 1;
    *((u16 *) (o + 6)) = *((u16 *) (t + 0));
    *((u16 *) (o + 8)) = *((u16 *) (t + 2));
    *((u16 *) (o + 0xA)) = *((u16 *) (t + 4));
    *((u16 *) (o + 0xC)) = *((u16 *) (t + 6));
    *((u16 *) (o + 0xE)) = *((u16 *) ((D_080CBDD0 + ((*((s16 *) new_var)) * 0x28)) + 0x12));
    new_var3 = D_080CBDD0;
    *((void **) (o + 0x10)) = p0;
    t = (D_0810255C + (((*((u8 *) new_var4)) * 6) * 0x10)) + (((*((u8 *) (new_var7 + 0x50))) * 3) * 8);
    o = sub_08016190();
    *((u8 **) (r7 + 0x48)) = o;
    if (o == NULL)
    {
      if (t)
      {
        _call_via_r1(arg0, *((void **) (new_var7 + 0x24)));
        return;
      }
      else
      {
        _call_via_r1(arg0, *(new_var7 + 0x24));
        return;
      }
    }
    o[1] = D_0810261C[idx + 1];
    o[2] = 8;
    new_var10 = (u16 *) (t + 0xA);
    o[3] = 1;
    new_var11 = D_080CBDD0 + ((*((s16 *) new_var)) * 0x28);
    *((u16 *) (o + 4)) = *((u16 *) (new_var11 + 0x10));
    *((u16 *) (o + 6)) = *((u16 *) (t + 8));
    *((u16 *) (o + 8)) = *new_var10;
    *((u16 *) (o + 0xA)) = *((u16 *) (t + 0xC));
    *((u16 *) (o + 0xC)) = *((u16 *) (t + 0xE));
    *((u16 *) (o + 0xE)) = *((u16 *) ((new_var3 + ((*((s16 *) new_var)) * 0x28)) + 0x12));
    *((void **) (o + 0x10)) = p0;
    t = (D_0810255C + (((*((u8 *) new_var4)) * 6) * 0x10)) + (((*((u8 *) (new_var7 + 0x50))) * 3) * 8);
    o = sub_08016190();
    *((u8 **) (r8 + 4)) = o;
    if (o == NULL)
    {
      _call_via_r1(arg0, *((void **) (new_var7 + 0x24)));
      return;
      *((u16 *) (o + 4)) = *((u16 *) ((new_var3 + ((*((s16 *) new_var)) * 0x28)) + 0x10));
    }
    o[1] = D_0810261C[idx + 2];
    o[2] = 8;
    o[3] = 1;
    new_var8 = (u16 *) (t + 0x10);
    *((u16 *) (o + 6)) = *new_var8;
    *((u16 *) (o + 8)) = *((u16 *) (t + 0x12));
    *((u16 *) (o + 0xA)) = *((u16 *) (t + 0x14));
    *((u16 *) (o + 0xC)) = *((u16 *) (t + 0x16));
    *((u16 *) (o + 0xE)) = *((u16 *) ((new_var3 + ((*((s16 *) new_var)) * 0x28)) + 0x12));
    *((void **) (o + 0x10)) = p0;
  }
  else
  {
    idx = (((*((u8 *) new_var4)) * 6) * 0x10) + (((*((u8 *) (new_var7 + 0x50))) * 3) * 8);
    t = D_0810255C + idx;
    new_var2 = *((void **) (new_var7 + 0x24));
    o = sub_08016190();
    *((u8 **) (r7 + 0x28)) = o;
    if (o == NULL)
    {
      _call_via_r1(arg0, new_var2);
      return;
    }
    idx = ((*((u8 *) (new_var7 + 0x50))) * 3) + ((*((u8 *) new_var4)) * 0xC);
    o[1] = D_0810261C[idx];
    o[2] = 8;
    o[3] = 1;
    *((u16 *) (o + 4)) = *((u16 *) (D_080CB2B8 + ((*((s16 *) new_var)) * 0x14)));
    *((u16 *) (o + 6)) = *((u16 *) (t + 0));
    *((u16 *) (o + 8)) = *((u16 *) (t + 2));
    *((u16 *) (o + 0xA)) = *((u16 *) (t + 4));
    *((u16 *) (o + 0xC)) = *((u16 *) (t + 6));
    new_var12 = (u8 **) (r7 + 0x48);
    *((u16 *) (o + 0xE)) = *((u16 *) ((D_080CB2B8 + ((*((s16 *) new_var)) * 0x14)) + 4));
    *((void **) (o + 0x10)) = p0;
    t = (D_0810255C + (((*((u8 *) new_var4)) * 6) * 0x10)) + (((*((u8 *) (new_var7 + 0x50))) * 3) * 8);
    o = sub_08016190();
    *new_var12 = o;
    if (o == NULL)
    {
      _call_via_r1(arg0, *((void **) (new_var7 + 0x24)));
      return;
    }
    new_var13 = (u8 **) (r8 + 4);
    o[1] = D_0810261C[idx + 1];
    o[2] = 8;
    o[3] = 1;
    *((u16 *) (o + 4)) = *((u16 *) (D_080CB2B8 + ((*((s16 *) new_var)) * 0x14)));
    *((u16 *) (o + 6)) = *((u16 *) (t + 8));
    *((u16 *) (o + 8)) = *((u16 *) (t + 0xA));
    new_var5 = D_080CB2B8;
    *((u16 *) (o + 0xA)) = *((u16 *) (t + 0xC));
    *((u16 *) (o + 0xC)) = *((u16 *) (t + 0xE));
    *((u16 *) (o + 0xE)) = *((u16 *) ((new_var5 + ((*((s16 *) new_var)) * 0x14)) + 4));
    *((void **) (o + 0x10)) = p0;
    t = (D_0810255C + (((*((u8 *) new_var4)) * 6) * 0x10)) + (((*((u8 *) (new_var7 + 0x50))) * 3) * 8);
    o = sub_08016190();
    *new_var13 = o;
    if (o == NULL)
    {
      _call_via_r1(arg0, *((void **) (new_var7 + 0x24)));
      return;
    }
    o[1] = D_0810261C[idx + 2];
    o[2] = 8;
    o[3] = 1;
    *((u16 *) (o + 4)) = *((u16 *) (new_var5 + ((*((s16 *) new_var)) * 0x14)));
    *((u16 *) (o + 6)) = *((u16 *) (t + 0x10));
    *((u16 *) (o + 8)) = *((u16 *) (t + 0x12));
    *((u16 *) (o + 0xA)) = *((u16 *) (t + 0x14));
    *((u16 *) (o + 0xC)) = *((u16 *) (t + 0x16));
    *((u16 *) (o + 0xE)) = *((u16 *) ((new_var5 + ((*((s16 *) new_var)) * 0x14)) + 4));
    *((void **) (o + 0x10)) = p0;
  }
  i = (*((u8 *) (new_var7 + 0x54)) = 0);
  do
  {
    t = D_0810255C + (i * 8);
    t = (t + (((*((u8 *) (new_var7 + 0x50))) * 3) * 8)) + (((*((u8 *) new_var4)) * 3) * 0x20);
    *((s32 *) ((r8 + 8) + (i * 4))) = sub_08005910(*((s16 *) (t + 6)), *((s16 *) (t + 4)));
    *((s32 *) ((r8 + 0x14) + (i * 4))) = sub_080059DC(((s32) (*((s16 *) (t + 4)))) << 16, ((s32) (*((s16 *) (t + 6)))) << 16);
  }
  while ((++i) <= 2);
  if (((*((u8 *) new_var4)) == 0) && ((*((s8 *) (new_var7 + 0x5C))) == 1))
  {
    *((u16 *) p0) = ((*((u16 *) p0)) & 0xFFF) | 0xFFFFF000;
  }
  *((u16 *) (new_var7 + 0x2)) = ((unsigned char) 0x1800) | (*((u16 *) (new_var7 + new_var9)));
  *((void **) (new_var7 + 0x14)) = (void *) 0x080AF955;
  *((u16 *) (new_var7 + 0x22)) = 1;
  _call_via_r1(arg0, (void *) 0x080AF955);
}

