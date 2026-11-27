extern s32 sub_080C389C(u8 value, s32 divisor);
extern s32 randomSignedOffset(s32 range);
extern void *sub_08028BAC(s32 x, s32 y, s32 arg2);
extern void setPolarOffset(u8 *out, s32 angle, s32 length);

void sub_08028864(u8 *arg0) {
    u8 *actor = *(u8 **)(arg0 + 0x3C);
    u8 *anglePtr = actor + 0x48;
    u8 flag;
    s32 x, y;
    u16 delta;
    s32 value;

    flag = *(u8 *)(arg0 + *(s16 *)(arg0 + 0x22) * 2 + 0x19);
    if ((sub_080C389C(flag, 10) << 0x18) == 0) {
        s32 range = 0x10000;
        x = *(s32 *)(actor + 8) + (randomSignedOffset(range) << 2);
        y = *(s32 *)(actor + 0xC) + (randomSignedOffset(range) << 2);
        sub_08028BAC(x, y, *(s16 *)(actor + 0x1C));
    }
    if (*(s16 *)(arg0 + 0x64) < 0) {
        s32 value;
        delta = *(u16 *)(arg0 + 0x7C);
        value = (*(s32 *)anglePtr + delta) & 0xFFFF;
        *(s32 *)anglePtr = value;
        if (value > 0x7000) *(s32 *)anglePtr = 0x7000;
    } else {
        s32 value;
        delta = *(u16 *)(arg0 + 0x7C);
        value = (*(s32 *)anglePtr - delta) & 0xFFFF;
        *(s32 *)anglePtr = value;
        if (value < 0xFFF) *(s32 *)anglePtr = 0x1000;
    }
    setPolarOffset(actor, *(s32 *)anglePtr, *(s32 *)(arg0 + 0x6C));
}
