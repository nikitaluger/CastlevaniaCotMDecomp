extern u32 D_020230F0;
extern u32 D_040000D4;
extern u32 D_00004770;
extern u32 D_0866CA14;
s32 sub_080C31E4(void *, s32, s32);

/* Timed-action record: handler index +0, frames left +2, elapsed frames +4,
 * user data pointer +8, finished flag +0xC. */
struct Timer {
    u8 handler;
    u16 frames;
    u16 elapsed;
    s32 data;
    u8 finished;
};

/* Start `timer` on handler `handler` (index into the table at 0x0866CA14),
 * due after one frame, carrying `data` as its payload. */
void startEffectTimer(struct Timer *timer, u8 handler, s32 data)
{
  timer->handler = handler;
  timer->frames = 1;
  timer->elapsed = 0;
  timer->data = data;
  timer->finished = 0;
}

/* Zero the 0x100-byte work area at D_020230F0 through DMA3 and return the DMA
 * control word. */
s32 sub_08003AA0(void)
{
  s32 zero = 0;
  *(s32 *)&D_040000D4 = (s32)&zero;
  *(s32 *)(&D_040000D4 + 1) = (s32)&D_020230F0;
  *(s32 *)(&D_040000D4 + 2) = 0x85000040;
  return *(s32 *)(&D_040000D4 + 2);
}

/* Tick the timed action `timer`: 0 when it was already spent, 1 while it is
 * still counting down, and when the countdown reaches zero it dispatches the
 * handler for timer->handler with (timer, sprite). */
s32 stepDelayTimer(void *timer, s32 sprite)
{
  u16 v = *(u16 *)((u8 *)timer + 0x02);
  if (v == 0)
    return 0;
  v--;
  *(u16 *)((u8 *)timer + 0x02) = v;
  if (((u32)v << 16) == 0)
    return sub_080C31E4(timer, sprite, *(s32 *)(*(u8 *)timer * 4 + (s32)&D_0866CA14));
  return 1;
}
