extern u16 D_080CA9F4[];

/* If the object faces left, clear the sprite's 0x40 flag; otherwise set it
 * and point the sprite's graphic at the animation frame's tile data. */
void sub_08008C28(u8 *obj) {
    u8 *sprite;
    u8 *spriteFlags;
    sprite = *(u8 **)(obj + 0x38);
    if (*(s32 *)(*(u8 **)(obj + 0x28) + 0x4C) < 0) {
        spriteFlags = sprite + 0x2A;
        *(u8 *)spriteFlags &= 0xBF;
        return;
    }
    spriteFlags = sprite + 0x2A;
    {
        s32 bit = 0x40 | *(u8 *)spriteFlags;
        *(u8 *)spriteFlags = bit;
    }
    *(u32 *)(sprite + 0x24) = D_080CA9F4[(*(s32 *)(obj + 0x4C) * 2 + *(s32 *)(*(u8 **)(obj + 0x28) + 0x4C) * 4) / 2] * 8 + 0x08639ECC;
}
