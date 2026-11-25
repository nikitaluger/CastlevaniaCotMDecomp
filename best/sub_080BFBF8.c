extern s32 sub_080BFBD0(s32);

void sub_080BFBF8(void *arg1) {
    void *temp_r2 = *(void **)((u8 *)arg1 + 0x40);
    u32 val = ((((*(u8 *)((u8 *)temp_r2 + 3) << 8) | *(u8 *)((u8 *)temp_r2 + 2)) << 8) | *(u8 *)((u8 *)temp_r2 + 1)) << 8;
    s32 ret = sub_080BFBD0(val);
    *(s32 *)((u8 *)arg1 + 0x40) = ret | *(u8 *)((u8 *)temp_r2 + 0);
}
