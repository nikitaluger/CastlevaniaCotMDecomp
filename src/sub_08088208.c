extern void sub_08003740(void *, void *);
extern void sub_08003A6C(void *, s32, void *);
extern void sub_0806D588(void *, void *);
extern void sub_080C31E4(void *, void *, s32);

/* Low part of the main game state; mode at 0x14. */
struct S_02025FF0_14
{
  u8 _0[0x14];
  u32 mode;
};
extern struct S_02025FF0_14 gMainWorkspace;

/* Sprite update: in game mode 0x24, restart the actor's animation from the
 * data at 0x085063F8, clear the sprite's 0x10 flag, reset the script step and
 * run the script handler; then advance the animation timer and copy the
 * actor's position into the sprite. */
void sub_08088208(void *arg0)
{
  u8 *self = (u8 *)arg0;
  u8 *actor = *((u8 **)(self + 0x6C));
  u8 *actorPos = actor + 4;
  u8 *sprite = *((u8 **)(self + 0x38));
  s32 spriteFlags;
  u16 zero;
  s32 *scriptHandlers;
  if (gMainWorkspace.mode == 0x24)
  {
    sub_08003A6C(actor + 0x20, 0, (void *)0x085063F8);
    *(u32 *)(actorPos + 8) = 0x20000;
    spriteFlags = 0xFFEF & *(u16 *)(sprite + 2);
    zero = 0;
    *(u16 *)(sprite + 2) = spriteFlags;
    *(u32 *)(actorPos + 0x14) = 1;
    *(u8 *)(self + (*(s16 *)(self + 0x22)) * 2 + 0x19) = zero;
    scriptHandlers = (s32 *)0x08671BB0;
    sub_080C31E4(self + 0x18, self + 0x22, *scriptHandlers);
  }
  sub_08003740(actor + 0x20, sprite);
  sub_0806D588(sprite, actorPos);
}
