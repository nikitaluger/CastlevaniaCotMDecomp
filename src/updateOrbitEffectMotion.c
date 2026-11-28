s32 setAttachedObjectMode(s32, s32, void *);
s32 setObjectModeWord(s32, s32);
s32 sub_080BE5A4();
s32 sub_080BE5FC(void *);
volatile short setEffectPartState(s32, s32);
s32 sub_080C31E0(s32, s32);
s32 sub_080C31E4(void *, void *, s32);

extern s32 gTrigFuncTable[];
extern s32 gMainObjTimerCallbacks[];

/* Update a trig-driven orbiting effect: reposition the sprite from its angle
 * and scale, integrate and clamp its angular and vertical velocity, wrap its
 * height at the bounds, and on a timer tear the effect down and dispatch the
 * next script step. */
void updateOrbitEffectMotion(void *entity)
{
  s32 timer;
  s32 *callbackTable;
  s32 velocity;
  s32 newHeight;
  s32 newVelocity;
  s32 effectKind;
  s32 wrapVelocity;
  s8 *workBytes;
  void *orbitState;
  void *sprite;
  unsigned int heightSum;
  s32 *trigFuncTable;

  sprite = *((void **) ((u8 *)entity + 0x3C));
  orbitState = sprite + 0x48;
  sub_080BE5A4();
  sub_080BE5FC(entity);
  trigFuncTable = gTrigFuncTable;
  *(s32 *)((u8 *)sprite + 8) = (s32)((((s32)*(s32 *)((u8 *)orbitState + 0x7C)) >> 8) * ((sub_080C31E0(*(s32 *)((u8 *)orbitState + 0x70) + 0x4000, *trigFuncTable) >> 8)) + 0x01000000);
  *(s32 *)((u8 *)sprite + 0xC) = (s32)((((s32)*(s32 *)((u8 *)orbitState + 0x7C)) >> 8) * ((sub_080C31E0(*(s32 *)((u8 *)orbitState + 0x70), *trigFuncTable) >> 8)) + 0x01500000);
  *(s32 *)((u8 *)orbitState + 0x70) = (s32)(*(s32 *)((u8 *)orbitState + 0x70) + *(s32 *)((u8 *)orbitState + 0x74));
  velocity = *(s32 *)((u8 *)orbitState + 0x74);
  if (*(s32 *)((u8 *)orbitState + 0x6C) != 0) {
    newVelocity = velocity - *(s32 *)((u8 *)orbitState + 0x78);
  } else {
    newVelocity = velocity + *(s32 *)((u8 *)orbitState + 0x78);
  }
  *(s32 *)((u8 *)orbitState + 0x74) = newVelocity;
  workBytes = (s8 *)orbitState;
  if (*(vs32 *)(workBytes + 0x74) > 0x80) {
    *(s32 *)((u8 *)orbitState + 0x74) = 0x80;
  }
  if (*(vs32 *)(workBytes + 0x74) < (-0x80)) {
    *(s32 *)((u8 *)orbitState + 0x74) = -0x80;
  }
  heightSum = *(s32 *)((u8 *)orbitState + 0x7C) + *(s32 *)((u8 *)orbitState + 0x80);
  newHeight = heightSum;
  *(s32 *)((u8 *)orbitState + 0x7C) = newHeight;
  if ((((s32) *(s32 *)(workBytes + 0x80)) > 0) && (newHeight > 0x680000)) {
    wrapVelocity = -0x8000;
    goto block_13;
  }
  if ((((s32) *(s32 *)((u8 *)orbitState + 0x80)) < 0) && (((s32) *(s32 *)((u8 *)orbitState + 0x7C)) <= 0x2FFFFF)) {
    wrapVelocity = 0x8000;
block_13:
    *(s32 *)((u8 *)orbitState + 0x80) = wrapVelocity;
  }
  timer = *(s32 *)((u8 *)entity + 4) + 1;
  *(s32 *)((u8 *)entity + 4) = timer;
  if (timer == 0x2B0) {
    *(s32 *)((u8 *)orbitState + 0x6C) = 1;
  }
  if (*(s32 *)((u8 *)entity + 4) == 0x2D0) {
    setAttachedObjectMode(*(s32 *)((u8 *)orbitState + 0x20), 0, sprite);
    effectKind = *(s32 *)((u8 *)orbitState + 0x1C);
    setObjectModeWord(effectKind, 1);
    setEffectPartState(*(s32 *)((u8 *)orbitState + 0x34), 2);
    *(s8 *)((u8 *)(*(s16 *)((u8 *)entity + 0x22) * 2 + entity) + 0x19) = 0;
    callbackTable = gMainObjTimerCallbacks;
    sub_080C31E4(entity + 0x18, entity + 0x22, *callbackTable);
  }
}
