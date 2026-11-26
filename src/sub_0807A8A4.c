struct GameState_7A8A4
{
  u8 _0[0x10];
  u32 flags;
  u8 _14[0x14ED - 0x14];
  u8 modeFlag;
  u8 _14EE[0x173A - 0x14EE];
  u8 mode;
  u8 _173B[0x18C2 - 0x173B];
  u16 spriteAttr;
};
extern struct GameState_7A8A4 gMainWorkspace;
extern s32 sub_0806D450(void *, void *, void *);
extern void sub_08003740(void *, void *);
extern void sub_0806D588(void *, void *);
extern void sub_080C31E0(void *, void *);
extern void sub_080C31E4(void *, void *, s32);

/* Updates a projectile that periodically resets its velocity: handles special
 * movement, ticks its timer and restarts the direction when it expires, projects
 * to screen while holding Y fixed, and aborts on global mode/flag changes. */
void sub_0807A8A4(void *arg0)
{
  u8 *actor = *((u8 **) (((u8 *) arg0) + 0x6C));
  u8 *mover = actor + 4;
  u8 *world = *((u8 **) (((u8 *) arg0) + 0x38));
  struct GameState_7A8A4 *d;
  int zero;
  if (sub_0806D450(arg0, world, mover) > 0)
  {
    sub_080C31E0(arg0, *((void **) (((u8 *) arg0) + 0x24)));
    return;
  }
  d = &gMainWorkspace;
  *((u16 *) world) = d->spriteAttr;
  zero = 0;
  {
    u32 timer = (*((u32 *) (mover + 0x10))) - 1;
    *((u32 *) (mover + 0x10)) = timer;
    if (timer == zero)
    {
      u8 byteZero;
      s32 *eventTable;
      *((u32 *) (mover + 8)) = 0;
      timer = 0x40000;
      *((u32 *) (mover + 0xC)) = timer;
      *((u32 *) (mover + 0x10)) = 0x20;
      byteZero = zero;
      *((u8 *) ((((u8 *) arg0) + ((*((s16 *) (((u8 *) arg0) + 0x22))) * 2)) + 0x19)) = byteZero;
      eventTable = (s32 *) 0x08671BB0;
      sub_080C31E4(((u8 *) arg0) + 0x18, ((u8 *) arg0) + 0x22, *eventTable);
    }
  }
  sub_08003740(actor + 0x20, world);
  {
    u32 savedY = *((u32 *) (world + 0x18));
    sub_0806D588(world, mover);
    *((u32 *) (world + 0x18)) = savedY;
  }
  if ((d->mode == 0x1C) || ((d->modeFlag == zero) && (d->flags != 0)))
  {
    sub_080C31E0(arg0, *((void **) (((u8 *) arg0) + 0x24)));
  }
}
