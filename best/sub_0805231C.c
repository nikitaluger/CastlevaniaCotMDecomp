void sub_080144D8(void *, void *);
void sub_080144FC(void *, void *);
void sub_080C31E0(void *, void *);
void sub_080113A8(void *, void *);
void sub_08011368(void *, void *, s32, s32);
void sub_080148D8(void *, void *);
void sub_080C31E4(void *, void *, u32);

void sub_08052628(void *arg0) {
    void *r5 = *(void **)((u8 *)arg0 + 0x38);
    sub_080144D8(arg0, r5);
    *(void **)((u8 *)arg0 + 0x14) = (void *)0x0866E65C;
    *(u16 *)((u8 *)arg0 + 0x22) = (u16)(*(u16 *)((u8 *)arg0 + 0x22) + 1);
    {
        u8 *p = (u8 *)((u32)(*(s16 *)((u8 *)arg0 + 0x22)) * 2 + (u32)arg0);
        p[0x19] = (u8)(p[0x19] + 1);
        {
            s32 idx2 = (*(s16 *)((u8 *)arg0 + 0x22)) * 2;
            u8 *base = (u8 *)arg0 + 0x18;
            u8 b = *(base + idx2);
            void **tbl = *(void **)((u8 *)arg0 + 0x14);
            void *arg = tbl[b];
            sub_080C31E0(arg0, arg);
        }
    }
    *(u16 *)((u8 *)arg0 + 0x22) = (u16)(*(u16 *)((u8 *)arg0 + 0x22) - 1);
    sub_080144FC(arg0, r5);
}

void sub_08052680(void *arg0) {
    void *r7;
    void *r6;
    u8 *r4;
    u32 *pp;
    r7 = *(void **)((u8 *)arg0 + 0x38);
    r6 = *(void **)((u8 *)arg0 + 0x3C);
    r4 = (u8 *)r6 + 0x34;
    sub_080113A8(r7, r4);
    if (2 & *r4) {
        sub_08011368(r7, r4, 3, 0);
        *(u8 *)((u8 *)*(void **)((u8 *)r6 + 0x28) + 2) = 8;
        *(u8 *)((u8 *)*(void **)((u8 *)r6 + 0x28) + 3) = 1;
        *(u8 *)((u8 *)((u32)(*(s16 *)((u8 *)arg0 + 0x22)) * 2 + (u32)arg0) + 0x19) = 0;
        pp = (u32 *)0x08671BB0;
        sub_080C31E4((u8 *)arg0 + 0x18, (u8 *)arg0 + 0x22, *pp);
    }
}

void sub_080526DC(void *arg0) {
    void *r5;
    void *r0_3c;
    u8 *r6;
    u32 *pp;
    r5 = *(void **)((u8 *)arg0 + 0x38);
    r0_3c = *(void **)((u8 *)arg0 + 0x3C);
    r6 = (u8 *)r0_3c + 0x34;
    sub_080148D8(r5, *(void **)((u8 *)r0_3c + 8));
    if (*(u8 *)((u8 *)((u32)(*(s16 *)((u8 *)arg0 + 0x22)) * 2 + (u32)arg0) + 0x19) == 0x1E) {
        sub_08011368(r5, r6, 5, 0);
        *(u8 *)((u8 *)arg0 + 0x6C) = 0;
        *(u8 *)((u8 *)arg0 + 0x70) = 0;
        *(u8 *)((u8 *)((u32)(*(s16 *)((u8 *)arg0 + 0x22)) * 2 + (u32)arg0) + 0x19) = 0;
        pp = (u32 *)0x08671BB0;
        sub_080C31E4((u8 *)arg0 + 0x18, (u8 *)arg0 + 0x22, *pp);
    }
}

s16 sub_0805231C(void) { return 0; }
