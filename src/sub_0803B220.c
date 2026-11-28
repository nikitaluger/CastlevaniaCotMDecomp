s32 sub_08005E80(s32);
s32 spawnJitteredParticles(s32, s32, s32, s32, s32, s32);
s32 spawnVariant2Effect(s32, s32, s32);
s32 sub_080C31E0(void *, s32);

/* Effect entity tick: mirror a per-frame flag of `self` into the attribute
 * word `attr`, play sound 0x84 on the first frame, spray two small particles
 * near `state` every fourth frame, and on frame 30 emit a final particle and
 * dispatch `self`'s completion callback (function pointer at +0x24). */
void sub_0803B220(void *self, void *state, u16 *attr, u8 *frame)
{
  u8 frameAfterInc;
  if (2 & (*((u8 *) (((s8 *) (((*((s16 *) (((s8 *) self) + 0x22))) * 2) + self)) + 0x19))))
  {
    *attr = (0xFFF & (*attr)) | 0xE000;
  }
  frameAfterInc = (*frame = (*frame) + 1);
  if (frameAfterInc == 1)
  {
    sub_08005E80(0x84);
  }
  if (!(3 & (*frame)))
  {
    spawnJitteredParticles(0, 2, *((s32 *) (((s8 *) state) + 8)), (*((s32 *) (((s8 *) state) + 0xC))) + 0xFFF00000, 0xC0000, 0x100000);
  }
  if ((*frame) == 0x1E)
  {
    spawnVariant2Effect(*((s32 *) (((s8 *) state) + 8)), *((s32 *) (((s8 *) state) + 0xC)), 8);
    sub_080C31E0(self, *((s32 *) (((s8 *) self) + 0x24)));
  }
}
