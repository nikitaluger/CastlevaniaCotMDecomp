s32 setAttachedObjectMode(s32, s32, void *);
s32 setObjectModeWord(s32, s32);
s32 sub_080BE5A4();
s32 sub_080BE5FC(void *);
volatile short setEffectPartState(s32, s32);
s32 sub_080C31E0(s32, s32);
s32 sub_080C31E4(void *, void *, s32);

/* Updates an entity's motion each frame: recomputes its screen position from
 * a scale factor, advances and clamps velocity/height, wraps the height at its
 * bounds, and spawns effects and advances the script on a timer. */
void sub_080BA35C(void *arg0)
{
  s32 timer;
  s32 *scriptData;
  s32 delta;
  s32 newHeight;
  s32 newDelta;
  s32 state1C;
  s32 wrappedVel;
  s8 *motionBytes;
  void *motion;
  void *actor;
  unsigned int sum;
  s32 *paramTable;

  actor = *((void **) ((u8 *)arg0 + 0x3C));
  motion = actor + 0x48;
  sub_080BE5A4();
  sub_080BE5FC(arg0);
  paramTable = (s32 *)0x08671BFC;
  *(s32 *)((u8 *)actor + 8) = (s32)((((s32)*(s32 *)((u8 *)motion + 0x7C)) >> 8) * ((sub_080C31E0(*(s32 *)((u8 *)motion + 0x70) + 0x4000, *paramTable) >> 8)) + 0x01000000);
  *(s32 *)((u8 *)actor + 0xC) = (s32)((((s32)*(s32 *)((u8 *)motion + 0x7C)) >> 8) * ((sub_080C31E0(*(s32 *)((u8 *)motion + 0x70), *paramTable) >> 8)) + 0x01500000);
  *(s32 *)((u8 *)motion + 0x70) = (s32)(*(s32 *)((u8 *)motion + 0x70) + *(s32 *)((u8 *)motion + 0x74));
  delta = *(s32 *)((u8 *)motion + 0x74);
  if (*(s32 *)((u8 *)motion + 0x6C) != 0) {
    newDelta = delta - *(s32 *)((u8 *)motion + 0x78);
  } else {
    newDelta = delta + *(s32 *)((u8 *)motion + 0x78);
  }
  *(s32 *)((u8 *)motion + 0x74) = newDelta;
  motionBytes = (s8 *)motion;
  if (*(vs32 *)(motionBytes + 0x74) > 0x80) {
    *(s32 *)((u8 *)motion + 0x74) = 0x80;
  }
  if (*(vs32 *)(motionBytes + 0x74) < (-0x80)) {
    *(s32 *)((u8 *)motion + 0x74) = -0x80;
  }
  sum = *(s32 *)((u8 *)motion + 0x7C) + *(s32 *)((u8 *)motion + 0x80);
  newHeight = sum;
  *(s32 *)((u8 *)motion + 0x7C) = newHeight;
  if ((((s32) *(s32 *)(motionBytes + 0x80)) > 0) && (newHeight > 0x680000)) {
    wrappedVel = -0x8000;
    goto block_13;
  }
  if ((((s32) *(s32 *)((u8 *)motion + 0x80)) < 0) && (((s32) *(s32 *)((u8 *)motion + 0x7C)) <= 0x2FFFFF)) {
    wrappedVel = 0x8000;
block_13:
    *(s32 *)((u8 *)motion + 0x80) = wrappedVel;
  }
  timer = *(s32 *)((u8 *)arg0 + 4) + 1;
  *(s32 *)((u8 *)arg0 + 4) = timer;
  if (timer == 0x2B0) {
    *(s32 *)((u8 *)motion + 0x6C) = 1;
  }
  if (*(s32 *)((u8 *)arg0 + 4) == 0x2D0) {
    setAttachedObjectMode(*(s32 *)((u8 *)motion + 0x20), 0, actor);
    state1C = *(s32 *)((u8 *)motion + 0x1C);
    setObjectModeWord(state1C, 1);
    setEffectPartState(*(s32 *)((u8 *)motion + 0x34), 2);
    *(s8 *)((u8 *)(*(s16 *)((u8 *)arg0 + 0x22) * 2 + arg0) + 0x19) = 0;
    scriptData = (s32 *)0x08671BB0;
    sub_080C31E4(arg0 + 0x18, arg0 + 0x22, *scriptData);
  }
}
