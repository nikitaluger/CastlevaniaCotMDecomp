extern s32 sub_08014938(s32); /* sign(target - pos): 1, 0 or -1 */
extern void sub_080C31E4(void *, void *, s32); /* _call_via_r2 */
extern void sub_080C31E8(void *, void *, s32, s32);
extern void sub_08011368(s32, s32, s32, s32);
extern void sub_080C31E0(void *, s32);
extern s32 sub_080133A4(s32, s32);
extern void _08012F88(void *, s32);
inline u8 *inline_fn(u8 *arg0)
{
  return arg0;
}

/* Walk command: when the actor is moving (flag 0x4), aim its horizontal
 * velocity at +/-0.75px/frame toward the target X, apply -1.5px/frame on Y,
 * then clear the current step and run the command stream handler. */
void sub_08029AD4(void *arg0)
{
  s32 *stream;
  u8 *self = (u8 *) arg0;
  u8 *work = *((u8 **) (self + 0x3C));
  if ((*((u16 *) (work + 2))) & 4)
  {
    s32 dir = sub_08014938(*((s32 *) (work + 8)));
    s32 velX = (dir < 0) ? (0xC000) : ((s32) 0xFFFF4000);
    if (work)
    {
      *((s32 *) (work + 0x10)) = velX;
    }
    else
    {
      *((s32 *) (work + 0x10)) = velX;
    }
  }
  *((s32 *) (work + 0x14)) = (s32) 0xFFFE8000;
  {
    s16 idx = *((s16 *) (inline_fn(self) + 0x22));
    self[(idx * 2) + 0x19] = 0;
  }
  stream = (s32 *) 0x08671BB0;
  sub_080C31E4(self + 0x18, self + 0x22, *stream);
}

void sub_08029A44(void *arg0);
void sub_08029998(void *arg0);
void sub_08029FB8(void *arg0);
