extern u8 D_080CAB40[];
extern u8 D_080CAB60[];

/* Match the 8-byte signature at obj+0x600 against the four known patterns in
 * D_080CAB40; on a match, return the bit index from D_080CAB60 for that pattern
 * if the corresponding bit of the flags byte at obj+0x634 is set, else 0. */
u32 sub_0800BF70(void *arg0)
{
    u8 *base = arg0;
    u32 signature = 0xFF;
    u32 i = 0, j;
    u8 *sigBytes = base + 0x600;
    u8 *known = D_080CAB40;

    for (i = 0; i <= 3; ) {
        u32 matches;
        u32 next;
        u8 *candidate;
        matches = 1;
        j = 0;
        next = i + 1;
        candidate = (u8 *)((i * 8) + (u32)known);
        while (j <= 7) {
            if (sigBytes[j] != *candidate) matches = 0;
            candidate++;
            j++;
        }
        if (matches) signature = i;
        i = next;
    }
    if (signature == 0xFF) return 0;

    for (i = 0; i <= 3; i++) {
        if (signature == i) {
            s32 flags = *(u8 *)((u8 *)arg0 + 0x634);
            s32 bit = D_080CAB60[i];
            if ((flags >> bit) & 1) return bit;
        }
    }
    return 0;
}
