void *allocSpriteObject(void);
void allocWorkSlot(void *, s32, s32, s32);
void installUpdateHandler(void *, void *, void *);
void initSpawnedObject(void *, void *, void *, void *, s32);
void initThreePartSpriteGfx(void *, void *, s32, s32);
void setObjectAnimation(void *, void *, s32, s32);
void loadEffectPalette(void *);
void *allocEffectPart(void);
void *spawnParamChild(void *, s32);
void *spawnKind1C1Child(void *);
void *spawnKind1C3Child(void *);
void *spawnBudgetedEffect(void *, s32);
void registerScriptObject(void *, s32);
void sub_080C31E4(void *, void *, void *);
void sub_080C31E0(void *, void *);
extern u8 gThreePartEffectPalette[];
extern u16 gPairedPoseAttrs[];
extern u8 gSpriteKindTable[];
extern s16 gEffectGfxTable[];
extern u32 gMainWorkspace[];
extern void *gScriptStepCallbackTable;

/* 0x34-byte render part returned by allocEffectPart. */
struct Effect {
    u8 unused;      /* 0x00 */
    u8 active;      /* 0x01 */
    u8 param2;      /* 0x02 */
    u8 param3;      /* 0x03 */
    u16 tile;       /* 0x04 */
    u16 p0;         /* 0x06 */
    u16 p1;         /* 0x08 */
    u16 p2;         /* 0x0A */
    u16 p3;         /* 0x0C */
    u16 tile2;      /* 0x0E */
    void *sprite;   /* 0x10 */
};
/* State block at thread+0x3C (0x70 bytes from allocWorkSlot). */
struct State { u8 pad0[4]; u16 flags; u8 pad6[0x12]; s32 spawnFlags; s16 kind; u8 pad1E[0xA]; struct Effect *mainPart; u8 pad2C[0x8]; void *gfxSlot; u8 pad38[0x10]; struct Effect *secondPart; u8 pad4C[0x1D]; u8 stateByte; };
/* Script thread / command state (the argument). */
struct Thread { u8 pad0[2]; u16 flags; s32 field4; u8 pad8[0xC]; void **scriptTable; u8 scriptBytes[4]; u8 pad1C[3]; u8 flag1F; u8 pad20[2]; s16 stateIndex; void *savedHandler; u8 pad28[0x10]; void *sprite; struct State *state; u8 pad40[0xC]; s32 spawnFlags; u8 pad50[0xC]; s32 effectTile; u8 pad60[0x4C]; void *scriptRef; };

/* Spawn the kind-0x66 three-part scripted object: allocate its sprite and state
 * block, build two render parts from the paired-pose table, spawn five children,
 * then hand control back to the script interpreter. */
void scriptCmdSpawnThreePartObject(struct Thread *thread)
{
  void *scriptRef;
  void *sprite;
  struct State *state;
  void *gfxSlot;
  u8 *childSlots;
  u16 *poseAttrs;
  u8 *kindTable;
  scriptRef = thread->scriptRef;
  sprite = allocSpriteObject();
  if (sprite == 0) goto fail;
  thread->sprite = sprite;
  allocWorkSlot(thread, 0, 0x70, 0);
  if ((*((u32 *) (((u8 *) thread) + 0x3C))) == 0) goto fail;
  *((s32 *) (((u8 *) sprite) + 0x1C)) = 0x8000000A;
  state = thread->state;
  gfxSlot = ((u8 *) state) + 0x34;
  childSlots = ((u8 *) state) + 0x48;
  installUpdateHandler(thread, state, (void *) 0x080B4ACD);
  initSpawnedObject(thread, sprite, state, scriptRef, 0x66);
  initThreePartSpriteGfx(sprite, gfxSlot, 0x10, 3);
  setObjectAnimation(sprite, gfxSlot, 0, 1);
  loadEffectPalette(gThreePartEffectPalette);
  poseAttrs = gPairedPoseAttrs;
  {
    void *newPart = allocEffectPart();
    state->mainPart = (struct Effect *) newPart;
    if (newPart == 0) goto fail;
  }
  state->mainPart->active = 5;
  state->mainPart->param2 = 8;
  state->mainPart->param3 = 1;
  {
    struct Effect *part = state->mainPart;
    s32 kindOffset;
    kindTable = gSpriteKindTable;
    kindOffset = (((s32) state->kind) * 5) << 2;
    part->tile = *((u16 *) (kindTable + kindOffset));
    state->mainPart->p0 = poseAttrs[0];
    state->mainPart->p1 = poseAttrs[1];
    state->mainPart->p2 = poseAttrs[2];
    state->mainPart->p3 = poseAttrs[3];
    state->mainPart->tile2 = *((u16 *) (kindTable + ((((s32) state->kind) * 5) << 2) + 4));
    state->mainPart->sprite = sprite;
  }
  {
    u16 *poseParams = poseAttrs + 4;
    state->secondPart = (struct Effect *) allocEffectPart();
    if (state->secondPart != 0) goto body;
    fail:
    sub_080C31E0(thread, thread->savedHandler);
    goto end;
    body:
    state->secondPart->active = 1;
    state->secondPart->param2 = 8;
    state->secondPart->param3 = 1;
    {
      struct Effect *part = state->secondPart;
      s32 kindOffset = (((s32) state->kind) * 5) << 2;
      part->tile = *((u16 *) (kindTable + kindOffset));
      state->secondPart->p0 = poseAttrs[4];
      state->secondPart->p1 = poseParams[1];
      state->secondPart->p2 = poseParams[2];
      state->secondPart->p3 = poseParams[3];
      state->secondPart->tile2 = *((u16 *) (kindTable + ((((s32) state->kind) * 5) << 2) + 4));
      state->secondPart->sprite = sprite;
    }
    *((void **) (childSlots + 4)) = spawnParamChild(thread, -1);
    *((void **) (childSlots + 8)) = spawnParamChild(thread, 1);
    *((void **) (childSlots + 12)) = spawnKind1C1Child(thread);
    *((void **) (childSlots + 16)) = spawnKind1C3Child(thread);
    *((void **) (childSlots + 20)) = spawnBudgetedEffect(thread, 0x1C4);
    state->stateByte = 0;
    thread->spawnFlags = state->spawnFlags;
    {
      s16 *gfxTable = gEffectGfxTable;
      s32 kindIndex = ((s32) state->kind) * 20;
      thread->effectTile = (gfxTable + kindIndex)[18];
    }
    state->flags |= 0x10;
    gMainWorkspace[16] = 0;
    gMainWorkspace[17] = 0;
    gMainWorkspace[18] = 0;
    gMainWorkspace[19] = 0;
    registerScriptObject(thread, 0);
    thread->flags |= 0x1000;
    {
      u8 *base = (u8 *) thread;
      s32 *callbackTable;
      u8 *scriptByte;
      *((u8 *) ((base + ((*((s16 *) (base + 0x22))) * 2)) + 0x19)) = 0;
      callbackTable = (s32 *) 0x08671BB0;
      scriptByte = base + 0x18;
      sub_080C31E4(scriptByte, base + 0x22, *callbackTable);
      *((u8 *) ((base + ((*((s16 *) (base + 0x22))) * 2)) + 0x19)) += 1;
      scriptByte = scriptByte + ((*((s16 *) (base + 0x22))) * 2);
      sub_080C31E0(thread, *((void **) ((*((u32 *) (base + 0x14))) + ((*((u8 *) scriptByte)) * 4))));
    }
  }
  end:
  return;
}
