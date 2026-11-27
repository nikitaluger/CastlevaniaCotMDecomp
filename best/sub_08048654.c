struct S02025FF0_48654 {
    u8 _0[0x174C];
    s32 f174C;
    s32 f1750;
};
extern struct S02025FF0_48654 gMainWorkspace;

s32 sub_08005910(s32, s32);
void advanceMotion(void *, s32);
void setSpriteFlip(void *, s32);
void sub_080146D0(void *, ...);
s32 sub_0801473C(s32, s32);
void sub_08049180(void *, void *, void *, void *);
s32 sub_080C31E0(s32, s32);
void sub_080C31E4(void *, void *, s32);

void sub_08048654(void *arg0)
{
    void *r8;
    void *r6;
    void *sp0;
    void *r7;
    s32 *p;
    s32 v5;
    s32 v1;
    s32 rr;

    r8 = *(void **)((u8 *)arg0 + 0x38);
    r6 = *(void **)((u8 *)arg0 + 0x3C);
    sp0 = (u8 *)r6 + 0x34;
    r7 = (u8 *)r6 + 0x48;
    p = (s32 *)0x08671BFC;

    v5 = gMainWorkspace.f174C + (((sub_080C31E0(*(s32 *)((u8 *)r7 + 0x0C) + 0x4000, *p) >> 8) << 14));
    v1 = gMainWorkspace.f1750 + (((sub_080C31E0(*(s32 *)((u8 *)r7 + 0x0C), *p) >> 8) << 14));
    v1 -= *(s32 *)((u8 *)r6 + 0x0C);
    v5 -= *(s32 *)((u8 *)r6 + 0x08);

    rr = sub_08005910(v1, v5);
    *(s32 *)((u8 *)r7 + 0x08) += sub_0801473C(*(s32 *)((u8 *)r7 + 0x08), rr) << 9;
    *(s32 *)((u8 *)r7 + 0x04) += 0xFFFFF400;

    sub_080146D0(r6);
    advanceMotion(r6, 0);
    setSpriteFlip(r8, *(s32 *)((u8 *)r7 + 0x08));
    sub_08049180(r8, sp0, r6, r7);

    if (*(s32 *)((u8 *)r7 + 0x04) <= 0)
    {
        void **pp;

        *(s32 *)((u8 *)r7 + 0x04) = 0;
        sub_080146D0(r6, *(s32 *)((u8 *)r7 + 0x08), 0);
        *(u8 *)((u8 *)arg0 + *(s16 *)((u8 *)arg0 + 0x22) * 2 + 0x19) = 0;
        pp = (void **)0x08671BB0;
        sub_080C31E4((u8 *)arg0 + 0x18, (u8 *)arg0 + 0x22, *pp);
    }
}
