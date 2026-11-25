/* Set flag bits `bits` in the +0x64 halfword of each of the 10 slot objects,
 * skipping empty slots. */
void sub_08018694(void *arg0, u16 bits)
{
    u32 *slots;
    u32 *p;
    s32 i;

    slots = *(u32 **)((u8 *)arg0 + 0x3C);
    p = slots + 0x20;
    i = 9;
    do {
        u32 member = *p;
        if (member != 0) {
            *(u16 *)(member + 0x64) |= bits;
        }
        p++;
        i--;
    } while (i >= 0);
}
