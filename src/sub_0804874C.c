extern s32 sub_08005910(s32, s32);
extern void sub_0801165C(void *, s32);
extern void setSpriteFlip(void *, s32);
extern void sub_080146D0(void *, s32, s32);
extern s32 sub_0801473C(s32, s32);
extern void sub_08049180(void *, void *, void *, void *);
extern s32 sub_080C31E0(s32, s32);
extern void sub_080C31E4(void *, void *, s32);

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
extern s32 D_08671BFC;
extern s32 gMainObjTimerCallback;

/* Steers a homing entity toward the target, advances its motion and facing,
 * then stops it and fires a callback once its state byte reaches 0x5A. */
void sub_0804874C(struct HomingEntity *entity)
{
  void *sprite;
  struct HomingMotion *motion;
  struct HomingSteer *steer;
  s32 collisionData;
  s32 deltaX;
  s32 deltaY;
  s32 *trigFn;
  s32 desiredAngle;
  s32 turn;
  sprite = entity->sprite;
  motion = entity->motion;
  collisionData = (s32)((u8 *)motion + 0x34);
  steer = (struct HomingSteer *)((u8 *)motion + 0x48);
  trigFn = &D_08671BFC;
  deltaX = gMainWorkspace.targetX + ((sub_080C31E0(steer->phase + 0x4000, *trigFn) >> 8) << 14);
  deltaY = (gMainWorkspace.targetY + ((sub_080C31E0(steer->phase, *trigFn) >> 8) << 14)) - motion->y;
  deltaX -= motion->x;
  desiredAngle = sub_08005910(deltaY, deltaX);
  turn = sub_0801473C(steer->angle, desiredAngle);
  steer->angle = steer->angle + (turn << 8);
  if (((struct HomingState *)((u8 *)entity + entity->stateIndex * 2))->state <= 0x31) {
    steer->speed += 0xC00;
  } else {
    steer->speed += (s32)0xFFFFF400;
  }
  sub_080146D0(motion, steer->angle, steer->speed);
  sub_0801165C(motion, 0);
  setSpriteFlip(sprite, steer->angle);
  sub_08049180(sprite, (void *)collisionData, motion, steer);
  if (((struct HomingState *)((u8 *)entity + entity->stateIndex * 2))->state == 0x5A) {
    s32 zero = 0;
    steer->speed = zero;
    sub_080146D0(motion, steer->angle, 0);
    ((struct HomingState *)((u8 *)entity + entity->stateIndex * 2))->state = zero;
    {
      s32 *callback = &gMainObjTimerCallback;
      sub_080C31E4((u8 *)entity + 0x18, (u8 *)entity + 0x22, *callback);
    }
  }
}
