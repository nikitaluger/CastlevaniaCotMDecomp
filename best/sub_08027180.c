extern s32 sub_080C31E8(void *, void *, s32, s32);
extern void sub_08027A4C(void *, s32, void *, void *);

void sub_08027180(void *arg0)
{
  u8 *effect = arg0;
  u8 *state = *((u8 **) (effect + 0x3C));
  u8 *state48 = state + 0x48;
  u16 status = *((u16 *) (effect + 0x64));
  u32 masked = (u16) (status & 8);
  u8 *step;
u8 *__repair_phase_step;
  s32 *dispatch;
s32 *__repair_phase_dispatch;

  if (masked != 0)
  {
    {
      u32 stepAddr = (u32) (*((s16 *) (effect + 0x22)) * 2) + (u32) effect;
      *((u8 *) (stepAddr + 0x19)) = 0;
    }
    dispatch = (s32 *) 0x08671BD0;
    sub_080C31E8(effect + 0x18, effect + 0x22, 3, *dispatch);
    return;
  }
  if ((0x10 & status) != 0)
  {
    __repair_phase_step = (*((s16 *) (effect + 0x22)) * 2) + effect;
    *((u8 *) (__repair_phase_step + 0x19)) = masked;
    __repair_phase_dispatch = (s32 *) 0x08671BD0;
    sub_080C31E8(effect + 0x18, effect + 0x22, 4, *__repair_phase_dispatch);
    return;
  }
  {
    s32 val = *((s32 *) (state48 + 0xC));
    if ((u32) (val + 0xFFFF4FFF) <= 0x1FFE)
      *((s32 *) (state48 + 0xC)) = 0xC000;
    else
      *((s32 *) (state48 + 0xC)) = (val + 0x1200) & 0xFFFF;
    sub_08027A4C(effect, *((s32 *) (state48 + 0xC)), state + 8, state + 0xC);
  }
}
