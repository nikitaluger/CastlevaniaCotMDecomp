/* Update a scripted effect: seed its random horizontal motion, run its
 * animation and script step, then handle the finish branch with a facing-
 * dependent speed and a follow-up script. */
extern void sub_08011368(void *, void *, s32, s32);
extern void sub_08026954(void *, void *);
extern s32 sub_08014990(void *);
extern void sub_080269D4(void *, s32);
extern void sub_080C31E0(s32, s32);
extern void sub_080C31E8(void *, void *, s32, void *);
extern void *D_08671BD0;
struct S_02025FF0
{
  u8 _0[0x189C];
  u32 v;
};
extern struct S_02025FF0 D_02025FF0;
void sub_08026430(void *arg0)
{
  void *sprite = *((void **) (((u8 *) arg0) + 0x38));
  u8 *fxState = *((u8 **) (((u8 *) arg0) + 0x3C));
  u8 *motion = fxState + 0x34;
  u8 *state48 = fxState + 0x48;
  u8 *scriptPc;
  u8 randomFlag;
  s32 facing;
  *((u32 *) (fxState + 0x14)) = 0;
  *((u32 *) (fxState + 0x10)) = 0;
  randomFlag = motion[1];
  if (randomFlag == 1)
  {
    u32 globalRand = D_02025FF0.v;
    do
    {
      *((u32 *) (state48 + 0x14)) = ((((s32) (globalRand + (globalRand >> 31))) >> 1) & randomFlag) ? (0x80 << 9) : 0;
    }
    while (0);
  }
  sub_08011368(sprite, motion, 5, 0);
  *((u32 *) (((u8 *) arg0) + 0x14)) = 0x0866D998;
  *((u16 *) (((u8 *) arg0) + 0x22)) = (*((u16 *) (((u8 *) arg0) + 0x22))) + 1;
  (((u8 *) arg0) + ((*((s16 *) (((u8 *) arg0) + 0x22))) * 2))[0x19]++;
  {
    s32 stepIndex = (*((s16 *) (((u8 *) arg0) + 0x22))) * 2;
    u8 *stepPtr;
    scriptPc = ((u8 *) ((0, arg0))) + 0x18;
    stepPtr = scriptPc + stepIndex;
    {
      u8 opcode = *stepPtr;
      sub_080C31E0((s32) arg0, *((s32 *) (((u8 *) (*((u32 *) (((u8 *) arg0) + 0x14)))) + (opcode * 4))));
    }
  }
  *((u16 *) (((u8 *) arg0) + 0x22)) = (*((u16 *) (((u8 *) arg0) + 0x22))) - 1;
  if (motion[0] & 2)
  {
    sub_08026954(state48 + 8, state48 + 0x0C);
    facing = sub_08014990(sprite);
    {
      u32 speed = 0xE0 << 8;
      if (facing < 0)
      {
        speed = 0xA0 << 8;
      }
      *((u32 *) (state48 + 0x38)) = speed;
    }
    sub_080269D4(arg0, 0x1C);
    (((*((s16 *) (((u8 *) arg0) + 0x22))) * 2) + ((u8 *) arg0))[0x19] = 0;
    {
      void **scriptTable = &D_08671BD0;
      sub_080C31E8(((u8 *) arg0) + 0x18, ((u8 *) arg0) + 0x22, 4, *scriptTable);
    }
    *((u16 *) (state48 + 0x1E)) = 0;
  }
}
