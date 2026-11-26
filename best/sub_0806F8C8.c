extern u8 gMainWorkspace[];
extern u8 D_02023130[];
extern u32 D_08472AF0;
extern u32 gMainObjTimerCallback;

extern s32 sub_0806D518(void *, void *, void *);
extern void sub_080719EC(void *, void *, void *);
extern u16 sub_08007DD8(s32, s32);
extern void sub_0806D588(void *, void *);
extern void sub_08003A6C(void *, s32, void *);
extern s32 sub_08003740(void *, void *);
extern void sub_08005E80(s32);
extern void sub_0806D2F8(void *, void *);

void sub_0806F8C8(void *arg0) {
    void *r6 = arg0;
    void *r5 = *(void **)((u8 *)r6 + 0x6C);
    void *r10 = (u8 *)r5 + 4;
    void *r8 = *(void **)((u8 *)r6 + 0x38);
    void *r4 = r10;
    void *r7;
    s32 r1, r0, r2, t, r5c, r0b;
    s32 temp;

    if (sub_0806D518(r6, r8, r4) != 0) {
        return;
    }

    sub_080719EC(r6, r4, r4);
    r1 = *(s32 *)((u8 *)r4 + 0x48);
    r7 = (u8 *)r5 + 0x30;

    if (r1 != 0) {
        temp = *(s32 *)((u8 *)r4 + 0x0C);
        r0 = temp + r1;
        *(s32 *)((u8 *)r4 + 0x0C) = r0;
        if (r0 > 0x80000) {
            *(s32 *)((u8 *)r4 + 0x0C) = 0x80000;
        }
        *(s32 *)((u8 *)r4 + 0x04) += *(s32 *)((u8 *)r4 + 0x0C);
        r7 = (u8 *)r5 + 0x30;

        r0 = sub_08007DD8((gMainWorkspace[0x18A8] << 6) + (s32)D_02023130, *(s32 *)((u8 *)r5 + 0x04));
        if ((r0 << 16) != 0) {
            __repair_rows: {
                *(s32 *)((u8 *)r4 + 0x04) += 0xFFFF0000;
                t = sub_08007DD8((gMainWorkspace[0x18A8] << 6) + (s32)D_02023130, *(s32 *)((u8 *)r4 + 0x00));
            }
if (t != 0) goto __repair_rows;
            *(s32 *)((u8 *)r10 + 0x48) = t;
            *(s32 *)((u8 *)r4 + 0x0C) = t;
        }
    }

    sub_0806D588(r8, r4);

    r5c = *(s32 *)((u8 *)r4 + 0x10) - 1;
    *(s32 *)((u8 *)r4 + 0x10) = r5c;

    if (r5c == 0) {
        sub_08003A6C(r7, 0, (void *)D_08472AF0);
        *(u8 *)((u8 *)r6 + (*(s16 *)((u8 *)r6 + 0x22)) * 2 + 0x19) = (u8)r5c;
        ((void (*)(void *, void *))(*(void **)gMainObjTimerCallback))((u8 *)r6 + 0x18, (u8 *)r6 + 0x22);
    }

    sub_08003740(r7, r8);

    r0b = *(s32 *)((u8 *)r4 + 0x14) - 1;
    *(s32 *)((u8 *)r4 + 0x14) = r0b;

    if (r0b == 0) {
        sub_08005E80(0x96);
        *(s32 *)((u8 *)r4 + 0x14) = 0x0F;
    }

    sub_0806D2F8(r6, r8);
}
