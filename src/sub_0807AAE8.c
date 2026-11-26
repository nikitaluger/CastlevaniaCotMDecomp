extern void sub_08003A6C(void *, s32, s32);
extern void *allocEffectPart(void);
extern void sub_0806D2D0(void *);
extern s16 sub_0806D62C(u16, s32);
extern void sub_080C31E0(void *, s32);
extern void sub_080C31E4(void *, void *, s32);
extern u8 gGameStatus[];
extern u8 D_084DB5E8[];
extern u8 D_084DB788[];
extern s32 gMainObjTimerCallback;

struct EffectPart {
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
struct EffectGraphic { u8 _0[4]; void *f4; };
struct EffectState {
  u8 _0[4];
  void *f4;
  u8 _1[0x10 - 8];
  void *f10;
  u8 _2[0x18 - 0x14];
  void *f18;
  u8 _3[0x2C - 0x1C];
  struct EffectPart *f2C;
  void *f30;
  void *f34;
  void *f38;
  void *f3C;
};
struct EffectOwner {
  u8 _0[0x14];
  void *f14;
  u8 _1[0xA];
  s16 f22;
  void *f24;
  u8 _2[0x10];
  void *f38;
  u8 _3[0x30];
  void *f6C;
  u8 _4[0x0C];
  void *f7C;
  u8 _5[0xC];
  void *f8C;
  u8 _6[0xC];
  void *f9C;
};
struct ScriptStep { u8 _0[0x19]; u8 f19; };

/* Effect script step: allocate an effect part, fill it from the shared parameter
 * table, wire the effect object's graphic and callback pointers to this owner,
 * then clear the current step's byte, advance the script and dispatch the new
 * command handler. */
void sub_0807AAE8(struct EffectOwner *self)
{
  void *effectObj;
  struct EffectState *effectState;
  void *mainObj;
  u8 *paramTable;
  struct EffectPart *newPart;
  s32 zero;
  u32 stepOffset;
  effectObj = self->f6C;
  effectState = (struct EffectState *)((u8 *)effectObj + 4);
  mainObj = self->f38;
  paramTable = gGameStatus;
  newPart = allocEffectPart();
  effectState->f2C = newPart;
  if (newPart == NULL) {
    sub_0806D2D0(self);
    return;
  }
  zero = 0;
  effectState->f30 = (void *)zero;
  effectState->f34 = (void *)zero;
  effectState->f38 = (void *)zero;
  effectState->f3C = (void *)zero;
  newPart->f01 = zero;
  effectState->f2C->f02 = 2;
  effectState->f2C->f03 = 8;
  effectState->f2C->f04 = paramTable[0xC1 * 4];
  effectState->f2C->f06 = 0x14;
  effectState->f2C->f08 = 0x14;
  effectState->f2C->f0A = zero;
  effectState->f2C->f0C = zero;
  effectState->f2C->f0E = sub_0806D62C(*(u16 *)(paramTable + 0x2E2), 0x7A);
  effectState->f2C->f16 = 0x3C;
  effectState->f2C->f18 = 0x58;
  effectState->f2C->f10 = mainObj;
  effectState->f18 = self->f24;
  self->f24 = (void *)0x0808449D;
  ((struct EffectPart *)mainObj)->f24 = (void *)D_084DB5E8;
  sub_08003A6C((u8 *)effectObj + 0x20, 0, (s32)D_084DB788);
  ((struct EffectGraphic *)effectObj)->f4 = self->f7C;
  effectState->f4 = self->f8C;
  effectState->f10 = self->f9C;
  ((struct ScriptStep *)((u8 *)self + self->f22 * 2))->f19 = zero;
  {
    s32 *cueTable = &gMainObjTimerCallback;
    u8 *scriptPtr = (u8 *)self + 0x18;
    sub_080C31E4(scriptPtr, (u8 *)self + 0x22, *cueTable);
    ((struct ScriptStep *)((u8 *)self + self->f22 * 2))->f19++;
    stepOffset = self->f22 * 2;
    sub_080C31E0(self, *(s32 *)((u8 *)self->f14 + *(u8 *)((u32)scriptPtr + stepOffset) * 4));
  }
}
