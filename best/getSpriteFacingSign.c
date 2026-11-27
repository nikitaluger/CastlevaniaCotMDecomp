static s32 getSpriteFacingSign(void *arg0) {
    if (*(u16 *)((u8 *)arg0 + 2) & 0x10)
        return 1;
    return -1;
}
