extern void *spawnBudgetedEffect(u32, s32);
extern s32 getSpriteFacingSign(void *);
extern void sub_080C31E4(void *, void *, s32);
extern u8 gMainWorkspace[];

void sub_08031774(void *self) {
    u32 kindOffset = 0x1870;
    u8 *sprite;
    u8 *ref;
    u8 *state;
    u8 *timer;
    void *result;
    s32 flag;
    s32 v;
    u32 vel;
    u16 bits;
    u16 kind;
    s32 *lit;

    sprite = *(u8 **)((u8 *)self + 0x38);
    ref = *(u8 **)((u8 *)self + 0xAC);
    state = *(u8 **)((u8 *)self + 0x3C);
    timer = state + 0x48;
    result = spawnBudgetedEffect(*(u32 *)((u8 *)gMainWorkspace + kindOffset), 0xDC);
    if (result != NULL) {
        if (getSpriteFacingSign(sprite) > 0) {
            v = *(s32 *)(state + 8);
            flag = v < 0;
            if (flag) v += 0xFFFF;
            { u16 val = (v >> 16) + 0x14; *(u16 *)((u8 *)result + 0x4C) = val; }
            vel = 0xE0 << 9;
        } else {
            v = *(s32 *)(state + 8);
            flag = v < 0;
            if (flag) v += 0xFFFF;
            { u16 val = (v >> 16) - 0x14; *(u16 *)((u8 *)result + 0x4C) = val; }
            vel = 0xFFFE4000;
        }
        *(u32 *)((u8 *)result + 0x5C) = vel;
        if (2 & *(u16 *)(*(u32 *)(ref + 4) + 6)) {
            v = *(s32 *)(state + 0xC);
            flag = v < 0;
            if (flag) v += 0xFFFF;
            { u16 val = (v >> 16) + 0xC; *(u16 *)((u8 *)result + 0x54) = val; }
        } else {
            v = *(s32 *)(state + 0xC);
            flag = v < 0;
            if (flag) v += 0xFFFF;
            { u16 val = (v >> 16) - 0xC; *(u16 *)((u8 *)result + 0x54) = val; }
        }
        *(u32 *)((u8 *)result + 0x6C) = 0;
        kind = *(u16 *)(state + 0x1C);
        *(u16 *)((u8 *)result + 0x7C) = kind;
    }
    { s32 zero = 0; *(u16 *)(timer + 4) = 0x14; ((u8 *)self)[(*(s16 *)((u8 *)self + 0x22) * 2) + 0x19] = (u8)zero; }
    lit = (s32 *)0x08671BB0;
    sub_080C31E4((u8 *)self + 0x18, (u8 *)self + 0x22, *lit);
}
