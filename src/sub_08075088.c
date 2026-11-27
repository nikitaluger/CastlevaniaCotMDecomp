extern void sub_08003A6C(void *, s32, void *);
extern void *allocEffectPart(void);
extern void sub_0806D2D0(void *);
extern u16 scalePercentSaturate16(u16, s32);
extern void sub_0808449C(void);
extern void sub_080C31E0(void *, s32);
extern void sub_080C31E4(void *, void *, s32);
extern u8 gGameStatus[];
extern u8 D_0849A844[];
extern u8 D_0849A864[];
extern s32 gScriptStepCallbackTable;

/* Saved-game flags: the byte at 0x1510 holds the player's mirror/flip bit. */
struct SaveData
{
  u8 _0[0x1510];
  u8 b1510;
};
extern struct SaveData gMainWorkspace;

/* Effect part: an animation/sprite object spawned by the actor. */
struct EffectPart
{
  u8 f0, f1, f2, f3;
  u16 f4, f6, f8, fA, fC, fE;
  u32 f10;
  u8 _14[2];
  u16 f16, f18;
  u8 _1A[0x0A];
  u32 f24;
};

/* Owner record at actor+0x6C+4: holds the effect part and its update state. */
struct EffectOwner
{
  u8 _0[4];
  u32 f04;
  u8 _8[0x18 - 8];
  u32 f18;
  u8 _1C[0x2C - 0x1C];
  struct EffectPart *f2C;
  u32 f30, f34, f38, f3C;
  u8 _40[0x54 - 0x40];
  u32 f54;
};

/* Spawn the actor's effect part, copy the level's palette/animation settings
 * into it, install the new actor update callback, then advance the actor's
 * command script and dispatch its current step.  Bails out if allocation
 * fails. */
void sub_08075088(u8 *actor)
{
  u8 *groupBase = *((u8 **) (actor + 0x6C));
  struct EffectOwner *group = (struct EffectOwner *) (groupBase + 4);
  u8 *sprite = *((u8 **) (actor + 0x38));
  u8 *params = gGameStatus;
  struct EffectPart *spawn;
  s32 zero;
  s32 slotZero;
  u8 *scriptState;
  u8 *stepSlot;
  u8 *stepParam;
  u32 *stepCallbacks;

  spawn = (struct EffectPart *) allocEffectPart();
  group->f2C = spawn;
  if (spawn == NULL)
  {
    sub_0806D2D0(actor);
    return;
  }
  zero = 0;
  group->f30 = zero;
  group->f34 = zero;
  group->f38 = zero;
  group->f3C = zero;
  group->f2C->f1 = gMainWorkspace.b1510 & 1;
  group->f2C->f2 = 2;
  group->f2C->f3 = 8;
  slotZero = 0;
  group->f2C->f4 = params[0xC1 << 2];
  group->f2C->f6 = 6;
  group->f2C->f8 = 6;
  group->f2C->fA = zero;
  group->f2C->fC = zero;
  group->f2C->fE = scalePercentSaturate16(*((u16 *) (params + 0x2E2)), 0x2D);
  group->f2C->f16 = 0x0F;
  group->f2C->f18 = 0x31;
  group->f2C->f10 = (u32) sprite;
  group->f18 = *((u32 *) (actor + 0x24));
  *((u32 *) (actor + 0x24)) = (u32) sub_0808449C;
  *((u32 *) (sprite + 0x24)) = (u32) D_0849A844;
  sub_08003A6C(groupBase + 0x20, 0, D_0849A864);
  *((u32 *) (groupBase + 4)) = *((u32 *) (((u8 *) (&gMainWorkspace)) + 0x174C));
  group->f04 = *((u32 *) (((u8 *) (&gMainWorkspace)) + 0x1750));
  group->f54 = *((u32 *) (actor + 0x7C));
  *((u8 *) ((actor + ((*((s16 *) (actor + 0x22))) * 2)) + 0x19)) = slotZero;
  stepCallbacks = (u32 *) 0x08671BB0;
  scriptState = actor + 0x18;
  sub_080C31E4(scriptState, actor + 0x22, *stepCallbacks);
  stepSlot = (u8 *) ((s16) *((s16 *) (actor + 0x22)) * 2 + (u32) actor);
  *((u8 *) (stepSlot + 0x19)) = (u8) (*((u8 *) (stepSlot + 0x19)) + 1);
  stepParam = scriptState + (s16) *((s16 *) (actor + 0x22)) * 2;
  sub_080C31E0(actor, *((s32 *) ((u32) (*stepParam) * 4 + *((u32 *) (actor + 0x14)))));
}
