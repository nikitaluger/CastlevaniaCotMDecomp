extern void startEffectTimer(void *, s32, s32);
extern void *allocEffectPart(void);
extern void cleanupFailedEffectSpawn(void *);
extern u32 scalePercentSaturate16(u32, u32);
extern void _call_via_r1(void *, s32);
extern void _call_via_r2(void *, void *, s32);
extern void releaseActorEffectParts(void);

/* Main workspace fields used while spawning the effect. */
struct ActorEffectWorkspace
{
  u8 _0[0x1510];
  u8 mirrorFlag;                 /* 0x1510: player's horizontal-flip bit */
  u8 _1[0x174C - 0x1511];
  u32 spawnState;                /* 0x174C */
  u32 spawnParam;                /* 0x1750 */
};
extern struct ActorEffectWorkspace gMainWorkspace;
extern u8 gGameStatus[];
extern void *D_02027740;
extern u8 gActorEffectAnimSequence[];
extern u8 gActorEffectTimerData[];
extern s32 gMainObjTimerCallbacks;

/* Render part allocated for the actor's effect. */
struct ActorEffectPart
{
  u8 mode;                       /* 0x00 */
  u8 mirror;                     /* 0x01 */
  u8 layer;                      /* 0x02 */
  u8 priority;                   /* 0x03 */
  u16 tile0;                     /* 0x04 */
  u16 tile1;                     /* 0x06 */
  u16 tile2;                     /* 0x08 */
  u16 tile3;                     /* 0x0A */
  u16 anim0;                     /* 0x0C */
  u16 palette;                   /* 0x0E */
  void *owner;                   /* 0x10 */
  u8 _14[2];
  u16 timer;                     /* 0x16 */
  u16 animSlot;                  /* 0x18 */
  u8 _1A[0x24 - 0x1A];
  void *animSequence;            /* 0x24 */
};

/* Work block reached through object+0x6C+4. */
struct ActorEffectWork
{
  u8 _0[4];
  void *spawnState;              /* 0x04 */
  u8 _8[0x18 - 8];
  void *savedHandler;            /* 0x18 */
  u8 _1C[0x2C - 0x1C];
  struct ActorEffectPart *part;  /* 0x2C */
  u32 handle0;                   /* 0x30 */
  u32 handle1;                   /* 0x34 */
  u32 handle2;                   /* 0x38 */
  u32 handle3;                   /* 0x3C */
};

struct ActorEffectWorkTail
{
  u8 _0[0x10];
  u32 initFlag;                  /* 0x10: set to 1 */
  u8 _1[0x54 - 0x14];
  u32 effectParam;               /* 0x54 */
  u32 reserved;                  /* 0x58 */
};

/* Scripted actor that owns this effect. */
struct ActorEffectOwner
{
  u8 _0[0x14];
  u32 scriptTable;               /* 0x14 */
  u8 _1[0x0A];
  s16 stepIndex;                 /* 0x22 */
  u32 cleanupCallback;           /* 0x24 */
  u8 _2[0x38 - 0x28];
  void *sprite;                  /* 0x38 */
  u8 _3[0x6C - 0x3C];
  void *workPtr;                 /* 0x6C */
  u8 _4[0x7C - 0x70];
  u32 effectParam;               /* 0x7C */
  u8 _5[0x8C - 0x80];
  u32 initialized;               /* 0x8C */
};

/* One two-byte script step: its parameter byte lives at +0x19. */
struct ActorEffectStepSlot
{
  u8 _0[0x19];
  u8 stepParam;
};

/* Spawn and configure the actor's effect part, install the cleanup callback
 * and its timers, then dispatch the actor's current script step. */
void spawnActorEffectPart(struct ActorEffectOwner *obj)
{
  void *fx;
  struct ActorEffectWork *state;
  void *owner;
  u8 *work;
  struct ActorEffectPart *sub;
  s32 zero;
  u32 off;
  u8 *gState;
  u8 *stepSlot;
  fx = obj->workPtr;
  state = (struct ActorEffectWork *) (((u8 *) fx) + 4);
  owner = obj->sprite;
  work = gGameStatus;
  sub = allocEffectPart();
  state->part = sub;
  if (sub == NULL)
  {
    cleanupFailedEffectSpawn(obj);
    return;
  }
  zero = 0;
  state->handle0 = (u32) zero;
  state->handle1 = (u32) zero;
  state->handle2 = (u32) zero;
  state->handle3 = (u32) zero;
  gState = (u8 *) &gMainWorkspace;
  sub->mirror = gState[0x1510] & 1;
  state->part->layer = 2;
  state->part->priority = 8;
  state->part->tile0 = *((u8 *) (work + 0x304));
  state->part->tile1 = 8;
  state->part->tile2 = 8;
  state->part->tile3 = 0;
  state->part->anim0 = 0;
  state->part->palette = scalePercentSaturate16(*((u16 *) (work + 0x2E2)), 0x64);
  state->part->timer = 0x0F;
  state->part->animSlot = 0x30;
  state->part->owner = owner;
  state->savedHandler = obj->cleanupCallback;
  obj->cleanupCallback = (u32) releaseActorEffectParts;
  ((struct ActorEffectPart *) owner)->animSequence = (void *) gActorEffectAnimSequence;
  startEffectTimer(((u8 *) fx) + 0x20, 0, (s32) gActorEffectTimerData);
  *((u32 *) (((u8 *) fx) + 0x04)) = *((u32 *) (gState + 0x174C));
  state->spawnState = *((u32 *) (gState + 0x1750));
  ((struct ActorEffectWorkTail *)state)->effectParam = obj->effectParam;
  ((struct ActorEffectWorkTail *)state)->reserved = 0;
  ((struct ActorEffectWorkTail *)state)->initFlag = 1;
  ((struct ActorEffectStepSlot *) (((u8 *) obj) + (obj->stepIndex * 2)))->stepParam = zero;
  {
    s32 *fn = &gMainObjTimerCallbacks;
    u8 *p18 = ((u8 *) obj) + 0x18;
    _call_via_r2(p18, ((u8 *) obj) + 0x22, *fn);
    stepSlot = (u8 *) ((s16) obj->stepIndex * 2 + (u32) obj);
    *((u8 *) (stepSlot + 0x19)) = (u8) (*((u8 *) (stepSlot + 0x19)) + 1);
    off = obj->stepIndex;
    off = off * 2;
    _call_via_r1(obj, *((s32 *) (((u8 *) obj->scriptTable) + ((*((u8 *) (((u32) p18) + off))) * 4))));
  }
}
