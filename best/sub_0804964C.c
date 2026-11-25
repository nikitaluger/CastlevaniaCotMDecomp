extern void sub_080C31E0(void *, s32);

void sub_0804964C(void *arg0)
{
    u8 *self = (u8 *)arg0;
    s16 idx;
    s32 off;
    u8 *base18;

    *(u32 *)(self + 0x14) = 0x0866E3A0;
    *(u16 *)(self + 0x22) += 1;

    idx = *(s16 *)(self + 0x22);
    *(u8 *)(self + idx * 2 + 0x19) += 1;

    idx = *(s16 *)(self + 0x22);
    off = idx * 2;
    base18 = self + 0x18;
    sub_080C31E0(self, *(u32 *)(*(u32 *)(self + 0x14) + *(u8 *)(base18 + off) * 4));

    *(u16 *)(self + 0x22) -= 1;
}

void sub_08049692(void *arg0)
{
    u8 *self = (u8 *)arg0;
    s16 idx;
    s32 off;
    u8 *base18;

    *(u32 *)(self + 0x14) = 0x0866E3B4;
    *(u16 *)(self + 0x22) += 1;

    idx = *(s16 *)(self + 0x22);
    *(u8 *)(self + idx * 2 + 0x19) += 1;

    idx = *(s16 *)(self + 0x22);
    off = idx * 2;
    base18 = self + 0x18;
    sub_080C31E0(self, *(u32 *)(*(u32 *)(self + 0x14) + *(u8 *)(base18 + off) * 4));

    *(u16 *)(self + 0x22) -= 1;
}
