extern void setPolarOffset(void *, s32, s32);
extern void sub_080C31E4(void *, void *, s32);
extern void sub_080C31E0(void *, s32);
/* Set the work state's facing angle to 0x4000, build a downward vector of
 * length 0x4000 at work+0x10/+0x14, increase its y component by 25%, then
 * clear this actor's script-action byte and advance the script. */
void sub_0803FC64(void *obj)
{
  u8 *actor = (u8 *) obj;
  u8 *work = *((u8 **) (actor + 0x3C));
  const s32 *advance;
  u8 *entry;
  *((s32 *) (work + 0x4C)) = 0x4000;
  setPolarOffset(work, 0x4000, 0x4000);
  {
    s32 yVel = *((s32 *) (work + 0x14));
    *((s32 *) (work + 0x14)) = yVel + (yVel >> 2);
  }
  *((u8 *) ((actor + (((s32) (*((s16 *) (actor + 0x22)))) * 2)) + 0x19)) = 0;
  advance = (const s32 *) 0x08671BB0;
  entry = actor + 0x18;
  sub_080C31E4(entry, actor + 0x22, *advance);
  *((u8 *) ((actor + (((s32) (*((s16 *) (actor + 0x22)))) * 2)) + 0x19)) += 1;
  entry += ((s32) (*((s16 *) (actor + 0x22)))) * 2;
  sub_080C31E0(actor, *((s32 *) (((u8 *) (*((u32 *) (actor + 0x14)))) + ((*((u8 *) entry)) * 4))));
}
