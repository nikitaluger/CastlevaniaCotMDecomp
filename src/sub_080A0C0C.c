extern s32 scaleByRandom(s32);
extern void sub_080A1744(void *);
extern void sub_080A1780(void *, void *, void *);
extern void sub_080C31E0(void *, s32);
extern void sub_080C31E4(void *, void *, s32);

/* Initialize an effect's random offset and animation frame, then advance the
 * script step and dispatch its handler. */
void sub_080A0C0C(void *arg0)
{
  u8 *self = (u8 *) arg0;
  u8 *sprite;
  u8 *state;
  void *anim;
  u8 *work;
  u8 *stepData;
  s32 *scriptEvent;
  s32 zero;
  s32 index;

  sprite = *((u8 **) (self + 0x38));
  state = *((u8 **) (self + 0x3C));
  anim = ((u8 *) state) + 0x34;
  work = state;
  work = ((u8 *) work) + 0x48;
  sub_080A1744(sprite);
  zero = 0;
  *((u8 *) (work + 0x16)) = (u8)zero;
  *((s32 *) (self + 0x04)) = scaleByRandom(0xF0) + 0xF0;
  sub_080A1780(sprite, anim, work);
  *((u8 *) ((*(s16 *)(self + 0x22)) * 2 + self + 0x19)) = (u8)zero;
  scriptEvent = (s32 *) 0x08671BB0;
  stepData = self + 0x18;
  sub_080C31E4(stepData, self + 0x22, *scriptEvent);
  state = (u8 *)(*(s16 *)(self + 0x22));
  (*(u8 *)((s32)state * 2 + self + 0x19))++;
  stepData += (*((s16 *) (self + 0x22))) * 2;
  index = *(u8 *)stepData;
  state = (u8 *)*((u32 *)(self + 0x14));
  sub_080C31E0(self, *((s32 *)(state + index * 4)));
}
