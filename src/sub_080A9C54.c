s32 sub_08011528(s32, s32);
s32 sub_080C31E0(void *, s32);

/* Advance the entity's sprite descriptor (state block at entity+0x3C, +0x34)
 * and, if the descriptor reports completion (bit 1), run the entity's pending
 * update callback. */
void sub_080A9C54(void *entity)
{
  void *state;
  s32 spriteId;
  spriteId = *((s32 *) (((s8 *) entity) + 0x38));
  state = *((void **) (((s8 *) entity) + 0x3C));
  sub_08011528(spriteId, state + 0x34);
  if (2 & (*((u8 *) (((s8 *) state) + 0x34))))
  {
    sub_080C31E0(entity, *((s32 *) (((s8 *) entity) + 0x24)));
  }
}
