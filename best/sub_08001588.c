extern u32 D_02025B74;

void *sub_08001588(s32 arg0, s32 arg1, s32 arg2) {
    s32 b = arg1 & 0x3FFF;
    s32 a = arg0 & 0x3FFF;
    u16 *p = (u16 *)((u32)arg2 + 0xBC);
    u32 end = D_02025B74;
    while ((u32)p < end) {
        s32 v = *p & 0x3FFF;
        if (a > v) { p = (u16 *)((u32)p + 0xBC); continue; }
        if (v > b) { p = (u16 *)((u32)p + 0xBC); continue; }
        return (void *)p;
    }
    return 0;
}
