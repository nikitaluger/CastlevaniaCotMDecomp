void *sub_08000DC4(void **arg0) {
    void *p = *arg0;
    if (p != NULL) {
        *arg0 = *(void **)((u8 *)p + 0xC);
        *(void **)((u8 *)p + 0xC) = NULL;
    }
    return p;
}

void sub_08000DE0(void **arg0, void *arg1) {
    void *p = *arg0;
    if (p != NULL) {
        while (*(void **)((u8 *)p + 0xC) != NULL) {
            p = *(void **)((u8 *)p + 0xC);
        }
        *(void **)((u8 *)p + 0xC) = arg1;
    } else {
        *arg0 = arg1;
    }
}

void *sub_08000DC4();
void sub_08000DE0(void **, void *);
extern u32 D_020223B8;

s32 sub_08000DF8(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    void **head;
    u32 a;
    u32 b;
    void *p;
    head = &D_020223B8;
    a = arg0 & 3;
    b = (arg0 & 0x30000) >> 16;
    p = sub_08000DC4(head);
    if (p == NULL) return -1;
    *(u32 *)p = arg1;
    *(u32 *)((u8 *)p + 4) = arg2;
    *(u32 *)((u8 *)p + 8) = arg3;
    sub_08000DE0((void **)((u8 *)head + 4 + b * 4 + a * 8), p);
    return 0;
}

extern u8 D_02021E90[];

u32 sub_08000D6C(void) {
    u32 sp0;
    u8 *base = D_02021E90;
    u32 h = (u32)&base[0xA5 << 3];
    u32 t = (u32)&base[0x94 << 1];
    u32 n = (u32)&base[0xA3 << 3];
    u32 d = (u32)&base[(0xA3 << 3) + 0x14];
    u32 prev;
    *(u32 *)h = t;
    if (n >= t) {
        prev = 0;
        do {
            *(u32 *)(n + 0xC) = prev;
            prev = n;
            n -= 0x10;
        } while (n >= t);
    }
    sp0 = 0;
    *(u32 *)0x040000D4 = (u32)&sp0;
    *(u32 *)(0x040000D4 + 4) = d;
    *(u32 *)(0x040000D4 + 8) = 0x85000004;
    return *(u32 *)(0x040000D4 + 8);
}
