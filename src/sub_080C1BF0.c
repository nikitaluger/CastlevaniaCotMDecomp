extern void sub_080C18AC(void *, void *);
extern void sub_080C1984(void *, void *, void *);
extern void sub_080C1764(void);

/* Pack the two operand word-pairs into 20-byte forms, combine both forms into a
 * result, then finalize the operation. */
void sub_080C1BF0(s32 wordA0, s32 wordA1, s32 wordB0, s32 wordB1) {
    u8 packedA[0x14], packedB[0x14], result[0x14];
    volatile s32 a0 = wordA0, a1 = wordA1, b0 = wordB0, b1 = wordB1;
    sub_080C18AC((void *)&a0, packedA);
    sub_080C18AC((void *)&b0, packedB);
    sub_080C1984(packedA, packedB, result);
    sub_080C1764();
}
