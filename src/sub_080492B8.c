extern void sub_08011368(void *, s32, s32, s32);
extern s32 sub_08005910(s32, s32);
extern void sub_08014668(void *, s32);
extern s16 D_080CF904[];

/* Point a rotatable object along its velocity: take the atan2 angle of
 * (vx, vy), mirror the sprite according to the velocity's signs, then play the
 * animation frame for that direction from the 16-entry direction table. */
void sub_080492B8(void *arg0, void *arg1, s32 arg2)
{
  u8 *self = (u8 *) arg0;
  u8 *motion = (u8 *) arg1;
  s32 angle;
  s32 vy;
  int flags;
  s32 dir;
  angle = sub_08005910(*((s32 *) (motion + 0x14)), *((s32 *) (motion + 0x10)));
  dir = angle + 0x800;
  sub_08014668(arg0, *((s32 *) (motion + 0x10)));
  vy = *((s32 *) (motion + 0x14));
  if (vy != 0)
  {
    if (vy < 0)
    {
      flags = 0x20 | (*((u16 *) (self + 2)));
      *((u16 *) (self + 2)) = flags;
    }
    else
    {
      *((u16 *) (self + 2)) = (*((u16 *) (self + 2))) & 0xFFDF;
    }
  }
  sub_08011368(arg0, arg2, D_080CF904[((u32) (dir & 0xF000)) >> 12], 0);
}
