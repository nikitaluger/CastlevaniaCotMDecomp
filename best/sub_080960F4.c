extern void *sub_0800355C(void);
extern s32 sub_0800168C(void *, s32, s32, s32);
extern void sub_080C31E0(void *, s32);
extern void sub_080C31E4(void *, void *, s32);
extern void sub_08096794(void);
extern void sub_080967BC(void);
extern s32 sub_0809683C(void);
extern void sub_0801131C(void *, void *, s32);
extern void sub_08011368(void *, void *, s16, s32);
extern void *sub_08015914(void);
extern void sub_08005E80(s32);
struct Child96104
{
  u8 _0;
  u8 f1;
  u16 f2;
  u16 f4;
  u16 f6;
  u16 f8;
  u16 fA;
  s32 fC;
};
struct Sub96104
{
  s32 f0;
  struct Child96104 *f4;
  s32 f8;
  s32 fC;
  u16 f10;
  u16 f12;
};
struct Ent96104
{
  u8 _0[8];
  s32 f8;
  s32 fC;
  s32 f10;
  u8 _14[0x10];
  s32 f24;
  u8 _28[0x20];
  s32 f48;
  struct Sub96104 *f4C;
};
struct Arg96104
{
  u8 _0[2];
  u16 f2;
  u8 _4[0x10];
  u32 *f14;
  u8 _18[0xA];
  s16 f22;
  s32 f24;
  u8 _28[0x10];
  void *f38;
  struct Ent96104 *f3C;
  u8 _40[0x5C];
  void *f9C;
};
extern u8 D_02021E90[];
extern struct 
{
  u8 _0[0x18A8];
  u8 f18A8;
  u8 _18A9[0x19];
  u16 f18C2;
} D_02025FF0;
extern s16 D_08100B1C[];
extern s32 D_08671BB0[];
void sub_080960F4(struct Arg96104 *owner)
{
  void *sprite;
  unsigned short new_var2;
  struct Ent96104 *logic;
  int new_var;
  void *coords;
  struct Sub96104 *sub;
  struct Child96104 *child;
  u32 zero;
  s32 idx;
  s32 *cmdTable;
  u8 *cmdLog;
  struct Child96104 *new_var3;
  u16 t2;
  new_var = 0;
  sprite = sub_0800355C();
  if (sprite == 0)
  {
    goto fail;
  }
  owner->f38 = sprite;
  sub_0800168C(owner, 0, 0x60, 0);
  new_var2 = new_var;
  logic = owner->f3C;
  if (logic == 0)
  {
    goto fail;
  }
  coords = ((u8 *) logic) + 0x34;
  logic->f24 = owner->f24;
  owner->f24 = (s32) sub_08096794;
  logic->f8 = 0xFFF00000;
  logic->fC = 0x01270000;
  t2 = *((u16 *) sprite) | D_02025FF0.f18C2;
  zero = new_var2;
  *((u16 *) sprite) = t2;
  *((u32 *) (((u8 *) sprite) + 0x1C)) = 0x8000000C;
  sub = (struct Sub96104 *) (((u8 *) logic) + 0x48);
  idx = sub_0809683C();
  logic->f48 = idx;
  if (idx < 0)
  {
    goto fail;
  }
  sub_0801131C(sprite, coords, (idx * 0xC) + 0x08100B10);
  child = sub_08015914();
  sub->f4 = child;
  if (child != 0)
  {
    goto cont;
  }
  fail:
  sub_080C31E0(owner, owner->f24);

  goto end;
  cont:
  sub->f4->f1 = 7;

  sub->f4->f2 = zero;
  sub->f4->f4 = 0xFFF0;
  sub->f4->f6 = 0x128;
  sub->f4->f8 = 0x10;
  (new_var3 = sub->f4)->fA = 8;
  new_var3->fC = (s32) owner;
  logic->f10 = 0x10000;
  sub->f8 = logic->f8;
  sub->fC = logic->fC;
  sub->f10 = zero;
  sub->f12 = 1;
  owner->f9C = sub_080967BC;
  sub_08011368(sprite, coords, D_08100B1C[logic->f48], 1);
  sub_08005E80(0x1BE);
  {
    u8 *scrollBase = (u8 *) (&D_02021E90);
    {
      u32 offset = 0x1278;
      *((u32 *) (((u8 *) sprite) + 0x14)) = logic->f8 - (((*((u32 *) ((scrollBase + offset) + ((D_02025FF0.f18A8 + 1) << 6)))) + 0x8000) & 0xFFFF0000);
    }
    {
      u32 offset = 0x127C;
      *((u32 *) (((u8 *) sprite) + 0x18)) = logic->fC - (((*((u32 *) ((scrollBase + offset) + ((D_02025FF0.f18A8 + 1) << 6)))) + 0xFFFF8000) & 0xFFFF0000);
      do
      {
      }
      while (0);
    }
  }
  owner->f2 |= 0x1000;
  *((u8 *) ((((u8 *) owner) + (owner->f22 * 2)) + 0x19)) = zero;
  cmdTable = D_08671BB0;
  cmdLog = ((u8 *) owner) + 0x18;
  sub_080C31E4(cmdLog, &owner->f22, *cmdTable);
  *((u8 *) ((((u8 *) owner) + (owner->f22 * 2)) + 0x19)) += 1;
  cmdLog += owner->f22 * 2;
  sub_080C31E0(owner, owner->f14[*cmdLog]);
  end:
  return;

}
