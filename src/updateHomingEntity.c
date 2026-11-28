extern s32 getAngleFromDelta(s32, s32);
extern void advanceMotion(void *, s32);
extern void setSpriteFlip(void *, s32);
extern void setPolarOffset(void *, s32, s32);
extern s32 getAngleTurnDirection(s32, s32);
extern void applyHomingContactRecoil(void *, void *, void *, void *);
extern s32 _call_via_r1(s32, s32);
extern void _call_via_r2(void *, void *, s32);

/* Fixed-point target position held in the global game-state block. */
struct HomingGamePos { u8 _0[0x174C]; s32 targetX; s32 targetY; };
/* Motion block at entity+0x3C: position and velocity. */
struct HomingMotion { u8 _0[8]; s32 x; s32 y; };
/* Steering sub-block at motion+0x48. */
struct HomingSteer { u8 _0[4]; s32 speed; s32 angle; s32 phase; };
/* Per-entity state byte at entity + index*2 + 0x19. */
struct HomingState { u8 _0[0x19]; u8 state; };
struct HomingEntity {
  u8 _0[0x22];
  s16 stateIndex;
  u8 _1[0x14];
  void *sprite;
  struct HomingMotion *motion;
};
extern struct HomingGamePos gMainWorkspace;
extern s32 gTrigFuncTable;
extern s32 gMainObjTimerCallbacks;

/* Steers a homing entity toward a wobbling target point (the workspace target
 * plus a trig-driven circular offset), nudging its angle one step per frame
 * and ramping speed up or down by its state byte. After updating motion,
 * facing and contact recoil, a state byte of 0x5A stops the entity, clears the
 * byte and fires the main-object timer callback. */
void updateHomingEntity(struct HomingEntity *entity)
{
  void *sprite;
  struct HomingMotion *motion;
  struct HomingSteer *steer;
  s32 animState;
  s32 deltaX;
  s32 deltaY;
  s32 *trigFn;
  s32 desiredAngle;
  s32 turn;
  sprite = entity->sprite;
  motion = entity->motion;
  animState = (s32)((u8 *)motion + 0x34);
  steer = (struct HomingSteer *)((u8 *)motion + 0x48);
  trigFn = &gTrigFuncTable;
  deltaX = gMainWorkspace.targetX + ((_call_via_r1(steer->phase + 0x4000, *trigFn) >> 8) << 14);
  deltaY = (gMainWorkspace.targetY + ((_call_via_r1(steer->phase, *trigFn) >> 8) << 14)) - motion->y;
  deltaX -= motion->x;
  desiredAngle = getAngleFromDelta(deltaY, deltaX);
  turn = getAngleTurnDirection(steer->angle, desiredAngle);
  steer->angle = steer->angle + (turn << 8);
  if (((struct HomingState *)((u8 *)entity + entity->stateIndex * 2))->state <= 0x31) {
    steer->speed += 0xC00;
  } else {
    steer->speed += (s32)0xFFFFF400;
  }
  setPolarOffset(motion, steer->angle, steer->speed);
  advanceMotion(motion, 0);
  setSpriteFlip(sprite, steer->angle);
  applyHomingContactRecoil(sprite, (void *)animState, motion, steer);
  if (((struct HomingState *)((u8 *)entity + entity->stateIndex * 2))->state == 0x5A) {
    s32 zero = 0;
    steer->speed = zero;
    setPolarOffset(motion, steer->angle, 0);
    ((struct HomingState *)((u8 *)entity + entity->stateIndex * 2))->state = zero;
    {
      s32 *callback = &gMainObjTimerCallbacks;
      _call_via_r2((u8 *)entity + 0x18, (u8 *)entity + 0x22, *callback);
    }
  }
}
