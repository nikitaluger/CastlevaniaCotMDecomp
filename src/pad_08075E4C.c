/* Spawn a child render part for an actor's current script step: allocate from
 * the effect pool, seed it from gGameStatus, install releaseActorEffectParts as
 * the actor's handler with a sprite-flip-dependent velocity, start the child's
 * timer, then advance to and dispatch the next script command. */
extern void startEffectTimer(void *, s32, void *);
extern void *allocEffectPart(void);
extern void cleanupFailedEffectSpawn(void *);
extern u16 scalePercentSaturate16(u16, s32);
extern void _call_via_r1(void *, s32);
extern void _call_via_r2(void *, void *, s32);
extern void releaseActorEffectParts(void);
extern u8 gGameStatus[];
extern s32 gMainObjTimerCallbacks;

/* Animation sequence and script-timer table installed on the spawned child. */
#define CHILD_EFFECT_ANIM_SEQ  0x084A65BC
#define CHILD_EFFECT_TIMER_CB  0x084A67D0
/* Thumb entry of releaseActorEffectParts, installed as the actor's handler. */
#define ACTOR_EFFECT_RELEASE_CB 0x0808449D

/* Global workspace: byte 0x1510 supplies the new part's active parity. */
struct SaveData
{
  u8 _0[0x1510];
  u8 parity;
};
extern struct SaveData gMainWorkspace;

/* Render part allocated by allocEffectPart for the actor's child effect. */
struct EffectPart
{
  u8 unused;
  u8 active;
  u8 type;
  u8 subtype;
  u16 dataWord;
  u16 field6;
  u16 field8;
  u16 fieldA;
  u16 fieldC;
  u16 scaledValue;
  u32 sprite;
  u8 _14[2];
  u16 lifetime;
  u16 field18;
  u8 _1A[0x0A];
  u32 f24;
};

/* Work state reached through the actor's +0x6C pointer (plus four bytes):
 * +0x18 is the saved update handler, +0x2C the spawned part, +0x30..0x3C
 * scratch handles and +8/+0xC the child's X/Y velocity. */
struct EffectOwner
{
  u8 _0[4];
  u32 worldY;
  u8 _8[0x18 - 8];
  u32 oldHandler;
  u8 _1C[0x2C - 0x1C];
  struct EffectPart *child;
  u32 handle0, handle1, handle2, handle3;
  u8 _40[0x54 - 0x40];
  u32 field54;
};

void pad_08075E4C(u8 *actor)
{
  u8 *stateBase = *((u8 **) (actor + 0x6C));
  struct EffectOwner *state = (struct EffectOwner *) (stateBase + 4);
  u8 *sprite = *((u8 **) (actor + 0x38));
  u8 *params = gGameStatus;
  struct EffectPart *child;
  u8 *scriptPtr;
  u8 *stepSlot;
  u8 *stepParam;
  u32 *callbacks;
  u16 flipFlag;
  s32 velocityX;

  child = (struct EffectPart *) allocEffectPart();
  state->child = child;
  if (child == NULL)
  {
    cleanupFailedEffectSpawn(actor);
    return;
  }
  state->handle0 = 0;
  state->handle1 = 0;
  state->handle2 = 0;
  state->handle3 = 0;
  state->child->active = gMainWorkspace.parity & 1;
  state->child->type = 2;
  state->child->subtype = 8;
  state->child->dataWord = params[0xC1 << 2];
  state->child->field6 = 4;
  state->child->field8 = 4;
  state->child->fieldA = 0;
  state->child->fieldC = 0;
  state->child->scaledValue = scalePercentSaturate16(*((u16 *) (params + 0x2E2)), 0x2D);
  state->child->lifetime = 5;
  state->child->field18 = 0x82;
  state->child->sprite = (u32) sprite;
  state->oldHandler = *((u32 *) (actor + 0x24));
  *((u32 *) (actor + 0x24)) = ACTOR_EFFECT_RELEASE_CB;
  *((u32 *) (sprite + 0x24)) = CHILD_EFFECT_ANIM_SEQ;
  startEffectTimer(stateBase + 0x20, 0, (void *) CHILD_EFFECT_TIMER_CB);
  *((u32 *) (stateBase + 4)) = *((u32 *) (((u8 *) (&gMainWorkspace)) + 0x174C));
  state->worldY = *((u32 *) (((u8 *) (&gMainWorkspace)) + 0x1750));
  flipFlag = *((u16 *) (sprite + 2)) & 0x10;
  velocityX = 0x80 << 10;
  if (flipFlag != 0) velocityX = -0x20000;
  *((u32 *) ((u8 *) state + 8)) = velocityX;
  *((u32 *) ((u8 *) state + 0xC)) = 0xFFFC0000;
  {
    u8 zero = 0;
    *((u8 *) ((actor + ((*((s16 *) (actor + 0x22))) * 2)) + 0x19)) = zero;
  }
  callbacks = (u32 *) &gMainObjTimerCallbacks;
  scriptPtr = actor + 0x18;
  _call_via_r2(scriptPtr, actor + 0x22, *callbacks);
  stepSlot = (u8 *) ((s16) *((s16 *) (actor + 0x22)) * 2 + (u32) actor);
  *((u8 *) (stepSlot + 0x19)) = (u8) (*((u8 *) (stepSlot + 0x19)) + 1);
  stepParam = scriptPtr + (s16) *((s16 *) (actor + 0x22)) * 2;
  _call_via_r1(actor, *((s32 *) ((u32) (*stepParam) * 4 + *((u32 *) (actor + 0x14)))));
}
