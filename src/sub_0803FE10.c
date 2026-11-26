extern void sub_08040AB0(void *actor, void *sprite, void *work);
extern s32 sub_08040A1C(void *sprite, void *animState, void *work, void *steer);
extern void setAnimationFrame(void *sprite, void *animState, s16 animIndex, s32 arg);
extern void sub_080C31E4(void *scriptData, void *scriptIndex, s32 callback);
extern s32 gMainObjTimerCallback[];
extern s16 D_080CF474[];

/* Spawns a child effect when the trigger is clear, advances the actor's animation,
 * and on a flagged transition with an advanced script step sets the trigger's
 * animation, nudges the actor down a pixel and fires the script callback. */
void sub_0803FE10(void *arg0)
{
  u8 *self = (u8 *) arg0;
  u8 *sprite = *((u8 **) (self + 0x38));
  u8 *work = *((u8 **) (self + 0x3C));
  void *animState = work + 0x34;
  u8 *steer = work + 0x48;
  u8 *trigger = self + 0x4C;
  if ((*((u8 *) trigger)) == 0)
  {
    sub_08040AB0(self, sprite, work);
  }
  if (sub_08040A1C(sprite, animState, work, steer) != 0)
  {
 do { } while (0);
    if ((*((u8 *) ((self + ((*((s16 *) (self + 0x22))) * 2)) + 0x19))) > 0x78)
    {
      s16 animIndex = D_080CF474[*((u8 *) trigger)];
      setAnimationFrame(sprite, animState, animIndex, 0);
      *((s32 *) (work + 0x0C)) += 0x00010000;
      *((u8 *) ((self + ((*((s16 *) (self + 0x22))) * 2)) + 0x19)) = 0;
      {
        s32 *callbacks = gMainObjTimerCallback;
        sub_080C31E4(self + 0x18, self + 0x22, *callbacks);
      }
    }
  }
}
