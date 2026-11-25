void sub_0809C840(void *, s32);
void sub_080C31E4(void *, void *, s32);
s32 sub_080C31E0(void *, void *);
struct Zero { u32 w; u8 b; };

/* Motion step: refresh the animator flag, advance the swing angle and offset
 * X by its sine lookup; on step 0x1E latch the facing-based vertical motion,
 * clear the step byte and advance the script. */
void sub_0809AFE4(void *arg0)
{
  u8 *self = arg0;
  s32 sprite = *((s32 *) (self + 0x38));
  u8 *work = *((u8 **) (self + 0x3C));
  u8 *body = work + 0x48;
  s32 sine;
  s32 *sineTable;
  s32 *handlerTable;
  sub_0809C840((void *) self, sprite);
  *((u16 *) (body + 4)) = (*((u16 *) (body + 4))) + 0x217;
  sineTable = (s32 *) 0x08671BFC;
  sine = sub_080C31E0((void *) (*((u16 *) (body + 4))), (void *) (*sineTable));
  *((s32 *) (work + 0x0C)) = (*((s32 *) (work + 0x48))) - (sine * 8);
  if ((*((u8 *) ((self + ((*((s16 *) (self + 0x22))) * 2)) + 0x19))) == 0x1E)
  {
    struct Zero z = {0, 0};
    *((s32 *) (work + 0x10)) = (*((s32 *) (self + 0x6C))) << 0xF;
    *((s32 *) (work + 0x14)) = z.w;
    *((s32 *) (self + 4)) = 0xB4 << 1;
    *((u8 *) ((self + ((*((s16 *) (self + 0x22))) * 2)) + 0x19)) = z.b;
    handlerTable = (s32 *) 0x08671BB0;
    sub_080C31E4(self + 0x18, self + 0x22, *handlerTable);
  }
}
