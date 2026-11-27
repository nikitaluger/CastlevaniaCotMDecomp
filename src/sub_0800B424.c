extern s32 isResourceLoaded(s32);
extern void sub_08005E80(u16);
extern void sub_0800B824(u16, u16, s32);
extern void _call_via_r3(void *, void *, s32, void *);
extern u8 gCameraState[];
extern s32 gScriptStepCallbacks[];
extern s32 gMenuScriptCallback[];

/* Menu confirm handler: once the global flags allow it, reads the object's
 * state byte and either grants the entry and fires the "select" callback, or
 * clears it and fires the "deselect" callback. */
void sub_0800B424(u8 *menu)
{
  u8 *target = *((u8 **) (menu + 0x3C));
  s32 result;
  u32 scratch;
  u8 state;
  s16 slot;
  result = isResourceLoaded(0xAD << 1);
  if (result != 0)
  {
    return;
  }
  scratch = (u32) gCameraState;
  if ((*((u16 *) (scratch + 0x146C))) & 1)
  {
    goto doit;
  }
  if (((*((u16 *) (scratch + 0x146C))) & 2) == 0)
  {
    return;
  }
  doit:
  state = *((u8 *) (target + (0xC7 * 8)));

  if (state != 0)
  {
    sub_08005E80(0x157);
    sub_0800B824(0x81DA, 0x9C << 2, 0xC0 << 3);
    slot = (scratch = *((s16 *) (menu + 0x22)));
    *((u8 *) ((menu + (slot * 2)) + 0x19)) = result;
    {
      s32 *pd = gScriptStepCallbacks;
      _call_via_r3(menu + 0x18, menu + 0x22, 0, (void *) (*pd));
    }
    return;
  }
  *((u8 *) (target + 0x635)) = state;
  sub_08005E80(0x159);
  slot = *((s16 *) (menu + 0x22));
  *((u8 *) ((menu + (slot * 2)) + 0x17)) = state;
  {
    s32 *pd = gMenuScriptCallback;
    _call_via_r3(menu + 0x18, menu + 0x22, 0x10, (void *) (*pd));
  }
}
