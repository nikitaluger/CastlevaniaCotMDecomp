extern void sub_08014668(void *);
extern void sub_08011674(void *, s32);
extern void sub_080113A8(void *, void *);
extern void sub_0803C5F4(s32, void *, s32, s32, s32, s32, s32, s32);
extern void sub_08011368(void *, void *, s32, s32);
extern void sub_08014588(s32, s32);
extern void sub_080C31E4(void *, void *, s32);
extern void sub_0803C674(void *, void *, void *);

extern s32 D_08671BB0[];

void sub_0803BF54(void *obj)
{
    void *owner;
    void *work;
    void *r8;
    void *eff;
    owner = *(void **)((u8 *)obj + 0x38);
    work = *(void **)((u8 *)obj + 0x3C);
    r8 = (u8 *)work + 0x34;
    eff = (u8 *)work + 0x48;

    if (*(u16 *)((u8 *)work + 2) & 3) {
        s32 v;
        *(u16 *)((u8 *)work + 2) &= 0xFFFC;
        v = *(s32 *)((u8 *)work + 0x10);
        v = ~v;
        v += 1;
        *(s32 *)((u8 *)work + 0x10) = v;
        sub_08014668(owner);
    }

    sub_08011674(work, 0x240000);
    sub_080113A8(owner, r8);

    if (*(s32 *)((u8 *)work + 0x18) <= *(s16 *)((u8 *)eff + 2)) {
        s32 zero = 0;
        *(u8 *)((u8 *)eff + 4) = 1;
        sub_0803C5F4(4, owner, 0, 1,
            *(s32 *)((u8 *)work + 8),
            *(s32 *)((u8 *)work + 0xC) + 0xFFFF0000,
            0x0C001800,
            0x800);
        sub_08011368(owner, r8, 5, 1);
        sub_08014588(*(s32 *)((u8 *)work + 0x28),
            *(u8 *)((u8 *)eff + 4) * 8 + 0xFFFFF400);
        *(s32 *)((u8 *)work + 0xC) += 0xFFFFF400;
        *(s32 *)((u8 *)work + 0x10) = zero;
        *(u8 *)((u8 *)obj + *(s16 *)((u8 *)obj + 0x22) * 2 + 0x19) = 0;
        sub_080C31E4((u8 *)obj + 0x18, (u8 *)obj + 0x22, D_08671BB0[0]);
    } else {
        sub_0803C674(owner, work, eff);
    }
}
