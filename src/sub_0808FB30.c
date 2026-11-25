extern void sub_080C31E8(void *, void *, s32, u32);
/* When the object's animation reports that it has finished (flag bit 2),
 * clear its frame counter and advance the object's command script. */
void sub_0808FB30(void *arg0)
{
  void *obj = arg0;
  u8 *anim = *((u8 **) (((u8 *) obj) + 0x3C));
  u8 zero = 0;
  if ((*((u8 *) (anim + 0x18))) & 2)
  {
    u16 zero16 = 0;
    *((u16 *) (anim + 0x14)) = zero16;
    *((u8 *) ((((u8 *) obj) + ((*((s16 *) (((u8 *) obj) + 0x22))) * 2)) + 0x19)) = zero;
    {
      u32 *scriptTable = (u32 *) 0x08671BD0;
      sub_080C31E8(((u8 *) obj) + 0x18, ((u8 *) obj) + 0x22, 1, *scriptTable);
    }
  }
}
