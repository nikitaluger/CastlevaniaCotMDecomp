s32 stepDelayTimer(void *, void *);
s32 startEffectTimer(void *, s32, void *);
s32 sub_0806D588(void *, void *);
s32 sub_0806D654(void *);
void sub_080C31E4(void *, void *, s32);
extern void *D_08506428;
extern s32 gScriptStepCallbackTable;

/* Falling-object update: applies gravity to the fall speed (capped), moves the
 * object down, and when it hits the ground resets the motion and script state
 * and advances the script; then ticks the current script and syncs the sprite. */
void sub_08088130(void *arg0)
{
  u8 *self = arg0;
  void *work = *((void **) (self + 0x6C));
  void *motion = ((u8 *) work) + 4;
  void *sprite = *((void **) (self + 0x38));
  s32 *handlerTable;
  *((s32 *) (((u8 *) motion) + 0x0C)) += 0x4000;
  if ((*((s32 *) (((u8 *) motion) + 0x0C))) > 0x80000)
  {
    *((s32 *) (((u8 *) motion) + 0x0C)) = 0x80000;
  }
  *((s32 *) (((u8 *) motion) + 0x04)) += *((s32 *) (((u8 *) motion) + 0x0C));
  if (sub_0806D654(motion) != 0)
  {
    startEffectTimer(((u8 *) work) + 0x20, 0, &D_08506428);
    *((s32 *) (((u8 *) motion) + 0x08)) = 0;
    *((s32 *) (((u8 *) motion) + 0x0C)) = 0;
    *((u8 *) ((self + ((*((s16 *) (self + 0x22))) * 2)) + 0x19)) = 0;
    handlerTable = &gScriptStepCallbackTable;
    sub_080C31E4(self + 0x18, self + 0x22, *((s32 *) handlerTable));
  }
  stepDelayTimer(((u8 *) work) + 0x20, sprite);
  sub_0806D588(sprite, motion);
}
