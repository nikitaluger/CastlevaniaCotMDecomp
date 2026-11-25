extern s8 D_020278D0[];

/* Sprite setup: set the 0x40 flag, install the effect table at +0x24, and
 * derive two fixed-point parameters from the global state bytes. */
void sub_0800FC38(void *arg0) {
    u8 *sprite = *(u8 **)((u8 *)arg0 + 0x38);
    u8 *flags = sprite + 0x2A;
    s32 param;
    u8 flagsValue = 0x40 | *flags;
    *flags = flagsValue;
    *(u32 *)(sprite + 0x24) = 0x08642884;
    *(s32 *)(sprite + 0x14) = ((s32)D_020278D0[0xFA] - 1) << 0x14;
    param = D_020278D0[0xF9];
    *(s32 *)(sprite + 0x18) = (param * 5) << 0x13;
}
