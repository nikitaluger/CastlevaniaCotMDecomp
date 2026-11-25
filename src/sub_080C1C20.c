extern void sub_080C18AC(void *, void *);
extern void sub_080C1984(void *, void *, void *);
extern void sub_080C1764(void);

// Packs the two operand word-pairs into 20-byte forms, flips a flag bit in the
// second form, combines both forms into result, then finalizes the operation.
void sub_080C1C20(s32 wordA0, s32 wordA1, s32 wordB0, s32 wordB1) {
    u8 packedA[0x14];
    u32 packedB[5];
    u8 result[0x14];
    volatile s32 a0 = wordA0, a1 = wordA1, b0 = wordB0, b1 = wordB1;
    sub_080C18AC((void *)&a0, packedA);
    sub_080C18AC((void *)&b0, packedB);
    packedB[1] ^= 1;
    sub_080C1984(packedA, packedB, result);
    sub_080C1764();
}
