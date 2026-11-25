extern s32 sub_0806C4B4(void *, void *);
extern void sub_0806C5EC(void *, void *, void *, void *);
extern void sub_0806AB04(void *, void *, void *, void *);
extern void sub_0806A884(void *, void *);
extern void sub_0806E114(void *, s32, s32, s32);
extern s32 sub_08003740(void *, void *);
extern s32 sub_08065CC8(void *, void *, void *, void *);
extern void sub_080C31E8(void *, void *, s32, s32);
extern void sub_08084CBC(void *, void *);
extern void sub_0806D7B4(void *, s32);
extern s32 sub_0806D2A0(void *, s32, s32, s32);
extern s32 sub_0806BCD8(void *, void *, void *, void *);
extern void sub_0806C6B0(void *, void *, void *, void *);
struct F0 { u8 _0[0x24]; u32 f24; u16 f28; u8 _2A[0x182C-0x2A]; u32 f182C; };
struct S90 { u8 _0[0x146C]; u16 f146C; };
extern struct F0 D_02025FF0;
extern struct S90 D_02021E90;
extern s32 D_08671BD0[];

void sub_080661EC(void *arg0)
{
    void *r9; void *r10; void *r4; void *r8;

    r9 = (void *)((u8 *)*(void **)((u8 *)arg0 + 0x6C) + 4);
    r10 = *(void **)((u8 *)arg0 + 0x38);
    r4 = r9;
    if (sub_0806C4B4(r4, r4) != 0) return;

    sub_0806C5EC(arg0, r10, r4, r4);
    sub_0806AB04(arg0, r10, r4, r4);
    sub_0806A884(r10, r4);

    if (D_02025FF0.f24 != 0) {
        if ((D_02025FF0.f28 & 0xF0) != 0) goto L_do;
        goto L300;
    } else {
        if ((D_02021E90.f146C & 0xF0) == 0) goto L300;
    }

L_do:
    {
        s32 x = *(s32 *)((u8 *)r4 + 0x10);
        s32 low = x & 3;
        *(s32 *)((u8 *)r4 + 0x10) = x + 1;
        if (low == 0)
            sub_0806E114(arg0, 9, *(s32 *)r4, *(s32 *)((u8 *)r4 + 4));
    }

    r8 = (void *)sub_08003740((u8 *)r9 + 0x28, r10);
    if (r8 != 0) goto L300;

    *(u8 *)((u8 *)arg0 + *(s16 *)((u8 *)arg0 + 0x22) * 2 + 0x19) = (u8)(s32)r8;
    {
        u8 *r5 = (u8 *)arg0 + 0x18;
        u8 *r6 = (u8 *)arg0 + 0x22;
        s32 r2 = (u16)sub_08065CC8(arg0, r10, r9, r4);
        sub_080C31E8(r5, r6, r2, *D_08671BD0);
    }
    *(u32 *)((u8 *)r9 + 0x9C) = (u32)r8;
    D_02025FF0.f182C = (u32)r8;
    sub_08084CBC(arg0, r9);

    {
        void *r5 = (void *)((u8 *)r9 + 0xC0);
        s32 v = *(s32 *)r5;
        if (v != 0) {
            sub_0806D7B4(r4, v << 16);
            {
                void *r0 = (void *)sub_0806D2A0(arg0, 0x3C, 0x0A, 0x12);
                if (r0 != 0)
                    *(u16 *)((u8 *)r0 + 0x7C) = 1;
            }
            *(u32 *)r5 = (u32)r8;
        }
    }

L300:
    {
        s32 r0 = sub_0806BCD8(arg0, r10, r9, r4);
        void *r2 = (void *)((u8 *)r9 + 0xC4);
        *(s32 *)r2 = (u16)r0;
        if ((u16)r0 != 0) {
            s32 *tbl;
            *(u8 *)((u8 *)arg0 + *(s16 *)((u8 *)arg0 + 0x22) * 2 + 0x19) = 0;
            tbl = D_08671BD0;
            sub_080C31E8((u8 *)arg0 + 0x18, (u8 *)arg0 + 0x22, *(s32 *)r2, *tbl);
            D_02025FF0.f182C = 0;
            sub_08003740((u8 *)r9 + 0x28, r10);
        }
    }
    sub_0806C6B0(arg0, r10, r9, r4);
}
