void sub_08051CA0(void *arg0, void *arg1, void *arg2) {
    u8 *a0 = (u8 *)arg0;
    u8 *a1 = (u8 *)arg1;
    u8 *a2 = (u8 *)arg2;
    u8 *node;
    u8 *next;
    u8 *p;
    u8 *src;
    u32 v8;
    u32 vC;
    u32 t;

    v8 = *(u32 *)(a2 + 0x80);
    *(u32 *)(a1 + 8) = v8;
    vC = *(u32 *)(a2 + 0xA4);
    *(u32 *)(a1 + 0xC) = vC;
    node = *(u8 **)(a0 + 0x30);
    if (node == NULL) return;
    *(u32 *)(node + 0x4C) = *(u32 *)(a2 + 0x58);
    *(u32 *)(node + 0x5C) = *(u32 *)(a2 + 0x5C);
    t = *(u32 *)(node + 0x2C);
    next = (u8 *)t;
    if (t == 0) return;
    src = a2 + 0x60;
    do {
        p = next;
        t = *(u32 *)(p + 0x2C);
        next = (u8 *)t;
        *(u32 *)(p + 0x4C) = *(u32 *)(src);
        do { *(u32 *)(p + 0x5C) = *(u32 *)(src + 0x24);
        src += 4; } while (0);
    } while (t != 0);
}
