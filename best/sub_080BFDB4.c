extern s32 sub_080BFDBE(u8 *);
s32 sub_080BFDB4(u8 *arg0) {
    if (*(u32 *)(arg0 + 0x34) == 0x68736D53)
        return sub_080BFDBE(arg0);
    return (s32)arg0;
}

extern u8 *sub_080BFBEE(s32, void *, u8 *);
void sub_080BFD64(s32 arg0, void *arg1) {
    u8 *p = *(u8 **)((u8 *)arg1 + 0x40);
    u8 v = *p;
    *sub_080BFBEE((s32)((u8 *)0x04000060 + v), arg1, p + 1) = v;
}
