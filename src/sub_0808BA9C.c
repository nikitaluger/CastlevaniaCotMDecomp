extern u32 gMainWorkspace[];
extern u8 gCameraState[];

/* Periodic timer in the global state: while its countdown is nonzero it writes a
 * fixed sprite pattern into gCameraState when the count reaches a trigger value, clears
 * that pattern when the count runs out, and reloads the timer from a repeat counter.
 */
void sub_0808BA9C(void) {
  s32 zero;
  u8 *state = (u8 *)gMainWorkspace;
  s32 *timer = (s32 *)(state + 0x1764);
  s32 *trigger;
  s32 *repeat;
  s32 count, remaining;

  count = *timer;
  if (count != 0) {
    count--;
    *timer = count;
    trigger = (s32 *)(state + 0x175C);
    if (count == *trigger) {
      u8 *sprites = gCameraState;
      u8 *field1468 = sprites + 0x1468;
      zero = 0;
      *field1468 = 0x31;
      sprites[0x146A] = 0x1F;
      sprites[0x1460] = zero;
      sprites[0x1464] = zero;
      sprites[0x1462] = 0xF8;
      sprites[0x1466] = 0xA0;
    }
    remaining = *timer;
    if (remaining == 0) {
      u8 *sprites = gCameraState;
      sprites[0x1460] = remaining;
      sprites[0x1464] = remaining;
      sprites[0x1462] = remaining;
      sprites[0x1466] = remaining;
      repeat = (s32 *)(state + 0x1758);
      if (--*repeat != 0) {
        *timer = *trigger + *(s32 *)(state + 0x1760);
      }
    }
  }
}
