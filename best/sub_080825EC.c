extern u8 gMainWorkspace[];

extern s32 sub_0806D450(void *, void *, void *);
extern void *sub_0806D2A0(s32, s32, s32, s32);
extern void sub_08003740(void *, void *);
extern void playSound(s32);
extern void _call_via_r1(void *, void *);

void sub_080825EC(void *arg0) {
    u8 *r6;
    u8 *r8;
    u8 *r5;
    u8 *r4;
    u32 off;
    void *obj;

    r6 = (u8 *)arg0;
    r8 = *(u8 **)(r6 + 0x6C) + 4;
    r5 = *(u8 **)(r6 + 0x38);
    r4 = r8;

    if (sub_0806D450(r6, r5, r4) > 0) {
        _call_via_r1(r6, *(void **)(r6 + 0x24));
        return;
    }

    *(s32 *)(r4 + 0x10) -= 1;
    *(s32 *)(r5 + 0x14) += 0xFFFF0000;
    *(s32 *)(r5 + 0x18) += 0xFFFF0000;

    if ((*(s32 *)(r4 + 0x10) & 3) == 0) {
        obj = sub_0806D2A0(*(s32 *)(r6 + 0x28), 0x71, 0x0A, 0x12);
        if (obj != NULL)
            *(s32 *)((u8 *)obj + 0x9C) = *(s32 *)(r4 + 0x10) >> 2;
    }

    if (*(s32 *)(r4 + 0x10) == 0) {
        _call_via_r1(r6, *(void **)(r6 + 0x24));
        return;
    }

    off = 0x18C2;
    *(u16 *)r5 = *(u16 *)(gMainWorkspace + off);
    sub_08003740(r8 + 0x1C, r5);

    *(s32 *)(r4 + 0x14) -= 1;
    if (*(s32 *)(r4 + 0x14) == 0) {
        playSound(0x161);
        *(s32 *)(r4 + 0x14) = 0x0C;
    }

    off = 0x173A;
    if (*(u8 *)(gMainWorkspace + off) == 0x1C)
        goto call;
    off = 0x14ED;
    if (*(u8 *)(gMainWorkspace + off) != 0)
        return;
    if (*(u32 *)(gMainWorkspace + 0x10) == 0)
        return;
call:
    _call_via_r1(r6, *(void **)(r6 + 0x24));
}
