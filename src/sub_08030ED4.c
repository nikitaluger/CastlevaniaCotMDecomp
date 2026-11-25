void sub_08011368(s32, void *, s32, s32);
void sub_08030F90(s32, void *, s32);
void sub_080C31E0(void *, s32);

/* Play animation frame 9 for the entity and spawn effects around it at fixed
 * points in the animation; at the end of the animation it spawns the last two
 * effects and switches to the next script state. */
void sub_08030ED4(void *arg0)
{
  u8 *animFlags;
  s32 frameCode;
  s32 sprite;
  void *work;
  void *animator;
  sprite = *(s32 *)((s8 *)arg0 + 0x38);
  work = *(void **)((s8 *)arg0 + 0x3C);
  animFlags = (u8 *)((s8 *)work + 0x34);
  animator = (s8 *)work + 0x34;
  *(s32 *)((s8 *)work + 0x14) = 0;
  *(s32 *)((s8 *)work + 0x10) = 0;
  sub_08011368(sprite, animator, 0x09, 0);
  if (*(s32 *)((s8 *)animator + 4) == 1)
  {
    frameCode = *(u8 *)((s8 *)animator + 1) - 1;
    switch (frameCode)
    {
      case 2:
        sub_08030F90(sprite, work, 0);
        break;

      case 3:
        sub_08030F90(sprite, work, 1);
        sub_08030F90(sprite, work, 2);
        break;

    }

  }
  if (2 & (*animFlags))
  {
    sub_08030F90(sprite, work, 3);
    sub_08030F90(sprite, work, 4);
    sub_080C31E0(arg0, *(s32 *)((s8 *)arg0 + 0x24));
  }
}
