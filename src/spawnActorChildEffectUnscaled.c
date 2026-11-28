extern void startEffectTimer(void *, s32, void *);
extern void playSound(s32);
extern void *allocEffectPart(void);
extern void cleanupFailedEffectSpawn(void *);
extern void _call_via_r1(void *, void *);
extern void _call_via_r2(void *, void *, void *);
extern void releaseActorEffectParts(void);
struct EffectWorkspace { u8 _0[0x14EF]; u8 b14EF; u8 _1[0x1510 - 0x14F0]; u8 b1510; };
extern struct EffectWorkspace gMainWorkspace;
extern u8 gGameStatus[];
extern u8 D_084CEC88[];
extern u8 D_084CECC8[];
extern s32 gMainObjTimerCallbacks;
struct SubObject {
  u8 _0;
  u8 active;
  u8 type;
  u8 subtype;
  u16 dataWord;
  u16 field6;
  u16 field8;
  u16 fieldA;
  u16 fieldC;
  u16 scaledValue;
  void *sprite;
  u8 _14[2];
  u16 lifetime;
  u8 _18[0x24 - 0x18];
  void *animSequence;
};
struct EffectGraphic { u8 _0[4]; void *gfxData; u8 _1[0x20 - 8]; u8 f20; u8 _2[0x55 - 0x21]; u8 modeFlag; };
struct BehaviorState {
  u8 _0[4];
  void *oldHandler;
  u8 _1[0x18 - 8];
  void *cleanupCallback;
  u8 _2[0x2C - 0x1C];
  struct SubObject *subObject;
  void *handle0;
  void *handle1;
  void *handle2;
  void *handle3;
};
struct EffectOwner {
  u8 _0[0x14];
  void *scriptTable;
  u8 _1[0xA];
  s16 stepIndex;
  void *cleanupCallback;
  u8 _2[0x10];
  void *sprite;
  u8 _3[0x30];
  void *params;
  u8 _4[0x0C];
  void *graphicData;
  u8 _5[0xC];
  void *stateData;
};
struct ScriptStep { u8 _0[0x19]; u8 counter; };

/* Allocate a child effect part for this entity's current action, attach it to
 * the owner's behavior state, load its graphics and animation settings, start
 * the spawn timer, play the cue and dispatch the next script step. */
void spawnActorChildEffectUnscaled(struct EffectOwner *self)
{
  void *effectObj;
  struct BehaviorState *state;
  void *sprite;
  u8 *dataTable;
  struct SubObject *child;
  s32 zero;
  u32 off;
  effectObj = self->params;
  state = (struct BehaviorState *)((u8 *)effectObj + 4);
  sprite = self->sprite;
  dataTable = gGameStatus;
  child = allocEffectPart();
  state->subObject = child;
  if (child == NULL) {
    cleanupFailedEffectSpawn(self);
    return;
  }
  zero = 0;
  state->handle0 = (void *)zero;
  state->handle1 = (void *)zero;
  state->handle2 = (void *)zero;
  state->handle3 = (void *)zero;
  child->active = gMainWorkspace.b1510 & 1;
  state->subObject->type = 2;
  state->subObject->subtype = 8;
  state->subObject->dataWord = dataTable[0xC1 * 4];
  state->subObject->field6 = zero;
  state->subObject->field8 = zero;
  state->subObject->fieldA = zero;
  state->subObject->fieldC = zero;
  state->subObject->scaledValue = zero;
  state->subObject->lifetime = 5;
  state->subObject->sprite = sprite;
  state->cleanupCallback = self->cleanupCallback;
  self->cleanupCallback = (void *)releaseActorEffectParts;
  ((struct EffectGraphic *)effectObj)->modeFlag = gMainWorkspace.b14EF;
  ((struct SubObject *)sprite)->animSequence = (void *)D_084CEC88;
  startEffectTimer((u8 *)effectObj + 0x20, 0, (void *)D_084CECC8);
  ((struct EffectGraphic *)effectObj)->gfxData = self->graphicData;
  state->oldHandler = self->stateData;
  playSound(0x6D);
  ((struct ScriptStep *)((u8 *)self + self->stepIndex * 2))->counter = zero;
  {
    s32 *cueTable = &gMainObjTimerCallbacks;
    u8 *scriptPtr = (u8 *)self + 0x18;
    _call_via_r2(scriptPtr, (u8 *)self + 0x22, (void *)*cueTable);
    ((struct ScriptStep *)((u8 *)self + self->stepIndex * 2))->counter++;
    off = self->stepIndex * 2;
    _call_via_r1(self, *(void **)((u8 *)self->scriptTable + *(u8 *)((u32)scriptPtr + off) * 4));
  }
}
