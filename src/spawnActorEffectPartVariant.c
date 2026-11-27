extern void startEffectTimer(void *, s32, void *);
extern void *allocEffectPart(void);
extern void cleanupFailedEffectSpawn(void *);
extern u16 scalePercentSaturate16(u16, s32);
extern void releaseActorEffectParts(void);
extern void _call_via_r1(void *, s32);
extern void _call_via_r2(void *, void *, s32);
extern u8 gGameStatus[];
extern u8 gActorEffectVariantAnimSequence[];
extern u8 gActorEffectVariantTimerData[];
extern s32 gMainObjTimerCallbacks;

/* Main workspace: the byte at 0x1510 holds the player's mirror flag. */
struct ActorEffectWorkspace
{
  u8 _0[0x1510];
  u8 mirrorFlag;
  u8 _1[0x174C - 0x1511];
  u32 spawnState;
  u32 spawnParam;
};
extern struct ActorEffectWorkspace gMainWorkspace;

/* Render part allocated for the actor's effect. */
struct ActorEffectPart
{
  u8 mode;             /* 0x00 */
  u8 mirror;           /* 0x01 */
  u8 layer;            /* 0x02 */
  u8 priority;         /* 0x03 */
  u16 tile0;           /* 0x04 */
  u16 tile1;           /* 0x06 */
  u16 tile2;           /* 0x08 */
  u16 tile3;           /* 0x0A */
  u16 anim0;           /* 0x0C */
  u16 palette;         /* 0x0E */
  u32 owner;           /* 0x10 */
  u8 _14[2];
  u16 timer;           /* 0x16 */
  u16 animSlot;        /* 0x18 */
  u8 _1A[0x24 - 0x1A];
  u32 animSequence;    /* 0x24 */
};

/* Work block reached through actor+0x6C+4. */
struct ActorEffectWork
{
  u8 _0[4];
  u32 spawnParam;      /* 0x04 */
  u8 _8[0x18 - 8];
  u32 savedHandler;    /* 0x18 */
  u8 _1C[0x2C - 0x1C];
  struct ActorEffectPart *part; /* 0x2C */
  u32 handle0;         /* 0x30 */
  u32 handle1;         /* 0x34 */
  u32 handle2;         /* 0x38 */
  u32 handle3;         /* 0x3C */
  u8 _40[0x54 - 0x40];
  u32 effectParam;     /* 0x54 */
};

/* Spawn the actor's effect part, copy the level's palette/animation settings
 * into it, install the new actor update callback, then advance the actor's
 * command script and dispatch its current step.  Bails out if allocation
 * fails. */
void spawnActorEffectPartVariant(u8 *actor)
{
  u8 *workPtr = *((u8 **) (actor + 0x6C));
  struct ActorEffectWork *state = (struct ActorEffectWork *) (workPtr + 4);
  u8 *sprite = *((u8 **) (actor + 0x38));
  u8 *params = gGameStatus;
  struct ActorEffectPart *part;
  s32 zero;
  s32 slotZero;
  u8 *scriptState;
  u8 *stepSlot;
  u8 *stepParam;
  u32 *stepCallbacks;

  part = (struct ActorEffectPart *) allocEffectPart();
  state->part = part;
  if (part == NULL)
  {
    cleanupFailedEffectSpawn(actor);
    return;
  }
  zero = 0;
  state->handle0 = zero;
  state->handle1 = zero;
  state->handle2 = zero;
  state->handle3 = zero;
  state->part->mirror = gMainWorkspace.mirrorFlag & 1;
  state->part->layer = 2;
  state->part->priority = 8;
  slotZero = 0;
  state->part->tile0 = params[0xC1 << 2];
  state->part->tile1 = 6;
  state->part->tile2 = 6;
  state->part->tile3 = zero;
  state->part->anim0 = zero;
  state->part->palette = scalePercentSaturate16(*((u16 *) (params + 0x2E2)), 0x2D);
  state->part->timer = 0x0F;
  state->part->animSlot = 0x31;
  state->part->owner = (u32) sprite;
  state->savedHandler = *((u32 *) (actor + 0x24));
  *((u32 *) (actor + 0x24)) = (u32) releaseActorEffectParts;
  *((u32 *) (sprite + 0x24)) = (u32) gActorEffectVariantAnimSequence;
  startEffectTimer(workPtr + 0x20, 0, gActorEffectVariantTimerData);
  *((u32 *) (workPtr + 4)) = *((u32 *) (((u8 *) (&gMainWorkspace)) + 0x174C));
  state->spawnParam = *((u32 *) (((u8 *) (&gMainWorkspace)) + 0x1750));
  state->effectParam = *((u32 *) (actor + 0x7C));
  *((u8 *) ((actor + ((*((s16 *) (actor + 0x22))) * 2)) + 0x19)) = slotZero;
  stepCallbacks = (u32 *) &gMainObjTimerCallbacks;
  scriptState = actor + 0x18;
  _call_via_r2(scriptState, actor + 0x22, *stepCallbacks);
  stepSlot = (u8 *) ((s16) *((s16 *) (actor + 0x22)) * 2 + (u32) actor);
  *((u8 *) (stepSlot + 0x19)) = (u8) (*((u8 *) (stepSlot + 0x19)) + 1);
  stepParam = scriptState + (s16) *((s16 *) (actor + 0x22)) * 2;
  _call_via_r1(actor, *((s32 *) ((u32) (*stepParam) * 4 + *((u32 *) (actor + 0x14)))));
}
