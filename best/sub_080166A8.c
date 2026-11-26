void sub_08016B88(void);
s32 sub_08014114(s32, s32, s32, s32, s32, s32);
void *sub_08016AD8(void *);

extern void *D_02020BD4;

struct S_020279D0 {
    u8 _0[4];
    void *unk4;
    void *unk8;
};
extern struct S_020279D0 D_020279D0;

void sub_080166A8(void)
{
    void *r7 = *(void **)&D_02020BD4;
    void *r6;
    s32 r8;

    D_02020BD4 = 0;
    do { r8 = 0;
    sub_08016B88();

    r6 = D_020279D0.unk4;
    while (r6)
    {
        void *r4 = *(void **)r6;
        u8 *r5 = *(u8 **)((u8 *)(*(void **)((u8 *)r4 + 4)) + 0x3C);
        void *p28 = *(void **)(r5 + 0x28);

        if (p28)
        {
            if (!(*(u8 *)((u8 *)p28 + 1) & 4))
                *(u16 *)((u8 *)r4 + 2) |= 4;
            else
                *(u16 *)((u8 *)r4 + 2) &= 0xFFFB;

            p28 = *(void **)(r5 + 0x28);

            if (*(u16 *)(*(u8 **)((u8 *)p28 + 0x10) + 2) & 0x10)
                *(s32 *)((u8 *)r4 + 0xC) = *(s32 *)(r5 + 8) - ((s32)*(s16 *)((u8 *)p28 + 0xA) << 16);
            else
                *(s32 *)((u8 *)r4 + 0xC) = *(s32 *)(r5 + 8) + ((s32)*(s16 *)((u8 *)p28 + 0xA) << 16);

            if (*(u16 *)(*(u8 **)((u8 *)p28 + 0x10) + 2) & 0x20)
                *(s32 *)((u8 *)r4 + 0x10) = *(s32 *)(r5 + 0xC) - ((s32)*(s16 *)((u8 *)p28 + 0xC) << 16);
            else
                *(s32 *)((u8 *)r4 + 0x10) = *(s32 *)(r5 + 0xC) + ((s32)*(s16 *)((u8 *)p28 + 0xC) << 16);
        }
        else
        {
            *(u16 *)((u8 *)r4 + 2) |= 4;
            *(s32 *)((u8 *)r4 + 0xC) = *(s32 *)(r5 + 8);
            *(s32 *)((u8 *)r4 + 0x10) = *(s32 *)(r5 + 0xC);
        }

        if (sub_08014114(*(s32 *)((u8 *)r4 + 0xC), *(s32 *)((u8 *)r4 + 0x10), 0, 0, 0, 0) == 1)
        {
            void *ret;
            *(u16 *)((u8 *)r4 + 2) |= 1;
            ret = sub_08016AD8(r4);
            if (r4 == r7 || r8 == 1)
            {
                if (ret == 0)
                    D_02020BD4 = D_020279D0.unk8;
                else
                    D_02020BD4 = ret;
                r8 = 0;
            }
        }
        else
        {
            if (r4 == r7)
                r8 = 1;
            *(u16 *)((u8 *)r4 + 2) &= 0xFFFE;
        }

        r6 = *(void **)((u8 *)r6 + 4);
    } } while (0);

    if (D_02020BD4 == 0)
        D_02020BD4 = D_020279D0.unk8;
}
