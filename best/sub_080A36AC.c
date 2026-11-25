extern u32 sub_080057F8(void);
extern u32 sub_08005820(u32);
extern void sub_080A5670(s32, void *);
extern void sub_08011528(void *, void *);
extern void sub_08011550(void *, void *, s16, s32, u8);
extern void sub_08011624(void *, void *, s32);

extern u8 D_08101C60[];
extern u8 D_08101C74[];
extern u16 D_08101C78[];
extern u32 D_08671BD0;

void sub_080A36AC(void *arg0) {
    void *r5 = arg0;
    void *r8 = *(void **)((u8 *)r5 + 0x38);
    void *r4 = *(void **)((u8 *)r5 + 0x3C);
    u8 *r7 = (u8 *)r4 + 0x34;
    u8 *r6 = (u8 *)r4 + 0x48;
    s16 idx;
    u8 byte;
    u32 val;
    u32 x;
    u32 off;
    s16 t2;
    u32 v68;
    u32 nv;
    s32 c;
    u32 r64;
    u8 *r2ptr;
    u8 *r2ptr2;
    u8 b;
    u32 tmp;
    u16 t;
    void *fp;
    u8 *tb;
    u32 addr;
    u32 r0v, r1v;
    u32 *r4p;
    volatile u32 *dma;
    u8 *a0, *a1;

    idx = *(s16 *)((u8 *)r5 + 0x22);
    byte = *((u8 *)r5 + idx * 2 + 0x19);
    if (byte <= 0x59) {
        if (r7[0] & 2) {
            val = *(u32 *)(r6 + 0x6C);
            if (val != 0) {
                val--;
                *(u32 *)(r6 + 0x6C) = val;
            } else {
                x = sub_080057F8();
                if ((x & 0x1F) == 0) {
                    sub_080A5670(*(u32 *)((u8 *)r4 + 0x48), r4);
                    *(u32 *)(r6 + 0x6C) = 0x0C;
                }
            }
        }
    }

    idx = *(s16 *)((u8 *)r5 + 0x22);
    byte = *((u8 *)r5 + idx * 2 + 0x19);
    if (byte == 0x5A) {
        tb = D_08101C60;
        off = *(u32 *)(r6 + 0x00);
        addr = off * 4;
        tb = tb + 2;
        addr = addr + (u32)tb;
        t2 = *(s16 *)addr;
        sub_08011550(r8, r7, t2, (s32)0xFFFF0000, 0);
    }

    idx = *(s16 *)((u8 *)r5 + 0x22);
    byte = *((u8 *)r5 + idx * 2 + 0x19);
    if (byte <= 0x59) {
        sub_08011528(r8, r7);
    } else {
        sub_08011624(r8, r7, (s32)0xFFFF0000);
    }

    idx = *(s16 *)((u8 *)r5 + 0x22);
    byte = *((u8 *)r5 + idx * 2 + 0x19);
    if (byte > 0x5A) {
        if (r7[0] & 2) {
            v68 = *(u32 *)(r6 + 0x68);
            if (v68 == 0 || v68 == 2) {
                nv = sub_08005820(2);
                *(u32 *)(r6 + 0x64) = nv;
                *(u32 *)(r6 + 0x68) = 0;
            }
            c = *(u32 *)(r6 + 0x68);
            c = c + 1;
            *(u32 *)(r6 + 0x68) = c;
            r2ptr = D_08101C74;
            r64 = *(u32 *)(r6 + 0x64);
            r1v = r64 * 2;
            r1v -= 1;
            c = c + r1v;
            c = c + (u32)r2ptr;
            b = *(u8 *)c;
            tmp = 0;
            dma = (volatile u32 *)0x040000D4;
            dma[0] = (u32)&tmp;
            dma[1] = (u32)(r6 + 0x0C);
            dma[2] = 0x8500000F;
            (void)dma[2];
            idx = *(s16 *)((u8 *)r5 + 0x22);
            *((u8 *)r5 + idx * 2 + 0x19) = 0;
            r4p = (u32 *)0x08671BD0;
            a0 = (u8 *)r5 + 0x18;
            a1 = (u8 *)r5 + 0x22;
            r2ptr2 = (u8 *)D_08101C78;
            r0v = b;
            r0v = r0v * 2;
            r0v = r0v + (u32)r2ptr2;
            t = *(u16 *)r0v;
            fp = (void *)*r4p;
            ((void (*)(void *, void *, u16))fp)(a0, a1, t);
        }
    }
}
