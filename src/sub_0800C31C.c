extern s32 sub_080C2F20(s8 dividend, s32 divisor); /* BIOS Div: quotient */
extern s32 sub_080C2F24(s8 dividend, s32 divisor); /* BIOS Div: remainder */
extern u16 D_03000830[];

struct S { u8 pad0[2]; u16 flags; u8 pad4[0x26]; u8 highlight; };

/* Highlights the sprite for linked-object kinds 2 and 4 and programs its
 * parameter table plus scroll/offset values from the linked object's state. */
void sub_0800C31C(u8 *arg0) {
    u8 *self = arg0;
    struct S *sprite = *(struct S **)(self + 0x38);
    s8 linkedKind;
    if (*(s8 *)(self + 0x40) != 0 &&
        (((linkedKind = (s8)(*(u8 *)(*(u8 **)(self + 0x28) + 0x4C))) == 2) || (linkedKind == 4))) {
        sprite->flags |= 0x400;
        sprite->highlight |= 0x40;
        D_03000830[2] = 0x3F40;
        D_03000830[3] = 0x808;
    } else {
        sprite->highlight &= 0xBF;
    }
    *(u32 *)((u8 *)sprite + 0x24) = 0x0863E8A4;
    *(u32 *)((u8 *)sprite + 0x14) = sub_080C2F24((s8)(*(u8 *)(*(u8 **)(self + 0x28) + 0x5C)), 9) * 0x180000;
    *(u32 *)((u8 *)sprite + 0x18) = sub_080C2F20((s8)(*(u8 *)(*(u8 **)(self + 0x28) + 0x5C)), 9) * 0x180000;
}
