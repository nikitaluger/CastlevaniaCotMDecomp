extern void sub_080148D8(void *, s32);
extern s32 sub_08014964(s32);
extern s32 sub_080057F8(void);
extern s32 sub_080059DC(s32, s32);
extern s32 sub_08005910(s32, s32);
extern void sub_08049180(void *, void *, void *, void *);
extern void sub_08049160(void *, void *, void *, s32);
extern void sub_080146D0(void *);
extern void sub_080C31E4(void *, void *, s32);
extern void sub_080C31E8(void *, void *, s32, s32);

struct HomingGamePos { u8 _0[0x174C]; s32 targetX; s32 targetY; };
struct HomingMotion { u8 _0[8]; s32 x; s32 y; };
struct HomingSteer { u8 _0; u8 contactType; u16 contactCode; s32 speed; s32 angle; s32 phase; };
struct HomingState { u8 _0[0x19]; u8 state; };
struct HomingEntity {
  u8 _0[0x22];
  s16 stateIndex;
  u8 _1[0x14];
  void *sprite;
  struct HomingMotion *motion;
};
extern struct HomingGamePos D_02025FF0;
extern u8 D_080CF924[];
extern s32 D_08671BB0;
extern s32 D_08671BD0;

/* Steers a homing entity toward the target: on the terminal state it checks a
 * timer and a random angle band, then either rebounds or starts a new attack
 * phase before running the common follow-up. */
void sub_0804886C(struct HomingEntity *entity)
{
  void *sprite;
  struct HomingMotion *motion;
  struct HomingSteer *steer;
  s32 collisionData;
  s32 r4;
  s32 t;

  sprite = entity->sprite;
  motion = entity->motion;
  collisionData = (s32)((u8 *)motion + 0x34);
  steer = (struct HomingSteer *)((u8 *)motion + 0x48);
  sub_080148D8(sprite, motion->x);
  sub_08049180(sprite, (void *)collisionData, motion, steer);
  if (((struct HomingState *)((u8 *)entity + entity->stateIndex * 2))->state == 0x1E)
  {
    s32 zero = 0;
    steer->_0 = zero;
    if (sub_08014964(motion->y) < 0)
    {
      ((struct HomingState *)((u8 *)entity + entity->stateIndex * 2))->state = zero;
      {
        s32 *callback = &D_08671BD0;
        sub_080C31E8((u8 *)entity + 0x18, (u8 *)entity + 0x22, 0, *callback);
      }
    }
    else
    {
      r4 = sub_080057F8() & 0xF;
      t = (sub_080059DC(D_02025FF0.targetX - motion->x, D_02025FF0.targetY - motion->y) & 0xF00000) >> 0x14;
      if (r4 < D_080CF924[t])
      {
        sub_08049160(sprite, (void *)collisionData, steer, 5);
        ((struct HomingState *)((u8 *)entity + entity->stateIndex * 2))->state = zero;
        {
          s32 *callback = &D_08671BB0;
          sub_080C31E4((u8 *)entity + 0x18, (u8 *)entity + 0x22, *callback);
        }
      }
      else
      {
        t = sub_08005910(D_02025FF0.targetY - motion->y, D_02025FF0.targetX - motion->x);
        steer->angle = (t + 0x8000) & 0xFFFF;
        steer->speed = 0x18000;
        sub_080146D0(motion);
        ((struct HomingState *)((u8 *)entity + entity->stateIndex * 2))->state = zero;
        {
          s32 *callback = &D_08671BD0;
          sub_080C31E8((u8 *)entity + 0x18, (u8 *)entity + 0x22, 6, *callback);
        }
      }
    }
  }
}
