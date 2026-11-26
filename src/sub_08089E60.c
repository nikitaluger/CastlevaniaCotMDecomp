extern void sub_08003A6C(s32, s32, s32);
extern void sub_080C31E0(void *, void *);
extern void sub_080C31E4(void *, void *, s32);
extern s32 gMainObjTimerCallback[];

/* Initialises an entity's state and sprite: installs a data table and update
 * params, clears a sprite flag and timer, then advances the script step and
 * dispatches the matching callback. */
void sub_08089E60(void *arg0)
{
  u8 *self = (u8 *)arg0;
  u8 *state = *((u8 **)(self + 0x6C));
  u8 *actor = state + 4;
  u8 *sprite = *((u8 **)(self + 0x38));
  u8 zero;
  u16 masked;
  *((s32 *)(sprite + 0x24)) = 0x085042D4;
  sub_08003A6C((s32)(state + 0x20), 0, (s32)0x08504364);
  masked = (*((u16 *)(sprite + 0x02))) & 0xFFEF;
  zero = 0;
  *((u16 *)(sprite + 0x02)) = masked;
  *((s32 *)(state + 0x04)) = 0x00400000;
  *((s32 *)(actor + 0x04)) = 0x00870000;
  *((u8 *)((self + ((*((s16 *)(self + 0x22))) * 2)) + 0x19)) = zero;
  {
    s32 *eventPtr = gMainObjTimerCallback;
    sub_080C31E4(self + 0x18, self + 0x22, *eventPtr);
  }
  *((u8 *)((self + ((*((s16 *)(self + 0x22))) * 2)) + 0x19)) += 1;
  {
    u8 *stepBase = self + 0x18;
    s16 step = *((s16 *)(self + 0x22));
    stepBase += step * 2;
    sub_080C31E0(self, *((void **)((*((u32 *)(self + 0x14))) + ((*stepBase) * 4))));
  }
}
