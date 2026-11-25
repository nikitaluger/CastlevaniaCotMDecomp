void sub_080C31E4(void *, void *, s32);
void sub_080C31E8(void *, void *, s32, s32);
void sub_08097EF4(s32, void *, s32, s32);
void sub_08097F70(void *, s32);
/* Hold-timer step: add 0x34 per frame to the sprite's +4 timer; past 0x3FF,
 * clear the sprite flag 0x40, reset the effect byte at self+0x7C and the script
 * substep, then advance the script engine. The +6 mirror always follows +4. */
void sub_0809FED0(void *arg0)
{
  u8 *self = (u8 *) arg0;
  u8 *sprite = *((u8 **) (self + 0x38));
  u16 timer = (*((u16 *) (sprite + 4))) + 0x34;
  s32 zero = 0;
  *((u16 *) (sprite + 4)) = (*((u16 *) (sprite + 4))) + 0x34;
  if (((s32) (((u32) timer) << 16)) > 0x03FF0000)
  {
    *((u8 *) (sprite + 0x2A)) &= 0xBF;
    *((u8 *) (self + 0x7C)) = zero;
    *((u8 *) ((self + ((*((s16 *) (self + 0x22))) * 2)) + 0x19)) = zero;
    {
      s32 *scriptStep = (s32 *) 0x08671BD0;
      sub_080C31E8(self + 0x18, self + 0x22, 0, *scriptStep);
    }
  }
  *((u16 *) (sprite + 6)) = *((u16 *) (sprite + 4));
}

void sub_0809FE54(void *arg0);
void sub_080A0340(void *arg0, u8 arg1);
