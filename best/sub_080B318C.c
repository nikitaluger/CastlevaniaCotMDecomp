s32 sub_080B318C(void *arg0) {
    void *r1 = *(void **)((u8 *)arg0 + 0x30);
    if (r1 != NULL) {
        do {
            if (*(s16 *)r1 == 0x1BE) return 0;
            r1 = *(void **)((u8 *)r1 + 0x2C);
        } while (r1 != NULL);
    }
    return 1;
}

s32 sub_080B3158(void *arg0) {
    void *r1 = *(void **)((u8 *)arg0 + 0x30);
    if (r1 != NULL) {
        do {
            if (*(s16 *)r1 == 0x1BB) return 0;
            r1 = *(void **)((u8 *)r1 + 0x2C);
        } while (r1 != NULL);
    }
    return 1;
}

extern void sub_080C2E68(void *, void *, u32);

void sub_080B31C8(void) {
    *(s32 *)0x020230EC = 0; /* placeholder? */
    /* use struct for 0x125C offset */
    *(u32 *)((u8 *)0x02021E90 + 0x125C) = 0;
    sub_080C2E68((u8 *)0x02021E90 + 0x12B4, (void *)0x0810294C, 0x40);
}

extern void sub_08097DF8(void *);

void sub_080B31F4(void) {
    volatile u16 sp0;
    vu32 *dma = (vu32 *)0x040000D4;
    sp0 = 0x100;
    dma[0] = (u32)&sp0;
    dma[1] = *(u32 *)((u8 *)0x02021E90 + 0x1334);
    dma[2] = 0x81001000;
    (void)dma[2];
    sub_08097DF8((void *)0x083FF548);
}
