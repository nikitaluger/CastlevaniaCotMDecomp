s32 sub_08003740(void *, void *);
s32 sub_0806D2F8(void *, void *);
s32 sub_0806D518(void *, void *, void *);
s32 sub_0806D588(void *, void *);
void sub_080C31E0(void *, s32);
s32 sub_08007DD8(s32, s32, s32);
s32 sub_0808DBF8(s32, s32, s32);

/* Object at +0x6C of the entity: an accumulator at +4 and a timer block at +0x20. */
struct MotionBase {
  u8 _0[4];
  s32 coord;
  u8 _1[0x20 - 8];
  u8 timer[4];
};
/* The collision record starts at MotionBase+4; fields named from that base. */
struct HitFlags { u8 _0[0x14]; u16 flags; };
struct Motion {
  s32 coord;
  s32 subCoord;
  s32 delta;
  u8 _0[0x2C - 0x0C];
  struct HitFlags *hit;
};
/* Object tracked at entity+0x38. */
struct Target { u16 id; u8 _0[0x14 - 2]; s32 x; s32 y; };
struct Entity { u8 _0[0x24]; s32 handler; u8 _1[0x38 - 0x28]; struct Target *target; u8 _2[0x6C - 0x3C]; struct MotionBase *motion; };

/* Global game state: mode, level id, room index and the room spawn value. */
struct GameState {
  u8 _0[0x10];
  s32 gameMode;
  u8 _1[0x14ED - 0x14];
  u8 flag14ED;
  u8 _2[0x173A - 0x14EE];
  u8 levelId;
  u8 _3[0x18A8 - 0x173B];
  u8 roomIndex;
  u8 _4[0x18C2 - 0x18A9];
  u16 spawnValue;
};
extern struct GameState gMainWorkspace;
extern u8 gTilemapPages[];

/* Advance the projectile's coordinate, test it against the current room's tile
 * data and the global game-state flags, spawn a hit effect on impact and retire
 * the object; otherwise refresh the tracked target and run the bounds check. */
void sub_0807DC4C(struct Entity *entity)
{
  struct MotionBase *motion = entity->motion;
  struct Motion *m = (struct Motion *)((u8 *) motion + 4);
  struct Target *target = entity->target;
  if (sub_0806D518(entity, target, m) == 0) {
    s32 newCoord = motion->coord + m->delta;
    motion->coord = newCoord;
    if ((m->hit->flags & 1) != 0) {
      sub_0808DBF8(newCoord, m->subCoord, 0);
      sub_080C31E0(entity, entity->handler);
      return;
    }
    {
      u8 *room = gTilemapPages + (gMainWorkspace.roomIndex << 6);
      if ((sub_08007DD8((s32) room, newCoord, m->subCoord) << 16) != 0) {
        sub_0808DBF8(motion->coord, m->subCoord, 0);
        sub_080C31E0(entity, entity->handler);
        return;
      }
    }
    target->id = gMainWorkspace.spawnValue;
    if (((sub_08003740(motion->timer, target), sub_0806D588(target, m), gMainWorkspace.levelId == 0x1C)) || ((gMainWorkspace.flag14ED == 0) && (gMainWorkspace.gameMode != 0))) {
      sub_080C31E0(entity, entity->handler);
      return;
    }
    sub_0806D2F8(entity, target);
  }
}
