void sub_08009C84(void *arg0) {
    u8 *p38 = *(u8 **)((u8 *)arg0 + 0x38);
    s8 b = *(s8 *)(*(u8 **)((u8 *)arg0 + 0x28) + 0x5C);
    if (b != 1) {
        u8 *p = p38 + 0x2A;
        u8 v = 0xBF & *p;
        *p = v;
    } else {
        u8 *p;
        u8 v;
        s8 b2;
        p = p38 + 0x2A;
        v = 0x40 | *p;
        *p = v;
        b2 = *(s8 *)(*(u8 **)((u8 *)arg0 + 0x28) + 0x60);
        *(void **)(p38 + 0x24) = b2 ? (void *)0x0863664C : (void *)0x0863668C;
    }
}
