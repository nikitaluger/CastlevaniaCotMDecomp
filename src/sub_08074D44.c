extern void sub_08003A6C(void *, s32, s32);
extern void *allocEffectPart(void);
extern void sub_0806D2D0(void *);
extern u32 scalePercentSaturate16(u32, u32);
extern void sub_080C31E0(void *, s32);
extern void sub_080C31E4(void *, void *, s32);
extern void sub_0808449C(void);
struct S_02025FF0
{
  u8 _0[0x1510];
  u8 f1510;
  u8 _1[0x174C - 0x1511];
  u32 f174C;
  u32 f1750;
};
extern struct S_02025FF0 gMainWorkspace;
extern u8 gGameStatus[];
extern void *D_02027740;
extern u8 D_0849A5F0[];
extern u8 D_0849A610[];
extern s32 gMainObjTimerCallbacks;
struct S_r4
{
  u8 _0;
  u8 f01;
  u8 f02;
  u8 f03;
  u16 f04;
  u16 f06;
  u16 f08;
  u16 f0A;
  u16 f0C;
  u16 f0E;
  void *f10;
  u8 _2[2];
  u16 f16;
  u16 f18;
  u8 _3[0x24 - 0x1A];
  void *f24;
};
struct S_5
{
  u8 _0[4];
  void *f4;
  u8 _1[0x18 - 8];
  void *f18;
  u8 _2[0x2C - 0x1C];
  struct S_r4 *f2C;
  u32 f30;
  u32 f34;
  u32 f38;
  u32 f3C;
};
struct S_5b
{
  u8 _0[0x10];
  u32 f10;
  u8 _1[0x54 - 0x14];
  u32 f54;
  u32 f58;
};
struct S_A0
{
  u8 _0[0x14];
  u32 table;
  u8 _1[0x0A];
  s16 idx;
  u32 callback;
  u8 _2[0x38 - 0x28];
  void *ptr38;
  u8 _3[0x6C - 0x3C];
  void *ptr6C;
  u8 _4[0x7C - 0x70];
  u32 val7C;
  u8 _5[0x8C - 0x80];
  u32 val8C;
};
struct Sub
{
  u8 _0[0x19];
  u8 f19;
};

/* Initialize a visual-effect entity: allocate and configure its sub-object,
 * install the cleanup callback and command handlers, then advance its script. */
void sub_08074D44(struct S_A0 *obj)
{
  void *fx;
  struct S_5 *state;
  void *owner;
  u8 *work;
  struct S_r4 *sub;
  s32 zero;
  u32 off;
  u8 *gState;
  u8 *stepSlot;
  fx = obj->ptr6C;
  state = (struct S_5 *) (((u8 *) fx) + 4);
  owner = obj->ptr38;
  work = gGameStatus;
  sub = allocEffectPart();
  state->f2C = sub;
  if (sub == NULL)
  {
    sub_0806D2D0(obj);
    return;
  }
  zero = 0;
  state->f30 = (u32) zero;
  state->f34 = (u32) zero;
  state->f38 = (u32) zero;
  state->f3C = (u32) zero;
  gState = (u8 *) &gMainWorkspace;
  sub->f01 = gState[0x1510] & 1;
  state->f2C->f02 = 2;
  state->f2C->f03 = 8;
  state->f2C->f04 = *((u8 *) (work + 0x304));
  state->f2C->f06 = 8;
  state->f2C->f08 = 8;
  state->f2C->f0A = 0;
  state->f2C->f0C = 0;
  state->f2C->f0E = scalePercentSaturate16(*((u16 *) (work + 0x2E2)), 0x64);
  state->f2C->f16 = 0x0F;
  state->f2C->f18 = 0x30;
  state->f2C->f10 = owner;
  state->f18 = obj->callback;
  obj->callback = (u32) sub_0808449C;
  ((struct S_r4 *) owner)->f24 = (void *) D_0849A5F0;
  sub_08003A6C(((u8 *) fx) + 0x20, 0, (s32) D_0849A610);
  *((u32 *) (((u8 *) fx) + 0x04)) = *((u32 *) (gState + 0x174C));
  state->f4 = *((u32 *) (gState + 0x1750));
  ((struct S_5b *)state)->f54 = obj->val7C;
  ((struct S_5b *)state)->f58 = 0;
  ((struct S_5b *)state)->f10 = 1;
  ((struct Sub *) (((u8 *) obj) + (obj->idx * 2)))->f19 = zero;
  {
    s32 *fn = &gMainObjTimerCallbacks;
    u8 *p18 = ((u8 *) obj) + 0x18;
    sub_080C31E4(p18, ((u8 *) obj) + 0x22, *fn);
    stepSlot = (u8 *) ((s16) obj->idx * 2 + (u32) obj);
    *((u8 *) (stepSlot + 0x19)) = (u8) (*((u8 *) (stepSlot + 0x19)) + 1);
    off = obj->idx;
    off = off * 2;
    sub_080C31E0(obj, *((s32 *) (((u8 *) obj->table) + ((*((u8 *) (((u32) p18) + off))) * 4))));
  }
}
