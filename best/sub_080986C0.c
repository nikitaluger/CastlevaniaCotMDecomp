extern u8 sub_080988DC(u8 *);

void sub_080986C0(u8 *self) {
    u8 *p27;
    u8 *p28;
    u32 flag;
    u8 r7;
    u8 idx;
    u8 *base;
    int tmp;
    s8 a;
    s8 b;
    s32 x;
    s8 *p29;

    p29 = (s8 *)(self + 0x29);
    a = *(s8 *)(self + 0x35);
    b = *p29;
    x = (s32)a ^ (s32)b;
    flag = (u32)((-x) | x) >> 31;

    p27 = self + 0x27;
    if (*p27 == 2) {
        if (flag) sub_080988DC(self);
        return;
    }
    p28 = self + 0x28;
    tmp = *p28 - 1;
    *p28 = (u8)tmp;
    r7 = (u8)tmp;
    if (r7 != 0) {
        if (flag) sub_080988DC(self);
        return;
    }
    idx = self[0x26];
    base = *(u8 **)(self + 0x20);
    {
        u32 off = idx << 4;
        off += (u32)base;
        if (*(u8 *)off == 0xFF) {
    if (*p27 == 0) {
            if (flag) sub_080988DC(self);
            *p27 = 2;
            return;
        }
        self[0x25] = r7;
    } else {
        self[0x25] = idx;
    }
    }
    *p28 = sub_080988DC(self);
}
