/* Reset the object pool: clear the list globals and wipe all 128 0x34-byte
 * slots (0xD0 << 5 bytes) at D_0201E8A8. */
extern s32 D_020202A8;  /* object list head */
extern s32 D_020202AC;  /* object search cursor (resume point) */
extern s32 D_020202B0;  /* last object searched */
extern u8 D_0201E8A8[]; /* 128 x 0x34-byte object slots */
void sub_080008A0(void *, s32);

void sub_08016160(void) {
    D_020202A8 = 0;
    D_020202AC = 0;
    D_020202B0 = 0;
    sub_080008A0(D_0201E8A8, 0xD0 << 5);
}
