extern s32 sub_0806D450(void *, void *, void *);
extern void sub_08003740(void *, void *);
extern void playSound(s32);
extern void *sub_0806D2A0(s32, s32, s32, s32);
extern void sub_080C31E0(void *, void *);

struct S_02025FF0_8039C {
    u8 _00[0x10];
    u32 field10;
    u8 _14[0x14ED - 0x14];
    u8 field14ED;
    u8 _14EE[0x173A - 0x14EE];
    u8 field173A;
    u8 _173B[0x18C2 - 0x173B];
    u16 field18C2;
};
extern struct S_02025FF0_8039C gMainWorkspace;

void sub_0808039C(void *arg0)
{
    u8 *r6 = (u8 *)arg0;
    u8 *r8 = *(u8 **)(r6 + 0x6C) + 4;
    u8 *r5 = *(u8 **)(r6 + 0x38);
    u8 *r4 = r8;

    if (sub_0806D450(r6, r5, r4) <= 0) {
        *(s32 *)(r4 + 0x10) -= 1;
        *(s32 *)(r5 + 0x14) += 0xFFFF8000;
        *(s32 *)(r5 + 0x18) += 0x10000;

        if (!(*(s32 *)(r4 + 0x10) & 3)) {
            void *t = sub_0806D2A0(*(s32 *)(r6 + 0x28), 0x65, 0x0A, 0x12);
            if (t != NULL) {
                *(s32 *)((u8 *)t + 0x9C) = (*(s32 *)(r4 + 0x10) >> 2) & 0x1F;
            }
        }

        if (*(s32 *)(r4 + 0x10) != 0) {
            goto cont;
        }
    }
    sub_080C31E0(r6, *(void **)(r6 + 0x24));
    return;

cont:
    *(u16 *)(r5 + 0) = gMainWorkspace.field18C2;
    sub_08003740(r8 + 0x1C, r5);

    *(s32 *)(r4 + 0x14) -= 1;
    if (*(s32 *)(r4 + 0x14) == 0) {
        playSound(0xAF << 1);
        *(s32 *)(r4 + 0x14) = 0x1E;
    }

    if (gMainWorkspace.field173A == 0x1C ||
        (gMainWorkspace.field14ED == 0 && gMainWorkspace.field10 != 0)) {
        sub_080C31E0(r6, *(void **)(r6 + 0x24));
    }
}
