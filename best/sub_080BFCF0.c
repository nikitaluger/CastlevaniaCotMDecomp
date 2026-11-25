struct Ret_BFBEE { s32 a, b, c, d; };
extern struct Ret_BFBEE sub_080BFBEE(s32, void *, u8 *);
void sub_080BFD64(s32 arg0, void *arg1) {
    u8 *p = *(u8 **)((u8 *)arg1 + 0x40);
    u8 v = *p;
    struct Ret_BFBEE r = sub_080BFBEE((s32)((u8 *)0x04000060 + v), arg1, p + 1);
    *(u8 *)r.a = v;
}

struct Ret_BFBEC { s32 a, b, c, d; };
extern struct Ret_BFBEC sub_080BFBEC(void);
void sub_080BFCF0(s32 arg0, void *arg1) {
    struct Ret_BFBEC r = sub_080BFBEC();
    *(u8 *)((u8 *)r.b + 0x14) = (u8)(r.d - 0x40);
    *(u8 *)r.b |= 3;
}
