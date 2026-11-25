extern void sub_080BFBEC(void);
extern void sub_080BFBFA(void);

void sub_080BFC48(void *arg1) {
    u8 *p;
    u8 v;
    p = *(u8 **)((u8 *)arg1 + 0x40);
    if (*p == 0) {
        *(u8 **)((u8 *)arg1 + 0x40) = p + 1;
        sub_080BFBFA();
        return;
    }
    v = *(u8 *)((u8 *)arg1 + 3) + 1;
    *(u8 *)((u8 *)arg1 + 3) = v;
    sub_080BFBEC();
    if (v < *(u8 *)((u8 *)arg1 + 3)) {
        sub_080BFBFA();
        return;
    }
    *(u8 *)((u8 *)arg1 + 3) = 0;
    *(u8 **)((u8 *)arg1 + 0x40) = p + 5;
}
