extern void sub_080C31E0(void *a, void *b);
extern void sub_080C31E4(void *a, void *b, s32 c);
extern void sub_080161F0(void *a);
extern void sub_08071FA0(void);
extern void sub_08072018(void *a);
extern void sub_08006120(void);

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
    u8 pad0[0x2FC];
    s16 s2FC;
    u8 pad1[2];
    u32 u300;
};
extern struct S_02025368 gGameStatus;

extern s32 gMainObjTimerCallback[];
extern u32 gLevelExpTable[];

void sub_080718F4(void *arg0)
{
    u8 *p = (u8 *)arg0;
    u8 *r4 = *(u8 **)(p + 0x6C) + 4;

    sub_080161F0(*(void **)(r4 + 0x3C));
    gMainWorkspace.arr1780[*(s32 *)(p + 0xAC)] = 0;
    sub_080C31E0(arg0, *(void **)(r4 + 0x18));
}

void sub_08071E9C(void *arg0)
{
    gMainWorkspace.f1844 |= 0x08000000;
    *(u8 *)((u8 *)arg0 + (*(s16 *)((u8 *)arg0 + 0x22)) * 2 + 0x19) = 0;
    {
        s32 *nv = gMainObjTimerCallback;
        sub_080C31E4((u8 *)arg0 + 0x18, (u8 *)arg0 + 0x22, *nv);
    }
}

void sub_08071EDC(void *arg0)
{
    u32 cur = gGameStatus.u300;
    s16 idx = gGameStatus.s2FC;
    if (cur >= gLevelExpTable[idx - 1])
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

/* Turn on all sound-player slots and start the players that are enabled and
 * not already running (the counterpart of sub_08071FDC, which stops them). */
void sub_08071FA0(void)
{
    gMainWorkspace.f1848 |= 0x55FE0000;
    gMainWorkspace.b18C6 = 1;
    gMainWorkspace.b18C5 = 1;
    sub_08006120();
}
