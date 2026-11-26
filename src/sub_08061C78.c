extern void divideInt(s32 a, s32 b);
extern u8 gGameStatus[];
/* Rescale the 16-bit value at gGameStatus+0xAC by 1000/980 via BIOS signed
 * division (swi #6); the quotient is left in r0 for the caller. */
volatile int sub_08061C78(void)
{
  u16 scaledValue;
  u8 *state = gGameStatus;
  u16 value = *((u16 *) (state + 0xAC));
  scaledValue = value;
 do { } while (0);
  divideInt(scaledValue * 0x3E8, 0x3D4);
}

extern u8 D_080D9B3C[];
s32 sub_08061C9C(u32 arg0, s32 arg1);
extern u8 D_080DABDC[];
s32 sub_08061CE8(u32 arg0, s32 arg1);
void sub_08061D30(u32 arg0, s32 arg1);
