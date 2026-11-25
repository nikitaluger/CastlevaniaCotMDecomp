void sub_080C0270(s32 a, u8 *self)
{
    u8 *buf;
    u16 v;
    u8 *node;
    u32 flags;

    buf = *(u8 **)(self + 0x40);
    v = *buf;
    if (v < 0x80) {
        self[5] = v;
        *(u8 **)(self + 0x40) = buf + 1;
    } else {
        v = self[5];
    }

    node = *(u8 **)(self + 0x20);
    if (!node) goto end;

loop:
    flags = *node;
    if (flags & 0x83) {
        if (!(flags & 0x40)) {
            if (node[0x11] == v) {
                *node = flags | 0x40;
                goto end;
            }
        }
    }
    node = *(u8 **)(node + 0x34);
    if (node) goto loop;

end:
    ;
}
