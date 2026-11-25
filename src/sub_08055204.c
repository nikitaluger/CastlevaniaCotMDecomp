/* Per-frame update for a scripted attack/effect: checks whether it should be removed,
 * handles proximity/target and flag events (optionally firing an event), advances the
 * script step to dispatch a callback, then repositions the sprite's Y on screen. */
extern u8 D_02021E90[];
extern u8 D_02025FF0[];
extern u8 D_0866E730[];
extern u32 D_08671BDC[];
s32 sub_080141AC(void *, void *);
void sub_08013C5C(void *, void *);
s32 sub_08013558(void *, void *, void *);
void sub_08013978(void *, void *);
void sub_080142C0(void *, void *);
void sub_08013AC4(void *);
void sub_08005E80(s32);
void sub_080C31E8(void *, void *, s32, u32);
s32 sub_08013B5C(void *, void *);
void sub_080C31E0(void *, s32);
void sub_080113A8(void *, void *);
void sub_0801165C(void *, s32);
void sub_08055990(void *, void *);
void sub_08013C8C(void *, void *);

void sub_08055204(u8 *arg0)
{
  u8 *sprite;
  u8 *state;
  u8 *scratch;
  u8 *extra;
  u8 *coordBase;
  u8 *scrollPtr;
  u32 scrollOff;
  u32 scrollY;
  u8 cmd;
  u8 *script;
  s32 stepOff;
  sprite = *((u8 **) (arg0 + 0x38));
  state = *((u8 **) (arg0 + 0x3C));
  scratch = state + 0x34;
  extra = state + 0x48;
  if (sub_080141AC(sprite, state) == 1)
  {
    if (*((u8 *) ((((u32) (*((s16 *) (arg0 + 0x22)))) * 2) + ((u32) arg0) + 0x1A)) <= 2) return;
  }
  sub_08013C5C(arg0, sprite);
  if (sub_08013558(sprite, state, *((void **) (state + 0x28))) != 0)
  {
    sub_08013978(arg0, *((void **) (state + 0x28)));
  }
  sub_080142C0(arg0, *((void **) (state + 0x28)));
  if ((*((u16 *) state)) & 1)
  {
    if (*((u8 *) ((((u32) (*((s16 *) (arg0 + 0x22)))) * 2) + ((u32) arg0) + 0x1A)) != 5)
    {
      u32 *callback;
      sub_08013AC4(arg0);
      sub_08005E80(0x80);
      *((u8 *) (((((u32) (*((s16 *) (arg0 + 0x22)))) * 2) + ((u32) arg0)) + 0x1B)) = 0;
      callback = D_08671BDC;
      sub_080C31E8(arg0 + 0x18, arg0 + 0x22, 5, *callback);
    }
  }
  if (sub_08013B5C(sprite, state) == 0)
  {
    u8 *stepPtr;
    *((u32 *) (arg0 + 0x14)) = (u32) D_0866E730;
    *((u16 *) (arg0 + 0x22)) = (*((u16 *) (arg0 + 0x22))) + 1;
    stepPtr = (u8 *) ((((u32) (*((s16 *) (arg0 + 0x22)))) * 2) + ((u32) arg0));
    *((u8 *) (stepPtr + 0x19)) = (*((u8 *) (stepPtr + 0x19))) + 1;
    stepOff = (*((s16 *) (arg0 + 0x22))) * 2;
    script = arg0;
    script += 0x18;
    cmd = *((u8 *) (((u32) script) + ((u32) stepOff)));
    sub_080C31E0((s32) arg0, *((u32 *) ((*((u32 *) (arg0 + 0x14))) + (cmd * 4))));
    *((u16 *) (arg0 + 0x22)) = (*((u16 *) (arg0 + 0x22))) - 1;
    if (((*((u16 *) (arg0 + 2))) & 0x8000) == 0)
    {
      sub_080113A8(sprite, scratch);
      sub_0801165C(state, 0);
    }
    else
    {
      return;
    }
  }
  sub_08055990(sprite, state);
  sub_08013C8C(arg0, sprite);
  {
    s32 worldY = (*((s32 *) (state + 0x0C))) + (*((s32 *) (extra + 0x00)));
    coordBase = D_02021E90;
    scrollPtr = D_02025FF0;
    scrollPtr += 0x18A8;
    scrollOff = (((u32) (*((u8 *) scrollPtr))) + 1) * 0x40;
    coordBase += 0x127C;
    scrollY = *((u32 *) (coordBase + scrollOff));
    *((u32 *) (sprite + 0x18)) = worldY - ((scrollY + 0xFFFF8000) & 0xFFFF0000);
  }
}
