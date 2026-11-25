extern s32 sub_08011408(s32, void *, s32, s32, s32);
extern s32 sub_0802F89C(s32, s32);
extern void sub_080C31E4(void *, void *, s32);
struct Z { u16 w; u8 b; };
/* Steps the linked animation state; once its step counter passes 0x4F, spawns
 * a new object at the state's stored position and resets this object's slot. */
void sub_0802F238(void *arg0)
{
  u8 *obj = (u8 *) arg0;
  s32 context = *((s32 *) (obj + 0x38));
  u8 *state = *((u8 **) (obj + 0x3C));
  u8 *stateBuf = state + 0x34;
  u8 *counterPtr = state + 0x48;
  s32 stepCount;
  s32 *charData;
  struct Z z = {0, 0};
  *((s32 *) (state + 0x48)) = z.w;
  sub_08011408(context, stateBuf, (float) 0, 0, 1);
  stepCount = *((u16 *) (counterPtr + 8));
  stepCount = stepCount + 1;
  *((u16 *) (counterPtr + 8)) = stepCount;
  if (((s16) stepCount) > 0x4F)
  {
    sub_0802F89C(*((s32 *) (state + 8)), *((s32 *) (state + 0xC)));
    *((u8 *) ((obj + ((*((s16 *) (obj + 0x22))) * 2)) + 0x19)) = z.b;
    charData = (s32 *) 0x08671BB0;
    sub_080C31E4(obj + 0x18, obj + 0x22, *charData);
  }
}
