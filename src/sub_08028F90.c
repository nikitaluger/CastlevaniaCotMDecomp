extern void sub_08011368(void *, void *, s32, s32);
extern s32 sub_080C364C(s32, s32);
extern s32 sub_080C31E0(s32, s32);
extern void sub_080C31E4(void *, void *, s32);
extern s32 D_08671BFC;
extern s32 D_08671BB0;

/* Set an oscillating velocity from a sine lookup of the step counter, choose
 * the direction sign from the sprite flag, start frame 0 and advance the script. */
void sub_08028F90(void *arg0)
{
  u8 *self = arg0;
  void *sprite;
  u8 *state;
  s32 *event;
  u8 *anim;
  u8 *extra;
  u32 zero;
  s32 *global;
  s32 angle;
  s32 directionMask;
  s32 sway;

  sprite = *((void **) (self + 0x38));
  state = *((u8 **) (self + 0x3C));
  anim = state + 0x34;
  extra = state + 0x48;
  zero = 0;
  *((u32 *) (extra + 0x08)) = zero;
  directionMask = 0xC000;
  *((u32 *) (state + 0x10)) = directionMask;
  if (!((*((u16 *) (((u8 *) sprite) + 0x02))) & 0x10))
  {
    *((u32 *) (state + 0x10)) = -directionMask;
  }
  sub_08011368(sprite, anim, 0, 1);
  global = &D_08671BFC;
  angle = sub_080C364C((*((u32 *) (extra + 0x08))) << 16, 0x50);
  angle = angle + 0x4000;
  sway = sub_080C31E0(angle, *global);
  sway = sway << 4;
  *((u32 *) (state + 0x0C)) = (*((u32 *) (extra + 4))) + sway;
  *((u32 *) (extra + 0x08)) = (*((u32 *) (extra + 0x08))) + 1;
  *((u8 *) ((self + ((*((s16 *) (self + 0x22))) * 2)) + 0x19)) = zero;
  event = &D_08671BB0;
  global = event;
  sub_080C31E4(self + 0x18, self + 0x22, *global);
}
