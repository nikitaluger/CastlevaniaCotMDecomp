void setAnimationFrame(s32, s32, s32, s32);
void sub_080C31E4(void *, void *, s32);
static inline u8 zeroU8(void) { u8 v = 0; return v; }
static inline u16 zeroU16(void) { u16 v = 0; return v; }

/* Start animation 5 and give the work block a vertical velocity of -0x6000;
 * when the animator reports completion (bit 2), zero the pose counters at
 * +0x16/+0x18 and advance the script step. */
void sub_0801B5F8(void *arg0) {
  u8 *obj = arg0;
  void **stepFnTable;
  u32 sprite = *((u32 *) (obj + 0x38));
  u8 *work = *((u8 **) (obj + 0x3C));
  u8 *anim = work + 0x34;
  u8 *pose = work + 0x48;
  setAnimationFrame(sprite, work + 0x34, 5, 0);
  *((u32 *) (work + 0x14)) = 0xFFFFA000;
  if ((*((u8 *) anim)) & 2) {
    register u16 z0 = zeroU16();
    register u8 z1 = zeroU8();
    *((u16 *) (pose + 0x16)) = z0;
    *((u16 *) (pose + 0x18)) = z0;
    ((u8 *) (obj + ((*((s16 *) (obj + 0x22))) * 2)))[0x19] = z1;
    stepFnTable = (void **) 0x08671BB0;
    sub_080C31E4(obj + 0x18, obj + 0x22, *stepFnTable);
  }
}
