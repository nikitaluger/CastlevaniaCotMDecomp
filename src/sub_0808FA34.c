extern void sub_08005E80(s32);
extern void setObjectAnimationFrame(void *, void *, s32, s32);
extern void sub_080C31E4(void *, void *, u32);
struct FrameValue { s16 frame; u16 pad; };
extern struct FrameValue D_081003AC[];

/* Script step: when the work phase is 1, select an animation frame from the
 * frame table, release the graphic, clear the step byte and advance the script. */
void sub_0808FA34(void *entity)
{
  u8 *self = (u8 *) entity;
  void *animEntity = *((void **) (self + 0x38));
  u8 *work = *((u8 **) (self + 0x3C));
  u8 *anim = work + 0x18;
  u8 zero;
  u32 *scriptTable;
  s32 phase = *((s16 *) (work + 0x14));
  if (phase == 1)
  {
    s32 frame = D_081003AC[*((u32 *) work)].frame;
    setObjectAnimationFrame(animEntity, anim, frame, 0);
    zero = 0;
    *((s16 *) (work + 0x16)) = phase;
    sub_08005E80(0x72);
    *((u8 *) ((self + ((*((s16 *) (self + 0x22))) * 2)) + 0x19)) = zero;
    scriptTable = (u32 *) 0x08671BB0;
    sub_080C31E4(self + 0x18, self + 0x22, *scriptTable);
  }
}
