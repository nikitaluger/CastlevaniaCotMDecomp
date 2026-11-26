extern s32 sub_08011408(s32, s32, s32, s32, s32);
extern s32 signOf(s32);
extern s32 sub_0802EDF4(s32, s32);
extern s32 sub_080C31E4(void *, void *, s32);

/* Plays the entity's frame-0 animation, flips its sprite horizontally when it
 * lies left of the camera target, spawns an effect at its position, then clears
 * the current script step's action byte and advances the script. */
void sub_0802E628(void *entity)
{
  u8 *self = (u8 *)entity;
  void *sprite = *(void **)(self + 0x38);
  void *work = *(void **)(self + 0x3C);
  u8 *anim;
  s32 one;
  anim = (u8 *)work + 0x34;
  *(s32 *)((u8 *)work + 0x48) = 0;
  one = 1;
  sub_08011408((s32)sprite, (s32)anim, 0, 0, one);
  if (signOf(*(s32 *)((u8 *)work + 8)) > 0) {
    u16 attr1 = *(vu16 *)((u8 *)sprite + 2);
    *(u16 *)((u8 *)sprite + 2) = 0x10 | attr1;
  } else {
    *(u16 *)((u8 *)sprite + 2) &= 0xFFEF;
  }
  sub_0802EDF4(*(s32 *)((u8 *)work + 8), *(s32 *)((u8 *)work + 0xC));
  *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = 0;
  {
    const s32 *lit = (const s32 *)0x08671BB0;
    sub_080C31E4(self + 0x18, self + 0x22, *lit);
  }
}
