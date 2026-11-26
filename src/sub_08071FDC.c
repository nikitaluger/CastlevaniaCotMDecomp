extern void sub_080C31E0(void *a, void *b);
extern void sub_080C31E4(void *a, void *b, s32 c);
extern void sub_08001480(void *a, s32 b);
extern void sub_08005E80(s32 a);
extern void sub_0806D930(void *a);
extern void sub_08071FA0(void);
extern void sub_08072018(void *a);
extern void sub_0800617C(void);
extern void sub_08072270(void);

struct S_02025FF0 {
    u8 pad0[0x14EC];
    u8 b14EC;
    u8 pad1[0x1780 - 0x14ED];
    u32 arr1780[0x30];
    u8 pad2[0x1844 - (0x1780 + 0x30*4)];
    u32 f1844;
    u32 f1848;
    u8 pad3[0x18C5 - 0x184C];
    u8 b18C5;
    u8 b18C6;
};
extern struct S_02025FF0 gMainWorkspace;

struct S_02025368 {
    u8 pad0[0x2C4];
    u32 u2C4;
    u8 pad1[0x2FC - 0x2C8];
    s16 s2FC;
    u8 pad2[2];
    u32 u300;
};
extern struct S_02025368 gGameStatus;

extern s32 gMainObjTimerCallback[];
extern u32 gLevelExpTable[];

void sub_08071EDC(void *arg0)
{
    u8 *base = (u8 *)&gGameStatus;
    u32 cur = *(u32 *)(base + 0x300);
    u32 *tbl = gLevelExpTable;
    s16 idx = *(s16 *)(base + 0x2FC);

    if (cur >= tbl[idx - 1])
    {
        sub_08071FA0();
        sub_08072018(arg0);
        *(u8 *)((u8 *)arg0 + (*(s16 *)((u8 *)arg0 + 0x22)) * 2 + 0x19) = 0;
        {
            s32 *nv = gMainObjTimerCallback;
            sub_080C31E4((u8 *)arg0 + 0x18, (u8 *)arg0 + 0x22, *nv);
        }
    }
}

/* Turn off all sound-player slots and stop the running players (the
 * counterpart of sub_08071FA0, which starts them). */
void sub_08071FDC(void)
{
    gMainWorkspace.f1848 &= 0xAA01FFFF;
    gMainWorkspace.b18C6 = 0;
    gMainWorkspace.b18C5 = 0;
    sub_0800617C();
}

void sub_08072018(void *arg0)
{
    gGameStatus.s2FC++;
    sub_0806D930(&gGameStatus.u2C4);
    sub_08005E80(0x74);
    sub_08001480(arg0, 0x2E);
}

void sub_08072140(void *arg0)
{
    u8 *self = (u8 *)arg0;
    u8 *base18;
    s32 *lit;

    *(u32 *)(*(u32 *)(self + 0x6C) + 0x1C) = *(u32 *)(self + 0x24);
    *(u32 *)(self + 0x24) = (u32)sub_08072270;

    *(u8 *)(self + (s16)*(u16 *)(self + 0x22) * 2 + 0x19) = 0;
    lit = gMainObjTimerCallback;
    base18 = self + 0x18;
    sub_080C31E4(base18, self + 0x22, *lit);

    *(u8 *)(self + (s16)*(u16 *)(self + 0x22) * 2 + 0x19) += 1;
    base18 += (s16)*(u16 *)(self + 0x22) * 2;
    sub_080C31E0(self, *(void **)(*(u32 *)(self + 0x14) + *(u8 *)base18 * 4));
}
