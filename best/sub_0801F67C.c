struct S_02025FF0 { u8 _0[0x174C]; u32 f174C; u8 _1[0x1750-0x1750]; u32 f1750; u8 _2[0x1870-0x1754]; u32 f1870; u8 _3[0x189C-0x1874]; u32 f189C; };
extern struct S_02025FF0 D_02025FF0;
extern u8 D_080CE7AC[];
extern u32 D_080CE7C4[];
extern u32 D_08671BB0[];
extern void sub_08011368(void*, void*, int, int);
extern int spawnBudgetedEffect(int, int);
extern int sub_08014990(void*);

void sub_0801F67C(void *arg0) {
    u8 *r7 = (u8 *)arg0;
    u8 *r10 = *(u8 **)(r7 + 0x38);
    u8 *r4 = *(u8 **)(r7 + 0x3C);
    u8 *p34 = r4 + 0x34;
    u8 *r6 = r4 + 0x48;
    sub_08011368(r10, p34, 5, 0);
    if (*(s16 *)(r6 + 0x28) > 0 || *(s16 *)(r6 + 0x08) > 0) goto blockB;

    {
        u32 *sb = D_08671BB0;
        u8 *r12 = r7 + 0x18;
        u8 *r8 = r7 + 0x22;
        int r6v = 1;
        int r5v = 0;
        u8 *r3p = r4 + 0x58;
        int r2c = 5;
        u32 *pp;
        u16 *qq;
        s16 off;
        void (*fn)(void *, void *);
        do {
            pp = (u32 *)r3p;
            if (*pp != 0) {
                qq = (u16 *)(*pp + 0x5C);
                *qq |= r6v;
                *pp = r5v;
            }
            r3p += 4;
            r2c--;
        } while (r2c >= 0);
        off = *(s16 *)(r7 + 0x22);
        (r7 + off * 2)[0x19] = 0;
        fn = (void (*)(void *, void *))sb[0];
        fn(r12, r8);
        goto end;
    }

blockB:
    {
        s32 val;
        u32 r1v;
        s32 h;
        s16 r1sh;
        int r9v;
        u8 *r8b;
        u32 r0v;
        int r0r;
        int r1r;
        int r5v2;
        u8 *dst;
        u8 *r4b;
        int r0c;
        s32 r3v;
        u8 *r1q;
        u16 storeval;
        u8 *r1fin;
        u8 *r0p4;
        s16 sh3;
        u32 r0sh3;
        u32 r1val3;
        s32 r2fin;
        s32 r1asr;
        s32 r1asr2;
        u32 r0final;
        s32 h28;
        u8 *r1p;
        u8 *r0p;
        s16 sh;
        u32 r0sh;
        u32 r1val;
        u8 *r1p2;
        u8 *r0p3;
        s16 sh2;
        u32 r0sh2;
        u32 r1val2;

        val = D_02025FF0.f189C;
        r1v = (u32)val >> 31;
        val += r1v;
        r1v = val >> 1;
        r1v &= 1;
        if (r1v != 0) {
            *(u32 *)r6 = 0x10000;
        } else {
            *(u32 *)r6 = r1v;
        }
        h = *(u16 *)(r6 + 0x08) - 1;
        *(u16 *)(r6 + 0x08) = h;
        if ((s16)h >= 0) goto end;

        r1sh = *(s16 *)(r6 + 0x28);
        r9v = 6 - r1sh;
        r8b = (u8 *)&D_02025FF0;
        r0v = D_02025FF0.f1870;
        r0r = spawnBudgetedEffect((int)r0v, 0x99);
        r1r = r0r;
        r5v2 = r9v * 4;
        dst = r6 + 0x10 + r5v2;
        r4b = (u8 *)r1r;
        *(u32 *)dst = (u32)r4b;
        if (r4b == 0) goto FE;

        r0c = sub_08014990(r10);
        if (r0c < 0) {
          u16 storeval_1;
            r1p = r8b + 0x174C;
            r0p = (u8 *)(0x080CE7AC + r5v2);
            sh = *(s16 *)r0p;
            r0sh = (u32)sh << 16;/*__repair_loop_weight*/do {
            r1val = *(u32 *)r1p;} while (0);
            r3v = r1val + r0sh;
            r1q = r4b + 0x5C;
            storeval_1 = 0x10;
          *(u16 *)r1q = storeval_1;
        } else {
          u16 storeval_2;
            r1p2 = r8b + 0x174C;
            r0p3 = (u8 *)(0x080CE7AC + r5v2);
            sh2 = *(s16 *)r0p3;
            r0sh2 = (u32)sh2 << 16;
            r1val2 = *(u32 *)r1p2;
            r3v = r1val2 - r0sh2;
            r1q = r4b + 0x5C;
            storeval_2 = 0x20;
          *(u16 *)r1q = storeval_2;
        }
        
        r1fin = r8b + 0x1750;
        r5v2 = r9v * 4;
        r0p4 = (u8 *)(0x080CE7AC + 2 + r5v2);
        sh3 = *(s16 *)r0p4;
        r0sh3 = (u32)sh3 << 16;
        r1val3 = *(u32 *)r1fin;
        r2fin = r1val3 + r0sh3;
        r1asr = (s16)(r3v / 0x10000);
        *(s16 *)(r4b + 0x4C) = r1asr;
        r1asr2 = (s16)(r2fin / 0x10000);
        *(s16 *)(r4b + 0x54) = r1asr2;
        r0final = *(u32 *)(0x080CE7C4 + r5v2);
        *(u32 *)(r4b + 0x6C) = r0final;
        *(u32 *)(r4b + 0x8C) = (u32)r7;

FE:
        *(u16 *)(r6 + 0x08) = 0x0A;
        h28 = *(u16 *)(r6 + 0x28) - 1;
        *(u16 *)(r6 + 0x28) = h28;
        if ((u16)h28 != 0) goto end;
        *(u16 *)(r6 + 0x08) = 0x14;
    }

end:
    return;
}
