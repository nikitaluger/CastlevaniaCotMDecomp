s32 sub_080C31E0(s32, s32);
void stepAnimationTrack(void *, void *);
s32 getAngleTurnDirection(u16, s32);
void sub_080C31E4(void *, void *, s32);

void sub_080A43AC(void *arg0) {
    void *r5 = *(void **)((u8 *)arg0 + 0x3C);
    s32 litAddr = 0x08671BFC;
    s32 idx = *(s16 *)((u8 *)arg0 + 0x22);
    s32 val = sub_080C31E0((s32)(*(u8 *)((u8 *)arg0 + idx * 2 + 0x19)) << 9, *(s32 *)litAddr);
    *(s32 *)((u8 *)r5 + 0xC) = *(s32 *)((u8 *)arg0 + 0x7C) - (val << 1);
    {
        s32 cnt = *(s32 *)((u8 *)arg0 + 0x8C) - 1;
        *(s32 *)((u8 *)arg0 + 0x8C) = cnt;
        if (cnt == 0) {
            u16 one = 1;
            u16 v = *(u16 *)r5;
            *(u16 *)r5 = v | one;
        }
    }
}

/* Turn the sprite's angle toward the heading stored at self+0x6C in 1/64
 * steps; on reaching or overshooting it, snap to the heading and advance the
 * current script step. */
void sub_080A47FC(void *arg0)
{
  s32 *callback;
  s32 turn;
  u16 angle;
  void *sprite;
  sprite = *((void **) (((s8 *) arg0) + 0x38));
  stepAnimationTrack(sprite, (void *)((*((s32 *) (((s8 *) arg0) + 0x3C))) + 0x34));
  angle = *((u16 *) (((s8 *) sprite) + 8));
  turn = getAngleTurnDirection(angle, *((s32 *) (((s8 *) arg0) + 0x6C)));
  *((u16 *) (((s8 *) sprite) + 8)) = (u16) (angle + (turn << 0xA));
  if ((turn != getAngleTurnDirection(*((u16 *) (((s8 *) sprite) + 8)), *((s32 *) (((s8 *) arg0) + 0x6C)))) || (turn == 0))
  {
    s32 target;
    s32 zero;
    target = *((s32 *) (((s8 *) arg0) + 0x6C));
    zero = 0;
    *((u16 *) (((s8 *) sprite) + 8)) = (u16) target;
    *((s8 *) (((s8 *) (((*((s16 *) (((s8 *) arg0) + 0x22))) * 2) + arg0)) + 0x19)) = zero;
    callback = (s32 *) 0x08671BB0;
    sub_080C31E4(arg0 + 0x18, arg0 + 0x22, *callback);
  }
}
