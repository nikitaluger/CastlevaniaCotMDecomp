static s32 sub_08014990(void *arg0) {
    if (*(u16 *)((u8 *)arg0 + 2) & 0x10)
        return 1;
    return -1;
}
