extern void sub_080008A0(void *, s32);
extern u8 D_020279D0[];

/* Allocate one of the 64 0x14-byte entries of the effect pool at 0x020202C0:
 * clear it, mark it used, tag it with the next serial id (1..255) and return
 * it, or return NULL when the pool is full. */
void *sub_08016A54(void)
{
    s32 i = 0;
    u8 usedFlag = 0x80;
    u8 *slot = (u8 *)0x020202C0;
    u8 *flags = slot;
    u8 tmp;

    for (; i < 64; i++) {
        if ((flags[0] & 0x80) == 0) {
            sub_080008A0(slot, 0x14);
            tmp = flags[0];
            tmp |= usedFlag;
            flags[0] = tmp;
            flags[1] = D_020279D0[0];
            D_020279D0[0]++;
            if (D_020279D0[0] == 0)
                D_020279D0[0] = 1;
            return slot;
        }
        flags += 0x14;
        slot += 0x14;
    }
    return 0;
}
