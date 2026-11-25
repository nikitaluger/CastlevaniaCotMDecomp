void sub_08003740(u8 *, u8 *);
void sub_08003A6C(u8 *, s32, void *);
void sub_0806D588(u8 *, u8 *);
void sub_080C31E4(void *, void *, s32);

extern u8 D_0850643C[];

void sub_0808A1E8(u8 *self) {
    u8 *r4 = (u8 *)*(u32 *)(self + 0x6C);
    u8 *r6 = (u8 *)*(u32 *)(self + 0x38);
    u8 *obj = r4 + 4;
    u8 *base = (u8 *)0x02025FF0;
    s32 *lit;

    if (*(u32 *)(base + 0x14) == 6) {
        u8 *r4b = r4 + 0x20;
        sub_08003A6C(r4b, 0, D_0850643C);
        sub_08003740(r4b, r6);
        *(u32 *)(obj + 0x2C) = 0x40;
        *(u32 *)(base + 0x1C) = 0x10;
        *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = 0;
        lit = (s32 *)0x08671BB0;
        sub_080C31E4(self + 0x18, self + 0x22, *lit);
    }
    sub_0806D588(r6, obj);
}
