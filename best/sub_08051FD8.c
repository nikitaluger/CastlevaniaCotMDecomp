extern void sub_080C31E8(void*, void*, u16, void*);

void sub_08051FD8(u8 *self, u8 *cfg) {
    s32 span;
    u32 i;
    s32 step;
    u8 *p;
    u32 off;

    if (*(s8 *)(cfg + 6) > 0) span = *(s8 *)(cfg + 6);
    else if (*(s8 *)(cfg + 6) < 0) span = -*(s8 *)(cfg + 6);
    else span = *(s8 *)(cfg + 6);

    i = 0;
    step = span * 8;
    p = cfg + 0x60;
    off = 0;
    do {
        s32 t6 = *(s8 *)(cfg + 6);
        u32 n = t6 > 0 ? 8 - i : i;
        u8 c = cfg[4];
        u32 v = n * span;
        if (c >= v && c < v + cfg[5] - 1) {
            *(s32 *)p = *(s32 *)p + *(s32 *)(cfg + 0x10 + off);
            *(s32 *)(p + 0x24) = *(s32 *)(p + 0x24) + *(s32 *)(cfg + 0x34 + off);
        } else if (c == v + cfg[5] - 1) {
            *(s32 *)p = *(s32 *)(cfg + 0xB0 + off);
            *(s32 *)(p + 0x24) = *(s32 *)(cfg + 0xD4 + off);
        }
        p += 4;
        off += 4;
        i++;
    } while (i <= 8);

    cfg[4] = cfg[4] + 1;
    if (cfg[4] == step + span + cfg[5]) {
        u8 *q = self + *(s16 *)(self + 0x22) * 2;
        q[0x19] = 0;
        { u32 *fp = (u32 *)0x08671BD0;
          sub_080C31E8(self + 0x18, self + 0x22, *(u16 *)(cfg + 2), (void *)*fp); }
    }
}
