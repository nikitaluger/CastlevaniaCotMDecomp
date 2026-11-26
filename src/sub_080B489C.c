/* Animation script step: play animation 0x68 on the actor's sprite; when the
 * current step's action byte is 6, set the work byte at +0x69, clear the
 * linked sprite flag and the step's paired byte at +0x17, then advance the
 * script through the table at 0x08671BD8 with command 3. */
extern void setObjectAnimation(s32, void *, s32, s32);
extern void sub_080C31E8(void *, void *, s32, s32);

void sub_080B489C(void *arg0)
{
  u8 *self = (u8 *) arg0;
  s32 sprite = *((s32 *) (self + 0x38));
  u8 *work = *((u8 **) (self + 0x3C));
  u8 *animState = work + 0x34;
  u8 *spriteData = work + 0x48;

  setObjectAnimation(sprite, animState, 0x68, 0);
  if ((*((u8 *) ((self + ((*((s16 *) (self + 0x22))) * 2)) + 0x19))) == 6)
  {
    u8 *workFlag = work + 0x69;
    s32 zero = 0;
    s32 *scriptTable;
    *workFlag = 1;
    *(spriteData + 0x1F) = (u8)zero;
    *((u8 *) ((self + ((*((s16 *) (self + 0x22))) * 2)) + 0x17)) = (u8)zero;
    scriptTable = (s32 *) 0x08671BD8;
    sub_080C31E8(self + 0x18, self + 0x22, 3, *scriptTable);
  }
}
