void sub_080A0154(void *arg0, void *arg1, void *arg2, s32 arg3)
{
    void *a0 = arg0;
    void *a2 = arg2;
    if (a0 != NULL) {
        s32 v = (*(u16 *)((u8 *)arg1 + 2) & 0x10) ? 1 : -1;
        *(s32 *)((u8 *)a0 + 0x6C) = v;
        *(s32 *)((u8 *)a0 + 0x4C) = *(s32 *)((u8 *)a2 + 8) + (((v << 1) + v) << 0x13);
        *(s32 *)((u8 *)a0 + 0x5C) = *(s32 *)((u8 *)a2 + 0xC) + 0xFFE00000;
        *(u8 *)((u8 *)a0 + 0x7C) = (u8)arg3;
    }
}
