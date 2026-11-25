/* Three-way comparison of two {type, f4, f8, fC} records for sorting: types
 * 0 and 1 sort last, types 4 and 2 use their f4 field specially, and the rest
 * are ordered by f4, then signed f8, then unsigned fC. */
s32 sub_080C2A60(void *arg0, void *arg1) {
    s32 aTypeLow, bTypeLow, aType4, bType4, aType4Again, bType4Again;
    s32 aType2, bType2, aType2Again, bType2Again;
    u32 aType, bType, aTypeAgain;
    s32 aF4, aF8, bF8, result;
    u32 aFC, bFC;

    aTypeLow = 0;
    aType = *(u32*)arg0;
    if (aType <= 1U) aTypeLow = 1;
    if (aTypeLow != 0) return 1;
    bTypeLow = 0;
    bType = *(u32*)arg1;
    if (bType <= 1U) bTypeLow = 1;
    if (bTypeLow != 0) return 1;
    aType4 = 0;
    if (aType == 4) aType4 = 1;
    if (aType4 != 0) {
        bType4 = 0;
        if (bType == 4) bType4 = 1;
        if (bType4 != 0)
            return *(s32*)((u8*)arg1+4) - *(s32*)((u8*)arg0+4);
    }
    aType4Again = 0;
    aTypeAgain = *(u32*)arg0;
    if (aTypeAgain == 4) aType4Again = 1;
    if (aType4Again != 0) goto tailA;
    bType4Again = 0;
    if (bType == 4) bType4Again = 1;
    if (bType4Again != 0) {
tailB:
        result = (*(s32*)((u8*)arg1+4) != 0) ? 1 : -1;
        goto ret;
    }
    aType2 = 0;
    if (aTypeAgain == 2) aType2 = 1;
    if (aType2 != 0) {
        bType2 = 0;
        if (bType == 2) bType2 = 1;
        if (bType2 != 0) return 0;
    }
    aType2Again = 0;
    if (aTypeAgain == 2) aType2Again = 1;
    if (aType2Again != 0) goto tailB;
    bType2Again = 0;
    if (bType == 2) bType2Again = 1;
    if (bType2Again != 0) {
tailA:
        result = (*(s32*)((u8*)arg0+4) != 0) ? -1 : 1;
        goto ret;
    }
    goto f4sec;
ret:
    return result;
f4sec:
    aF4 = *(s32*)((u8*)arg0+4);
    if (aF4 != *(s32*)((u8*)arg1+4))
        return (aF4 != 0) ? -1 : 1;
    aF8 = *(s32*)((u8*)arg0+8);
    bF8 = *(s32*)((u8*)arg1+8);
    if (aF8 > bF8)
        return (aF4 != 0) ? -1 : 1;
    if (aF8 < bF8)
        return (aF4 != 0) ? 1 : -1;
    aFC = *(u32*)((u8*)arg0+0xC);
    bFC = *(u32*)((u8*)arg1+0xC);
    if (aFC > bFC)
        return (aF4 != 0) ? -1 : 1;
    if (aFC < bFC)
        return (aF4 != 0) ? 1 : -1;
    return 0;
}
