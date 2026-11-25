extern void *sub_0800355C(void *);
extern void sub_0801131C(void *, void *, void *);
extern void sub_08011368(void *, void *, s32, s32);
extern void sub_080141F8(void *, void *, void *, void *, s32);
extern void sub_08014288(void *, void *, void *);
extern void *sub_08016190(void);
extern void sub_08016664(void *, s32);
extern void sub_080C31E0(void *, void *);
extern void sub_080C31E4(void *, void *, void *);
extern u8 D_02021E90[];
extern u8 D_02025FF0[];
extern u8 D_080CB2B8[];
extern u8 D_080CD400[];
extern u8 D_080CFDE4[];
extern u8 D_080CFDF8[];
extern u8 D_08671BB0[];
void sub_0805B878(u8 *arg0)
{
  u8 *r6;
  void *r8;
  u8 *r9;
  u8 *r4;
  void *new_var;
  u8 *r5;
  r8 = *((void **) (&arg0[0xAC]));
  r6 = *((u8 **) (&arg0[0x3C]));
  r9 = &r6[0x34];
  r4 = &r6[0x48];
  r5 = (u8 *) sub_0800355C(r8);
  if (r5 == NULL)
  {
    sub_080C31E0(arg0, *((void **) (&arg0[0x24])));
    return;
  }
  *((u8 **) (&arg0[0x38])) = r5;
  *((u32 *) (&r5[0x1C])) = 0x8000000A;
  sub_08014288(arg0, r6, (void *) 0x08014291);
  {
    s16 v = *((s16 *) (&D_080CFDF8[(*((u8 *) (&r4[0]))) * 4]));
    sub_080141F8(arg0, r5, r6, r8, v);
  }
  *((u8 **) (&r6[0x08])) = *((u8 **) (&arg0[0x4C]));
  *((u8 **) (&r6[0x0C])) = *((u8 **) (&arg0[0x5C]));
  {
    s16 idx = *((s16 *) (&r6[0x1C]));
    sub_0801131C(r5, r9, ((u8 *) 0x080CD400) + (idx * 12));
  }
  sub_08011368(r5, r9, 0, 0);
  {
    u8 *cfg = (u8 *) 0x080CFDE4;
    u8 *r2 = (u8 *) sub_08016190();
    *((u8 **) (&r6[0x28])) = (*((u8 **) (&r6[0x28])) = r2);
    if (r2 == NULL)
    {
      sub_080C31E0(arg0, *((void **) (&arg0[0x24])));
      return;
    }
    r2[1] = 5;
    r8 = NULL;
    ((u8 **) (&r6[0x28]))[0][2] = 0;
    *((u8 **) (&r6[0x28])) = r2;
    ((u8 **) (&r6[0x28]))[0][3] = 0;
    {
      s16 idx = *((s16 *) (&r6[0x1C]));
      u8 **p = (u8 **) (&r6[0x28]);
      *((u16 *) (&p[0][4])) = *((u16 *) (&D_080CB2B8[idx * 20]));
    }
    {
      u8 *q = *((u8 **) (&r6[0x28]));
      *((u16 *) (&q[6])) = *((u16 *) (&cfg[0]));
    }
    {
      u8 *q = *((u8 **) (&r6[0x28]));
      *((u16 *) (&q[8])) = *((u16 *) (&cfg[2]));
    }
    {
      u8 *q = *((u8 **) (&r6[0x28]));
      *((u16 *) (&q[10])) = *((u16 *) (&cfg[4]));
    }
    {
      u8 *q = *((u8 **) (&r6[0x28]));
      *((u16 *) (&q[12])) = *((u16 *) (&cfg[6]));
    }
    {
      s16 idx = *((s16 *) (&r6[0x1C]));
      u8 *q = *((u8 **) (&r6[0x28]));
      *((u16 *) (&q[14])) = *((u16 *) (&D_080CB2B8[(idx * 20) + 4]));
    }
    {
      u8 *q = *((u8 **) (&r6[0x28]));
      *((u8 **) (&q[0x10])) = r5;
    }
  }
  {
    u8 v = *((u8 *) (&D_02025FF0[0x18A8]));
    u32 off = (v + 1) << 6;
    s32 val = *((s32 *) (&D_02021E90[0x1278 + off]));
    val = (val + 0x8000) & 0xFFFF0000;
    *((s32 *) (&r5[0x14])) = (*((s32 *) (&r6[8]))) - val;
    val = *((s32 *) (&D_02021E90[0x127C + off]));
    val = (val + ((s32) 0xFFFF8000)) & 0xFFFF0000;
    *((s32 *) (&r5[0x18])) = (*((s32 *) (&r6[0x0C]))) - val;
  }
  sub_08016664(arg0, 0);
  *((u16 *) (&arg0[2])) |= 0x1000;
  new_var = *((void **) 0x08671BB0);
  {
    s16 idx = *((s16 *) (&arg0[0x22]));
    arg0[(idx * 2) + 0x19] = 0;
  }
  sub_080C31E4(&arg0[0x18], &arg0[0x22], new_var);
  {
    s16 idx = *((s16 *) (&arg0[0x22]));
    u8 *pp = &arg0[idx * 2];
    pp[0x19] = pp[0x19] + 1;
  }
  {
    s16 idx = *((s16 *) (&arg0[0x22]));
    u8 idx2 = *((u8 *) (&arg0[0x18 + (idx * 2)]));
    u8 *base2 = *((u8 **) (&arg0[0x14]));
    void *fn = *((void **) (&base2[idx2 * 4]));
    sub_080C31E0(arg0, fn);
  }
}

