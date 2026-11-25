extern void sub_080C31E0(s32, s32);

/* Push a script level using the handler table at 0x0866D914: clear a counter
 * in the animation state, store the table, bump the level index and its repeat
 * counter, dispatch the level's handler, then pop the level. */
void sub_080249E4(void *arg0) {
    u8 *self = (u8 *)arg0;
    u8 *animState = *(u8 **)(self + 0x3C) + 0x48;
    s16 level;
    s32 levelOffset;
    u8 *levelBytes;
    u8 *handlerPtr;

    *(u16 *)(animState + 2) = 0;
    *(u32 *)(self + 0x14) = (u32)0x0866D914;

    *(u16 *)(self + 0x22) += 1;
    level = *(s16 *)(self + 0x22);
    *(u8 *)(self + level * 2 + 0x19) += 1;

    level = *(s16 *)(self + 0x22);
    levelOffset = level * 2;
    levelBytes = self + 0x18;
    handlerPtr = levelBytes + levelOffset;
    sub_080C31E0((s32)self, *(s32 *)(*(u8 **)(self + 0x14) + *(u8 *)handlerPtr * 4));

    *(u16 *)(self + 0x22) -= 1;
}
