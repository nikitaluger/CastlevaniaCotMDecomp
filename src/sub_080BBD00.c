void sub_080114DC(void *, void *, s16, s32);
void sub_08013C8C(void *, void *);

/* Attach an effect to its owner: set the flip flags from its own direction
 * fields, play its animation frame, copy the owner's position and update the
 * sprite. */
void sub_080BBD00(void *arg0) {
    u8 *anim = *(u8 **)((u8 *)arg0 + 0x38);
    u8 *motion = *(u8 **)((u8 *)arg0 + 0x3C);
    u8 *animDesc = motion + 0x34;
    u8 *owner = *(u8 **)(*(u8 **)((u8 *)arg0 + 0x28) + 0x3C);

    if (*(u8 *)((u8 *)arg0 + 0x58) != 0) {
        u8 *flags = anim + 0x2A;
        u8 tmp = 0xBF & *flags;
        *flags = tmp;
    } else {
        u8 *flags = anim + 0x2A;
        u8 tmp = 0x40 | *flags;
        *flags = tmp;
    }

    if (*(s8 *)((u8 *)arg0 + 0x54) == -1) {
        u16 tmp = 0xFFEF & *(u16 *)(anim + 2);
        *(u16 *)(anim + 2) = tmp;
    } else {
        u16 tmp = 0x10 | *(u16 *)(anim + 2);
        *(u16 *)(anim + 2) = tmp;
    }

    sub_080114DC(anim, animDesc, *(s16 *)((u8 *)arg0 + 0x4C), 0);
    *(u32 *)(motion + 8) = *(u32 *)(owner + 8);
    *(u32 *)(motion + 0xC) = *(u32 *)(owner + 0xC);
    sub_08013C8C(arg0, anim);
}
