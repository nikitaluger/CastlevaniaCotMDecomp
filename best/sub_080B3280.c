void *sub_0800355C(void);
void sub_0800168C(void *, s32, s32, s32);
void sub_08014288(void *, void *, void *);
void sub_08097D18(void *, void *, void *, void *, s32);
void sub_080B710C(void *, void *, s32, s32);
void sub_080114DC(void *, void *, s32, s32);
void sub_08097EB4(void *);
void *sub_08016190(void);
void *sub_080B7144(void *, s32);
void *sub_080B7174(void *);
void *sub_080B7258(void *);
void *sub_0805FAEC(void *, s32);
void sub_08016664(void *, s32);
void sub_080C31E4(void *, void *, void *);
void sub_080C31E0(void *, void *);
extern u8 D_0840E198[];
extern u16 D_0810298C[];
extern u8 D_080CB2B8[];
extern s16 D_080CBDD0[];
extern u32 D_02025FF0[];
extern void *D_08671BB0;
struct UnkSub
{
  u8 pad0[1];
  u8 b1;
  u8 b2;
  u8 b3;
  u16 h4;
  u16 h6;
  u16 h8;
  u16 hA;
  u16 hC;
  u16 hE;
  void *p10;
};
struct Unk5
{
  u8 pad0[4];
  u16 h4;
  u8 pad6[0x12];
  s32 f18;
  s16 f1C;
  u8 pad1E[0xA];
  struct UnkSub *f28;
  u8 pad2C[0x8];
  void *f34;
  u8 pad38[0x10];
  struct UnkSub *f48;
  u8 pad4C[0x1D];
  u8 b69;
};
struct Arg0
{
  u8 pad0[2];
  u16 h2;
  s32 f4;
  u8 pad8[0xC];
  void **f14;
  u8 f18[4];
  u8 pad1C[3];
  u8 b1F;
  u8 pad20[2];
  s16 s22;
  void *f24;
  u8 pad28[0x10];
  void *f38;
  struct Unk5 *f3C;
  u8 pad40[0xC];
  s32 f4C;
  u8 pad50[0xC];
  s32 f5C;
  u8 pad60[0x4C];
  void *fAC;
};
void sub_080B3280(struct Arg0 *arg0)
{
  void *r8_ac;
  void *obj;
  struct Unk5 *r5;
  void *r4_34;
  u8 *r10_base;
  u16 *r8data;
  u8 *cb2b8;
  r8_ac = arg0->fAC;
  obj = sub_0800355C();
  if (obj == 0)
  {
    goto fail;
  }
  arg0->f38 = obj;
  sub_0800168C(arg0, 0, 0x70, 0);
  if ((*((u32 *) (((u8 *) arg0) + 0x3C))) == 0)
  {
    goto fail;
  }
  *((s32 *) (((u8 *) obj) + 0x1C)) = 0x8000000A;
  r5 = arg0->f3C;
  r4_34 = ((u8 *) r5) + 0x34;
  r10_base = ((u8 *) r5) + 0x48;
  sub_08014288(arg0, r5, (void *) 0x080B4ACD);
  sub_08097D18(arg0, obj, r5, r8_ac, 0x66);
  sub_080B710C(obj, r4_34, 0x10, 3);
  sub_080114DC(obj, r4_34, 0, 1);
  sub_08097EB4(D_0840E198);
  r8data = D_0810298C;
  cb2b8 = D_080CB2B8;
  {
    void *t1 = sub_08016190();
    r5->f28 = (struct UnkSub *) t1;
    if (t1 == 0)
    {
      goto fail;
    }
  }
  r5->f28->b1 = 5;
  r5->f28->b2 = 8;
  r5->f28->b3 = 1;
  {
    u8 *cb = cb2b8;
    struct UnkSub *ch = r5->f28;
    s32 idx20 = (((s32) r5->f1C) * 5) << 2;
    ch->h4 = *((u16 *) (cb + idx20));
    r5->f28->h6 = r8data[0];
    r5->f28->h8 = r8data[1];
    r5->f28->hA = r8data[2];
    r5->f28->hC = r8data[3];
    r5->f28->hE = *((u16 *) ((cb2b8 + ((((s32) r5->f1C) * 5) << 2)) + 4));
    r5->f28->p10 = obj;
  }
  {
    u16 *r4data8 = r8data + 4;
    u8 *cb = cb2b8;
    void *t2;
    t2 = sub_08016190();
    r5->f48 = (struct UnkSub *) t2;
    if (t2 != 0)
    {
      goto body;
    }
    fail:
    sub_080C31E0(arg0, arg0->f24);

    goto end;
    body:
    {
      struct UnkSub *ch = r5->f48;
      ch->b1 = 1;
      ch->b2 = 8;
      ch->b3 = 1;
      {
        s32 idx20 = (((s32) r5->f1C) * 5) << 2;
        ch->h4 = *((u16 *) (cb + idx20));
        r5->f48->h6 = r8data[4];
        r5->f48->h8 = r4data8[1];
        r5->f48->hA = r4data8[2];
        r5->f48->hC = r4data8[3];
        r5->f48->hE = *((u16 *) ((cb2b8 + ((((s32) r5->f1C) * 5) << 2)) + 4));
        r5->f48->p10 = obj;
      }
    }

    *((void **) (r10_base + 4)) = sub_080B7144(arg0, -1);
    *((void **) (r10_base + 8)) = sub_080B7144(arg0, 1);
    *((void **) (r10_base + 12)) = sub_080B7174(arg0);
    *((void **) (r10_base + 16)) = sub_080B7258(arg0);
    *((void **) (r10_base + 20)) = sub_0805FAEC(arg0, 0x1C4);
    r5->b69 = 0;
    arg0->f4C = r5->f18;
    arg0->f5C = (s32) D_080CBDD0[(((s32) r5->f1C) * 20) + 18];
    r5->h4 |= 0x10;
    D_02025FF0[16] = 0;
    D_02025FF0[17] = 0;
    D_02025FF0[18] = 0;
    D_02025FF0[19] = 0;
    sub_08016664(arg0, 0);
    arg0->h2 |= 0x1000;
    {
      u8 *self = (u8 *) arg0;
      s32 *lit;
      u8 *p18;
      *((u8 *) ((self + ((*((s16 *) (self + 0x22))) * 2)) + 0x19)) = 0;
      lit = (s32 *) 0x08671BB0;
      p18 = self + 0x18;
      sub_080C31E4(p18, self + 0x22, *lit);
      *((u8 *) ((self + ((*((s16 *) (self + 0x22))) * 2)) + 0x19)) += 1;
      p18 = p18 + ((*((s16 *) (self + 0x22))) * 2);
      sub_080C31E0(arg0, *((void **) ((*((u32 *) (self + 0x14))) + ((*((u8 *) p18)) * 4))));
    }
  }
  end:
  return;

}
