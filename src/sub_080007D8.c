struct KeyState
{
  u8 pad0[0x146C];
  u16 pressed;
  u16 current;
  u16 triggered;
  u16 repeatKeys;
  volatile u8 repeatCounter;
  u8 pad1[0x149C - 0x1475];
  u16 rawKeys;
};
extern struct KeyState D_02021E90;
extern vu16 D_04000130;

/* Reads the active-low key register and updates the global key state: raw,
 * new and current presses, plus a repeat counter that re-triggers the held
 * buttons after a delay. */
void sub_080007D8(void)
{
  struct KeyState *keys = &D_02021E90;
  u16 hardwareKeys = ~D_04000130;
  u16 current;
  u16 previous;
  u16 newPresses;
  u16 buttonMask;
  u32 zero = 0;
  keys->rawKeys = hardwareKeys;
  current = keys->rawKeys;
  previous = keys->current;
  newPresses = current & (~previous);
  keys->pressed = newPresses;
  keys->current = current;
  keys->triggered = newPresses;
  buttonMask = newPresses & 0x3FF;
  if (buttonMask == 0)
  {
    if (keys->repeatKeys == (current & 0x3FF))
    {
      int v = keys->repeatCounter;
      v++;
      *(u8 *)&keys->repeatCounter = (u8)v;
      if ((u8)v == 0x1E)
      {
        keys->triggered = current & 0x3FF;
        keys->repeatKeys = current & 0x3FF;
        *((u8 *) (&keys->repeatCounter)) = 0x1B;
      }
    }
    else
    {
      *((u8 *) (&keys->repeatCounter)) = zero;
      keys->repeatKeys = buttonMask;
    }
  }
  else
  {
    keys->repeatKeys = current & 0x3FF;
    *((u8 *) (&keys->repeatCounter)) = zero;
  }
}
