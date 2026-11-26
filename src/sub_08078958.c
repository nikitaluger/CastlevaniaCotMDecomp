struct GameState {
    u8 _0[0x10];
    s32 field10;
    u8 _1[0x14ED - 0x14];
    u8 field14ED;
    u8 _2[0x173A - 0x14EE];
    u8 field173A;
    u8 _3[0x18C2 - 0x173B];
    u16 field18C2;
};
extern struct GameState gMainWorkspace;

extern s32 sub_08003740(void *, void *);
extern s32 sub_0806D2F8(void *, void *);
extern s32 sub_0806D518(void *, void *, void *);
extern s32 sub_0806D588(void *, void *);
extern void sub_080C31E0(void *, s32);

/* Advance one frame of a scripted actor: skip while an area movement override
 * is active; otherwise apply a speed-scaled velocity, tick the lifetime,
 * refresh the graphic, then abort the actor or run its off-screen check. */
void sub_08078958(void *arg0)
{
  void *actor = *((void **) (((char *) arg0) + 0x6C));
  void *mover = ((char *) actor) + 4;
  void *world = *((void **) (((char *) arg0) + 0x38));
  if (sub_0806D518(arg0, world, mover) == 0)
  {
    s32 speed;
    s32 delta = (*((s32 *) (((char *) mover) + 8))) * ((*((s32 *) (((char *) mover) + 0x40))) >> 8);
    if (delta < 0)
    {
      if (arg0)
      {
        delta += 0xFF;
      }
      else
      {
        delta += 0xFF;
      }
    }
    *((s32 *) (((char *) actor) + 4)) += delta >> 8;
    speed = (*((s32 *) (((char *) mover) + 0x40))) >> 8;
    delta = (*((s32 *) (((char *) mover) + 0x0C))) * speed;
    if (delta < 0)
    {
      delta += 0xFF;
    }
    *((s32 *) (((char *) mover) + 4)) += delta >> 8;
    *((u16 *) world) = gMainWorkspace.field18C2;
    *((s32 *) (((char *) mover) + 0x48)) -= 1;
    if ((((*((s32 *) (((char *) mover) + 0x48))) == 0) || ((sub_08003740(((char *) actor) + 0x20, world), sub_0806D588(world, mover), gMainWorkspace.field173A == 0x1C))) || ((gMainWorkspace.field14ED == 0) && (gMainWorkspace.field10 != 0)))
    {
      sub_080C31E0(arg0, *((s32 *) (((char *) arg0) + 0x24)));
      return;
    }
    sub_0806D2F8(arg0, world);
  }
}
