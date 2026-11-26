extern void setAnimationFrame(s32, void *, s32, s32); /* set animation frame */
extern void D_08012F88(void *, s32); /* thumb routine at 0x08012F88 */
extern s32 sub_080133A4(s32, s32); /* probe ground collision below a point */

/* Jump command: switch to the jump animation and, while the actor's state
 * flags and jump timer are active, apply a 3px vertical step and count the
 * timer down. When the jump ends, set the "landed" flag once the ground probe
 * under the actor reports solid ground. */
void sub_08029FB8(void *arg0)
{
  u8 *actor = (u8 *) arg0;
  int sprite = *((s32 *) (actor + 0x38));
  u8 *work = *((u8 **) (actor + 0x3C));
  u8 *anim = work + 0x34;
  int one;
  u8 *jump = work + 0x48;
  u16 unused;
  s16 timer;
  setAnimationFrame(sprite, anim, 0x0B, 1);
  one = 1;
  if (((*((u16 *) (work + 2))) & 0x0D) != 0)
  {
    timer = *((s16 *) (jump + 2));
    if (timer > 0)
    {
      D_08012F88(work, 0x30000);
      *((u16 *) (jump + 2)) = (u16) ((*((s16 *) (jump + 2))) - 1);
    }
    else
    {
      goto grounded;
    }
  }
  {
    s32 r = sub_080133A4(*((s32 *) (work + 8)), *((s32 *) (work + 0xC)));
    if (r != one)
    {
      return;
    }
  }
  grounded:
  *((u16 *) (work + 0)) |= one;

}
