extern s16 D_020279F0[];

s32 findKindIndex(s16 arg0) {
    s32 i = 0;
    s32 v = arg0;
    s16 *p = D_020279F0;
    for (; i < 4; i++) {
        if (*p == v) {
            return i;
        }
        p++;
    }
    return -1;
}
