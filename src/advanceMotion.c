/* A moving object's position and velocity, 16.16 fixed point: x +8, y +0xC,
 * vx +0x10, vy +0x14. */
struct Motion {
    u8 pad[8];
    s32 x;
    s32 y;
    s32 vx;
    s32 vy;
};

/* Advance the motion by one step: x += vx, y += vy, then vy += gravity. */
void advanceMotion(struct Motion *motion, s32 gravity)
{
  struct Motion *pos = motion;
  s32 vy;
  pos->x = (s32) ((pos->x) + (pos->vx));
  vy = pos->vy;
  pos->y = (s32) ((pos->y) + (pos->vy));
  pos->vy = (s32) ((pos->vy) + gravity);
}
