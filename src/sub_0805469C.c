void sub_080C31E8(void *a, void *b, s32 c, s32 d); /* _call_via_r3 */

/* Wait-for-turn command: once the X and Y motion components at work+0x48 no
 * longer point in opposite directions, clear them, clear the current step's
 * byte and dispatch script op 0 through gScriptStepCallbacks. */
void sub_0805469C(void *arg0)
{
  u8 *actor = (u8 *) arg0;
  u8 *work = *((u8 **) (actor + 0x3C));
  s16 *motion = (s16 *) (work + 0x48);
  s16 dirY = motion[1];
  int zero;
  s16 dirX;
  if (dirY > 0)
  {
    dirX = motion[0];
    if (dirX >= 0)
    {
      goto act;
    }
  }
  zero = 0;
  if (dirY < 0)
  {
    dirX = motion[0];
    if (dirX <= 0)
    {
      goto act;
    }
  }
  return;
  act:
  {
    u8 zero8 = zero;
    s32 *stream;
    motion[0] = 0;
    motion[1] = 0;
    *((u8 *) ((actor + ((*((s16 *) (actor + 0x22))) * 2)) + 0x19)) = zero8;
    stream = (s32 *) 0x08671BD0;
    dirX = 0x22;
    sub_080C31E8(actor + 0x18, actor + dirX, 0, *stream);
  }

}
