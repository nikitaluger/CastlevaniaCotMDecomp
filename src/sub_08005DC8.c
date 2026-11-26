extern void sub_080C31E4(void *, void *, s32);
struct S_02021E90_Check
{
  u8 pad[0x146C];
  u16 field;
};
extern struct S_02021E90_Check gCameraState;
struct S_03000830
{
  u8 pad[4];
  u16 f4;
  u8 pad2[2];
  u16 f8;
};
extern struct S_03000830 D_03000830;
/* Reloads a text object's current slot when the global flag bit 3 is set or its
 * counter byte has reached 0x88: writes the system registers, clears the counter
 * byte and refills the slot through the shared char-data table. */
void sub_08005DC8(void *obj)
{
  u8 *bytes;
  if (((8 & gCameraState.field) != 0) || ((*((u8 *) (((u8 *) ((((u32) (*((s16 *) (((u8 *) obj) + 0x22)))) * 2) + ((u32) obj))) + 0x19))) == 0x88))
  {
    u8 zero;
    s32 *charData;
    D_03000830.f4 = 0xFF;
    D_03000830.f8 = 0;
    *((u8 *) (((u8 *) ((((u32) (*((s16 *) (((u8 *) obj) + 0x22)))) * 2) + ((u32) obj))) + 0x19)) = 0;
    bytes = (u8 *) obj;
    charData = (s32 *) 0x08671BB0;
    sub_080C31E4(bytes + 0x18, bytes + 0x22, *charData);
  }
}
