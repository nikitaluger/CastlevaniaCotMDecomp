s32 sub_0800168C(void *, s32, s32, s32);
void *sub_0800355C(void);
void sub_0806D2D0(void *);
void sub_080C31E4(void *, void *, s32);
void sub_080C31E0(void *, s32);

struct S_02025FF0 {
    u8 _0x000[0x18C2];
    u16 w;
};
extern struct S_02025FF0 D_02025FF0;

extern u32 D_08671BB0[];

void sub_0807F5E0(void *arg0)
{
    u8 *self = (u8 *)arg0;
    void *tmp;

    if (sub_0800168C(arg0, 0, 0x68, 3) == 0)
    {
        sub_080C31E0(arg0, *(s32 *)(self + 0x24));
        return;
    }

    tmp = sub_0800355C();
    if (tmp == 0)
    {
        sub_0806D2D0(arg0);
        return;
    }

    *(void **)(self + 0x38) = tmp;
    *(u32 *)((u8 *)tmp + 0x1C) = 0x80000005;
    {
        u16 w = D_02025FF0.w;
        u32 z = 0;
        *(u16 *)tmp = w;

        {
            s32 idx = *(s16 *)(self + 0x22);
            *(u8 *)(self + idx * 2 + 0x19) = z;
        }
    }

    {
        const u32 *lit = (const u32 *)0x08671BB0;
        void *r4 = self + 0x18;
        sub_080C31E4(r4, self + 0x22, *lit);
        *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) += 1;
        r4 = (u8 *)r4 + *(s16 *)(self + 0x22) * 2;
        sub_080C31E0(arg0, *(u32 *)(*(u32 *)(self + 0x14) + *(u8 *)r4 * 4));
    }
}
