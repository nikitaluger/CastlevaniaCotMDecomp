void sub_080AC0FC(void *arg0) {
    u8 *self = (u8*)arg0;
    u8 *sprite = (u8*)*(u32*)(self + 0x38);
    u8 *work = (u8*)*(u32*)(self + 0x3C);
    u8 *parts;
    u8 stepCount;
    s32 *cmdTable;
    /* work: +0x68 timer table, +0x98 two spinning sub-parts, +0xC6 facing. */
    sub_080AC9B4(*(u8*)(work + 0x244), work + 0x68);
    *(u8*)(work + 0xC6) = 0xFF;
    parts = work + 0x98;
    sub_080AC9EC(sprite, work, parts);
    sub_080ACCA4(0, sprite, work, parts);
    sub_080ACCA4(1, sprite, work, parts);
    stepCount = *(u8*)(self + *(s16*)(self + 0x22) * 2 + 0x19);
    if (stepCount == 0x78) {
        *(u8*)(self + *(s16*)(self + 0x22) * 2 + 0x19) = 0;
        cmdTable = (s32*)0x08671BD0;
        sub_080C31E8(self + 0x18, self + 0x22, 2, *cmdTable);
    }
}
