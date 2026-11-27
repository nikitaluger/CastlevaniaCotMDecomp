extern void setAnimationFrame(void *, void *, s32, s32);
extern s32 divInt32(s32, s32);
extern s32 sub_080C36E4(s32, s32);
extern void sub_080C31E8(void *, void *, s32, s32);
extern s32 absXFromFocus(s32);
extern s32 absYFromFocus(s32);
extern u8 gMainWorkspace[];

void sub_0803157C(u8 *self) {
    void *parent = *(void **)(self + 0x38);
    void *ref = *(void **)(self + 0xAC);
    u8 *obj = *(u8 **)(self + 0x3C);
    u8 *anim = obj + 0x34;
    u8 *state = obj + 0x48;
    s32 x;
    s32 t;
    s32 kind;
    u8 *slot;
    s32 *callbackTable;

    setAnimationFrame(parent, anim, 0, 0);
    x = *(s32 *)(obj + 8);
    t = x * 9 + *(s32 *)(obj + 0xC);
    if (t < 0) {
        s32 a = (t + 0xFFFF) >> 16;
        s32 q = divInt32(t, 0x280000);
        s32 first = sub_080C36E4(a - q * 30, 0x14A);
        s32 second = sub_080C36E4(*(s32 *)(gMainWorkspace + 0x189C), 0x14A);
        if (second != first) return;
    }
    if (*(s16 *)(state + 8) == 1 ||
        (*(u16 *)(*(void **)((u8 *)ref + 4) + 6) & 2) != 0) {
        *(u16 *)state = 1;
        slot = (u8 *)((u32)(*(s16 *)(self + 0x22)) * 2 + (u32)self);
        *(u8 *)(slot + 0x19) = 0;
        callbackTable = (s32 *)0x08671BD0;
        sub_080C31E8(self + 0x18, self + 0x22, 2, *callbackTable);
        return;
    }
    if (absXFromFocus(x) > 0x600000 || absYFromFocus(*(s32 *)(obj + 0xC)) > 0x400000) {
        kind = *(s16 *)(obj + 0x1C);
        if (kind == 0xD || kind == 0x77) {
            *(u16 *)(state + 6) = 3;
        } else {
            *(u16 *)state = 1;
        }
        slot = (u8 *)((u32)(*(s16 *)(self + 0x22)) * 2 + (u32)self);
        *(u8 *)(slot + 0x19) = 0;
        callbackTable = (s32 *)0x08671BD0;
        sub_080C31E8(self + 0x18, self + 0x22, 2, *callbackTable);
        return;
    }
    kind = *(s16 *)(obj + 0x1C);
    if (kind == 0xD || kind == 0x77) {
        *(u16 *)(state + 6) = 3;
    } else {
        *(u16 *)state = 1;
    }
    slot = (u8 *)((u32)(*(s16 *)(self + 0x22)) * 2 + (u32)self);
    *(u8 *)(slot + 0x19) = 0;
    callbackTable = (s32 *)0x08671BD0;
    sub_080C31E8(self + 0x18, self + 0x22, 1, *callbackTable);
}
