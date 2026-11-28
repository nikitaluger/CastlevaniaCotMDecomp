extern u8 gMainWorkspace[];

extern s32 applyAreaSpecialBehavior(void *, void *, void *);
extern void *spawnEntity(void *, s32, s32, s32);
extern void stepDelayTimer(void *, void *);
extern void playSound(s32);
extern void _call_via_r1(void *, void *);

void sub_08082B58(void *arg0)
{
    u8 *r5;
    u8 *r8;
    u8 *r6;
    u8 *r4;
    u32 off;
    void *obj;

    r5 = (u8 *)arg0;
    r8 = *(u8 **)(r5 + 0x6C) + 4;
    r6 = *(u8 **)(r5 + 0x38);
    r4 = r8;

    if (applyAreaSpecialBehavior(r5, r6, r4) > 0) {
        _call_via_r1(r5, *(void **)(r5 + 0x24));
        return;
    }

    *(s32 *)(r4 + 0x10) -= 1;
    *(s32 *)(r6 + 0x18) += 0xFFFF0000;

    if ((*(s32 *)(r4 + 0x10) & 1) == 0) {
        obj = spawnEntity(*(void **)(r5 + 0x28), 0x73, 0x0A, 0x12);
        if (obj != NULL)
            *(s32 *)((u8 *)obj + 0x9C) = *(s32 *)(r4 + 0x10) >> 1;
    }

    if (*(s32 *)(r4 + 0x10) == 0) {
        _call_via_r1(r5, *(void **)(r5 + 0x24));
        return;
    }

    off = 0x18C2;
    *(u16 *)r6 = *(u16 *)(gMainWorkspace + off);
    stepDelayTimer(r8 + 0x1C, r6);

    *(s32 *)(r4 + 0x14) -= 1;
    if (*(s32 *)(r4 + 0x14) == 0) {
        playSound(0x162);
        *(s32 *)(r4 + 0x14) = 0x14;
    }

    off = 0x173A;
    if (*(u8 *)(gMainWorkspace + off) != 0x1C) {
        off = 0x14ED;
        if (*(u8 *)(gMainWorkspace + off) != 0)
            return;
        if (*(u32 *)(gMainWorkspace + 0x10) == 0)
            return;
    }
    _call_via_r1(r5, *(void **)(r5 + 0x24));
}
