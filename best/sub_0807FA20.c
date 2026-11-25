struct S_02025FF0 {
    u8 _0[0x14ED];
    u8 f14ED;
    u8 _1[0x14F4 - 0x14EE];
    s32 f14F4;
    u8 _2[0x14FC - 0x14F8];
    s32 f14FC;
    s32 f1500;
};
extern struct S_02025FF0 D_02025FF0;
extern void *D_080E47E8;

void sub_08003740(void *, void *);
void *sub_0806D2A0(s32, s32, s32, s32);
s32 sub_0806D35C(void *, void *, void *);
void sub_0806D588(void *, void *);
void sub_0807F588(void *, void *);
void sub_0808DC40(s32, s32, s32);
void sub_080C31E0(void *, s32);

void sub_0807FA20(void *arg0) {
    void *r10 = *(void **)((u8 *)arg0 + 0x6C);
    void *sp0 = (u8 *)r10 + 4;
    void *r8 = *(void **)((u8 *)arg0 + 0x38);
    void *r5 = sp0;
    u8 *r9 = (u8 *)0x02025368;
    s32 r4 = sub_0806D35C(arg0, r8, r5);
    if ((u32)(r4 - 2) <= 1U) {
        sub_0807F588(arg0, r5);
    }
    if (r4 == 0) {
        s32 c = D_02025FF0.f14F4 - 1;
        D_02025FF0.f14F4 = c;
        if (c == 0) {
            sub_0807F588(arg0, r5);
        }
        if (!(D_02025FF0.f14F4 & 7)) {
            void *r6 = sub_0806D2A0(*(s32 *)((u8 *)arg0 + 0x28), 0x63, 0xA, 0x12);
            *(s32 *)(r9 + 0x2CC) -= *(s32 *)((u8 *)D_080E47E8 + 4 +
                ((*(u8 *)(r9 + 0x304) - 1) * 12) +
                ((*(u8 *)(r9 + 0x305) - 1) * 120));
            if (r6 != NULL) {
                *(s32 *)((u8 *)r6 + 0x7C) = *(s32 *)((u8 *)r10 + 4);
                *(s32 *)((u8 *)r6 + 0x8C) = *(s32 *)((u8 *)r5 + 4);
                *(u16 *)((u8 *)r6 + 0x9C) = *(u16 *)((u8 *)r8 + 2);
            }
        }
        sub_08003740((u8 *)sp0 + 0x1C, r8);
        sub_0806D588(r8, r5);
        D_02025FF0.f14FC = *(s32 *)((u8 *)r10 + 4);
        D_02025FF0.f1500 = *(s32 *)((u8 *)r5 + 4);
        if (D_02025FF0.f14ED != 0x8A) {
            sub_0808DC40(*(s32 *)((u8 *)r10 + 4), *(s32 *)((u8 *)r5 + 4), 0);
            sub_080C31E0(arg0, *(s32 *)((u8 *)arg0 + 0x24));
        }
    }
}
