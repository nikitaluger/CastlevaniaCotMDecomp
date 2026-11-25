s32 sub_080103F0(u8);

void sub_0800B888(void *arg0, void *arg1) {
    u8 one;
    u8 zero;
    u32 i;
    u8 *flag;
    u8 *tmp;
    zero = 0;
    *(u32 *)((u8 *)arg0 + 0x6C) = zero;
    tmp = (u8 *)arg1 + (0xC7 << 3);
    *tmp = zero;
    i = 0;
    flag = tmp;
    one = 1;
    for (; i <= 7; i++) {
        if (sub_080103F0((u8)i) != 0) {
            *flag = one;
            *(u32 *)((u8 *)arg0 + 0x6C) |= (u32)one << i;
        }
    }
}
