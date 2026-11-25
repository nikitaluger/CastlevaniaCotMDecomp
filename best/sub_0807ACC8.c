extern s32 sub_0806D450(void *a, void *b, void *c);
extern void sub_08003740(void *a, void *b);
extern void sub_0806D588(void *a, void *b);
extern void sub_0806D2F8(void *a, void *b);
extern void sub_080C31E0(void *a, s32 b);
extern void sub_0806E114(s32 a, s32 b, s32 c);
extern void *sub_0806D2A0(s32 a, s32 b, s32 c, s32 d);
extern s32 D_080E4E14[];
struct S_02025FF0 {
    u8 _pad0[0x10];
    s32 unk10;
    u8 _pad14[0x14E2 - 0x14];
    u16 w14E2;
    s32 w14E4;
    u8 _pad14E8[0x14ED - 0x14E8];
    u8 b14ED;
    u8 _pad14EE[0x173A - 0x14EE];
    u8 b173A;
    u8 _pad173B[0x18C2 - 0x173B];
    u16 w18C2;
};
extern struct S_02025FF0 D_02025FF0;

void sub_0807ACC8(u8 *arg0) {
    u8 *r6;
    u8 *r9;
    u8 *r7;
    u8 *r4;
    u16 flag;
    s32 *p;
    s32 i;
    void *obj;
    r6 = *(u8 **)(arg0 + 0x6C);
    r9 = r6 + 4;
    r7 = *(u8 **)(arg0 + 0x38);
    r4 = r9;
    if (sub_0806D450(arg0, r7, r4) <= 0) {
        D_02025FF0.w14E2 = 0x147;
        D_02025FF0.w14E4 = 0x2D;
        *(s32 *)(r6 + 4) = *(s32 *)(r6 + 4) + *(s32 *)(r4 + 8);
        *(s32 *)(r4 + 4) = *(s32 *)(r4 + 4) + *(s32 *)(r4 + 0x0C);
        flag = *(u16 *)(*(u8 **)(r4 + 0x2C) + 0x14);
        if (((flag & 1) != 0) && ((flag & 2) == 0)) {
            sub_0806E114(*(s32 *)(arg0 + 0x28), 0x0B, *(s32 *)(r6 + 4));
            p = D_080E4E14;
            i = 7;
            do {
                obj = sub_0806D2A0(*(s32 *)(arg0 + 0x28), 0x50, 0x0A, 0x12);
                if (obj != NULL) {
                    *(s32 *)((u8 *)obj + 0x7C) = *(s32 *)(r4 + 0);
                    *(s32 *)((u8 *)obj + 0x8C) = *(s32 *)(r4 + 4);
                    *(s32 *)((u8 *)obj + 0x9C) = *p;
                }
                p += 1;
                i -= 1;
            } while (i >= 0);
        } else {
            *(u16 *)r7 = D_02025FF0.w18C2;
            sub_08003740(r9 + 0x1C, r7);
            sub_0806D588(r7, r4);
            if (D_02025FF0.b173A == 0x1C) {
                goto fail;
            }
            if ((D_02025FF0.b14ED != 0) || (D_02025FF0.unk10 == 0)) {
                goto ok;
            }
        }
    }
fail:
    sub_080C31E0(arg0, *(s32 *)(arg0 + 0x24));
    return;
ok:
    sub_0806D2F8(arg0, r7);
}
