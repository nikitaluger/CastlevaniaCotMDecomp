extern volatile s8 D_020278D0[];

/* Sprite setup: set the 0x40 flag, install the effect table at +0x24, and
 * derive the sprite's horizontal/vertical screen offsets from the global
 * orientation byte. */
void sub_0800FB7C(void *arg0) {
    u8 *sprite = *(u8 **)((u8 *)arg0 + 0x38);
    u8 *flags = sprite + 0x2A;
    u8 flagsValue = 0x40 | *flags;
    *flags = flagsValue;
    *(u32 *)(sprite + 0x24) = 0x0864280C;
    *(u32 *)(sprite + 0x14) = ((D_020278D0[0xF7] & 1) * 7) << 0x14;
    *(u32 *)(sprite + 0x18) = ((s32)(D_020278D0[0xF7] << 24) >> 25) << 0x14;
}
