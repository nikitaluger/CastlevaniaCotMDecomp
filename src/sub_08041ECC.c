extern void sub_08011898(void *, s32);
extern void sub_080C31E8(void *, void *, s32, s32);

/* Step the object's motion by 0x16C1 units, OR the resulting status bits into
 * the animation state, and when the "hit" bit is set, clear the current script
 * byte and continue the script (code 0). */
void sub_08041ECC(void *arg0)
{
  u8 *obj = (u8 *)arg0;
  u8 *state = *((u8 **)(obj + 0x3C));
  u8 *animState = state + 0x48;
  s32 *advanceFunc;
  sub_08011898(state, 0x16C1);
  *((u16 *)(animState + 2)) = (u16)(*((u16 *)(animState + 2)) | *((u16 *)(state + 2)));
  if (4 & *((u16 *)(state + 2)))
  {
    *((s8 *)((u8 *)(((*((s16 *)(obj + 0x22))) * 2) + arg0)) + 0x19) = 0;
    advanceFunc = (s32 *)0x08671BD0;
    sub_080C31E8(obj + 0x18, obj + 0x22, 0, *advanceFunc);
  }
}
