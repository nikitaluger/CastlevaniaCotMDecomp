/* Find the first object after `object` in the 0xBC-byte object pool whose
 * flag word at +0 matches `mask`; return NULL if there is none. */
void *sub_080015E0(s32 mask, s32 object) {
    u32 p = (u32)(object + 0xBC);
    u32 usedEnd = *(u32 *)0x02025B74;
    if (p >= usedEnd) return 0;
    {
        u32 limit = usedEnd;
        do {
            if (*(s16 *)p & mask) goto found;
            p += 0xBC;
        } while (p < limit);
        return 0;
found:
        return (void *)p;
    }
}
