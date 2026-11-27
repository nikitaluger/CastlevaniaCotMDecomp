/* Parent entity; field names keep their byte offsets from the original struct. */
typedef struct
{
  u8 _0[0x02];
  u16 flags;          /* 0x02 */
  u8 _4[0x10];
  u32 dispatch;       /* 0x14 */
  u8 _18[0x0A];
  s16 step;           /* 0x22 */
  u32 script;         /* 0x24 */
  u8 _28[0x10];
  void *sprite;       /* 0x38 */
  void *state;        /* 0x3C */
  u8 _40[0x5C];
  void (*update)(void); /* 0x9C */
  u8 _A0[0x0C];
  void *spawnParams;  /* 0xAC */
} Entity;
/* Render object allocated by allocSpriteObject. */
typedef struct
{
  u16 graphics;       /* 0x00 */
  u8 _2[0x12];
  s32 x;              /* 0x14 */
  s32 y;              /* 0x18 */
  u32 typeFlags;      /* 0x1C */
  u8 _20[4];
  void *behavior;     /* 0x24 */
  u16 behaviorParam;  /* 0x28 */
} Sprite;
/* 0xAC: spawn parameters, a pair of 16-bit coordinates. */
typedef struct
{
  s16 x;
  s16 y;
} SpawnCoord;
typedef struct
{
  void *f0;
  SpawnCoord *coord;
} SpawnParams;
/* Motion values whose halves are applied to the tracker and the state. */
typedef struct
{
  s16 f0;
  s16 f2;
  s32 f4;
  s16 f8;
  s16 fA;
} MotionData;
/* Small tracker object allocated by allocMotionTracker. */
typedef struct
{
  u8 _0;
  u8 f1;
  u16 f2;
  u16 f4;
  s16 f6;
  s16 f8;
  s16 fA;
  void *fC;
} TrackerObj;
/* Extension at state+0x48 holding the tracker, motion and position. */
typedef struct
{
  s32 f0;
  TrackerObj *tracker; /* 0x04 */
  s32 f8;
  s32 fC;
  s32 f10;
  s32 f14;
  s32 f18;
  u8 _1C[4];
  void *motion;        /* 0x20 */
} Extension;
/* Behaviour state stored on the entity at +0x3C. */
typedef struct
{
  u8 _0[8];
  void *f8;
  s32 fC;
  u8 _10[4];
  s32 f14;
  u8 _14[0x0C];
  void *script;        /* 0x24 */
  u8 _28[0x20];
  s32 behaviorIndex;   /* 0x48 */
} BehaviorState;
struct S_02025FF0
{
  u8 _0[0x18A8];
  u8 b18A8;
  u8 _1[0x18C2 - 0x18A9];
  u16 w18C2;
};
extern struct S_02025FF0 gMainWorkspace;
extern u8 gCameraState[];
extern u32 gBehaviorHandlerTable[];
extern u16 D_081008CA[];
extern u32 gMainObjTimerCallbacks[];
extern void allocWorkSlot(void *, s32, s32, s32);
extern void *allocSpriteObject(void);
extern void *allocMotionTracker(void);
extern s32 getSpawnBehaviorIndex(void);
extern void *getMotionData(void *);
extern void sub_080C31E0(void *, void *);
extern void sub_080C31E4(void *, void *, u32);
extern void sub_08095418(void);
extern void sub_08095438(void);

/* Spawn one of the gBehaviorHandlerTable behaviours: allocate the sprite and its tracker,
 * copy the spawn coordinates into the behaviour state, then advance the
 * parent's animation step and dispatch the next handler. */
/* Spawn a behaviour-driven sprite: allocate its render object and motion tracker, seed fixed-point position/motion from the spawn parameters, mark the entity ready, then advance the script step and dispatch the next handler. */ void spawnTrackedBehaviorSprite(Entity *arg0)
{
  SpawnParams *params;
  Sprite *sprite;
  s16 px;
  BehaviorState *state;
  SpawnCoord *coord;
  Extension *ext;
  u8 *stepPtr;
  TrackerObj *tracker;
  MotionData *motion;
  void *coordY;
  s32 absVal;
  void *p18;
  s32 off;
  u32 dispatchTable;
  u32 *behaviorTable;
  params = (SpawnParams *) arg0->spawnParams;
  sprite = (Sprite *) allocSpriteObject();
  if (sprite == 0)
  {
    goto fail;
  }
  arg0->sprite = sprite;
  allocWorkSlot(arg0, 0, 0x6C, 0);
  state = (BehaviorState *) arg0->state;
  if (state == 0)
  {
    goto fail;
  }
  state->script = arg0->script;
  arg0->script = (void *) sub_08095418;
  coord = params->coord;
  px = coord->x;
  state->f8 = (void *) (((s32) px) << 16);
  state->fC = (void *) (((s32) coord->y) << 16);
  sprite->graphics = (u16) (sprite->graphics | gMainWorkspace.w18C2);
  sprite->typeFlags = 0x8000000C;
  ext = (Extension *) (((u8 *) state) + 0x48);
  state->behaviorIndex = getSpawnBehaviorIndex();
  if (state->behaviorIndex < 0)
  {
    goto fail;
  }
  ext->motion = getMotionData(arg0);
  tracker = (TrackerObj *) allocMotionTracker();
  ext->tracker = tracker;
  if (tracker != 0)
  {
    goto cont;
  }
  fail:
  sub_080C31E0(arg0, arg0->script);

  return;
  cont:
  tracker->f1 = 1;

  ext->tracker->f2 = 0;
  ext->tracker->f4 = (u16) params->coord->x;
  ext->tracker->f6 = (s16) (params->coord->y + 1);
  ext->tracker->f8 = (s16) (((s32) (((s32) ((MotionData *) ext->motion)->f8) + (((u32) ((MotionData *) ext->motion)->f8) >> 31))) >> 1);
  ext->tracker->fA = (s16) (((s32) (((s32) ((MotionData *) ext->motion)->fA) + (((u32) ((MotionData *) ext->motion)->fA) >> 31))) >> 1);
  ext->tracker->fC = arg0;
  coordY = state->fC;
  ext->f8 = (s32) coordY;
  motion = (MotionData *) ext->motion;
  ext->fC = ((s32) coordY) + (((s32) motion->f0) << 16);
  absVal = motion->f4;
  if (absVal < 0)
  {
    absVal = -absVal;
  }
  ext->f10 = absVal;
  state->fC = (void *) (((s32) coordY) + (((s32) motion->f2) << 16));
  state->f14 = motion->f4;
  ext->f14 = (s32) state->f8;
  ext->f18 = (s32) state->fC;
  sprite->behavior = (void *) gBehaviorHandlerTable[state->behaviorIndex];
  sprite->behaviorParam = D_081008CA[state->behaviorIndex];
  arg0->update = (void (*)(void)) sub_08095438;
  {
    u8 *pt = gCameraState;
    u8 *pb = (u8 *) (&gMainWorkspace);
    u8 *base1;
    u8 *base2;
    u32 cidx;
    pb += 0x18A8;
    cidx = (((u32) (*pb)) + 1) * 0x40;
    base1 = pt + 0x1278;
    sprite->x = ((s32) state->f8) - (((*((u32 *) (base1 + cidx))) + 0x8000) & 0xFFFF0000);
    cidx = (((u32) (*pb)) + 1) * 0x40;
    base2 = pt + 0x127C;
    sprite->y = ((s32) state->fC) - (((*((u32 *) (base2 + cidx))) + 0xFFFF8000) & 0xFFFF0000);
  }
  arg0->flags = (u16) (arg0->flags | 0x1000);
  {
    u8 *p = (u8 *) ((u32) (arg0->step * 2) + (u32) arg0);
    p[0x19] = 0;
  }
  behaviorTable = gMainObjTimerCallbacks;
  p18 = ((u8 *) arg0) + 0x18;
  sub_080C31E4(p18, ((u8 *) arg0) + 0x22, *behaviorTable);
  {
    u8 *p = (u8 *) ((u32) (arg0->step * 2) + (u32) arg0);
    p[0x19] = (u8) (p[0x19] + 1);
  }
  stepPtr = ((u8 *) p18) + (arg0->step * 2);
  off = (*stepPtr);
  dispatchTable = (u32) arg0->dispatch;
  off <<= 2;
  sub_080C31E0(arg0, *((void **) (u8 *) ((u32) off + dispatchTable)));
  return;
}
