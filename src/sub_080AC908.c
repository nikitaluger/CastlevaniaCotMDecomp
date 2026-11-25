extern void sub_080114A8(void *, void *, s16, s32);
extern void sub_08011528(void *, void *);
extern void sub_080C2E68(void *, void *, s32);

typedef struct { s32 v[8]; } DeltaTable;
extern const DeltaTable D_08102224;
extern const u8 D_08102244[];

/* Advance an entity's repeating aim/motion sequence: when the step timer runs out,
 * nudge its position by the current fixed-point delta, reload the timer from the
 * duration table and advance the step. Then refresh the animation and copy the
 * aim control byte into the two child objects. */
void sub_080AC908(void *gfx, void *anim, void *work, void *aim)
{
  s32 deltas[8];
  u8 durations[8];
  s32 stepIdx;
  u32 step;
  s32 timer;
  s16 angle;
  void *child;
  u8 value;
  *(DeltaTable *)deltas = D_08102224;
  sub_080C2E68(durations, (void *)D_08102244, 8);
  if (*((u8 *)((s8 *)aim + 0x11)) != 0)
  {
    if (*((s32 *)((s8 *)aim + 0x08)) == 0)
    {
      stepIdx = *((s32 *)((s8 *)aim + 0x0C));
      *((s32 *)((s8 *)work + 0x0C)) = *((s32 *)((s8 *)work + 0x0C)) + deltas[stepIdx];
      step = *((u32 *)((s8 *)aim + 0x0C));
      value = durations[step];
      *((s32 *)((s8 *)aim + 0x08)) = (s32)value;
      *((u32 *)((s8 *)aim + 0x0C)) = (step + 1) & 7;
    }
    else
    {
      timer = *((s32 *)((s8 *)aim + 0x08));
      timer = timer - 1;
      *((s32 *)((s8 *)aim + 0x08)) = timer;
    }
  }
  sub_08011528(gfx, anim);
  if ((*((u8 *)((s8 *)anim + 0x00)) & 0x02) && (*((u8 *)((s8 *)aim + 0x10)) != 0))
  {
    angle = *((s16 *)((s8 *)anim + 0x0E));
    sub_080114A8(gfx, anim, angle, 0);
  }
  child = *((void **)((s8 *)aim + 0x00));
  value = *((u8 *)((s8 *)aim + 0x10));
  *((u8 *)((s8 *)child + 0x50)) = value;
  child = *((void **)((s8 *)aim + 0x04));
  value = *((u8 *)((s8 *)aim + 0x10));
  *((u8 *)((s8 *)child + 0x50)) = value;
}
