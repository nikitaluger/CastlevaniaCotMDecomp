extern void *sub_0805FAEC(void *, s32);
extern s32 sub_0800583C(s32);
extern void sub_080A5644(s32, s32);
extern void _call_via_r1(void *, void *);
extern u8 D_08101CF4[];
extern u8 D_0866FF6C[];

struct S_02025FF0_1870 { u8 _0x000[0x1870]; u32 v; };
extern struct S_02025FF0_1870 gMainWorkspace;

void sub_080A56A8(s32 param0, s32 param1) {
    void *effect = sub_0805FAEC((void *)gMainWorkspace.v, 0x195);
    if (effect != 0) {
        *(s32 *)((u8 *)effect + 0x4C) = param0;
        *(s32 *)((u8 *)effect + 0x5C) = param1;
    }
}

void sub_080A56D8(void) {
    void *effect = *(void **)((u8 *)(void *)gMainWorkspace.v + 0x30);
    while (effect != 0) {
        if (*(s16 *)effect == 0x195) {
            u16 *flag = *(u16 **)((u8 *)effect + 0x3C);
            *flag |= 1;
        }
        effect = *(void **)((u8 *)effect + 0x2C);
    }
}

void sub_080A5670(s32 index, void *source) {
    u8 *table = (u8 *)D_08101CF4;
    s32 offset = index * 8;
    s32 value = sub_0800583C(0x80 << 11);
    sub_080A5644(
        *(s32 *)((u8 *)source + 8) + *(s32 *)(table + offset) + value,
        *(s32 *)((u8 *)source + 0xC) + *(s32 *)(table + 4 + offset)
    );
}

/* Installs action-script table 0x0866FF6C on the entity, bumps its +0x9C
 * counter, advances the sub-state's step counter and action byte, dispatches
 * that sub-state's handler, then restores the step counter. */
void sub_080A5A8C(void *entity) {
    u8 *self = (u8 *)entity;
    s16 step;

    *(u32 *)(self + 0x9C) = *(u32 *)(self + 0x9C) + 1;
    *(u32 *)(self + 0x14) = (u32)D_0866FF6C;
    *(u16 *)(self + 0x22) = *(u16 *)(self + 0x22) + 1;

    step = *(s16 *)(self + 0x22);
    *(u8 *)(self + step * 2 + 0x19) = *(u8 *)(self + step * 2 + 0x19) + 1;

    step = *(s16 *)(self + 0x22);
    {
        s32 stepOffset = step * 2;
        u8 *commandBytes = self + 0x18;
        _call_via_r1(entity, *(void **)((u8 *)*(void **)(self + 0x14) + *(u8 *)(commandBytes + stepOffset) * 4));
    }

    *(u16 *)(self + 0x22) = *(u16 *)(self + 0x22) - 1;
}
