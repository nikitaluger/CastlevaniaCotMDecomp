s32 sub_080113A8(void *, void *, void *, void *);

/* Advances the steering state: on certain heading transitions it nudges the
 * work velocity by +/-1.0 fixed point, records the new heading and reports the
 * 6/0x12 transition to the caller. */
s32 sub_08040A1C(void *sprite, void *animState, void *work, void *steer)
{
  u16 *spriteH = (u16 *)sprite;
  u32 *workW = (u32 *)work;
  u16 *steerH = (u16 *)steer;
  s32 transitioned = 0;

  sub_080113A8(sprite, animState, work, steer);

  if (steerH[1] == spriteH[0x14])
    goto end;

  if (spriteH[0x14] == 0 || spriteH[0x14] == 0x0B || spriteH[0x14] == 0 || spriteH[0x14] == 0x0B)
    goto add;

  if (spriteH[0x14] == 6 || spriteH[0x14] == 0x12 || spriteH[0x14] == 6 || spriteH[0x14] == 0x12)
  {
    workW[3] += 0xFFFF0000;
    transitioned = 1;
    goto store;
  }

  if (spriteH[0x14] == 3)
  {
    if (steerH[1] == 0)
      workW[3] += 0xFFFF0000;
    if (steerH[1] != 6)
      goto store;
    goto add;
  }
  else if (spriteH[0x14] == 0x0F)
  {
    if (steerH[1] == 0x0B)
      workW[3] += 0xFFFF0000;
    if (steerH[1] == 0x12)
      goto add;
  }
  goto store;

add:
  workW[3] += 0x10000;
store:
  steerH[1] = spriteH[0x14];
end:
  return transitioned;
}
