extern u8 gCameraState[];
extern u8 gMainWorkspace[];

void sub_0804148C(void *arg0)
{
    u8 *self = (u8 *)arg0;
    u8 *anim = *(u8 **)(self + 0x38);
    u8 *work = *(u8 **)(self + 0x3C);
    u32 v;
    s32 idx;
    s32 camword;
    u8 *camPtr;

    v = work[0];
    work[0] = v + 1;
    if (((s32)((v + 1) << 24) >> 24) == 2)
        work[0] = 0;
    idx = (s32)(v << 24) >> 22;

    *(s32 *)(work + 4 + idx) = *(s32 *)(*(u8 **)(self + 0x28) + 0x4C);
    *(s32 *)(work + 0xC + idx) = *(s32 *)(*(u8 **)(self + 0x28) + 0x5C);

    if (*(u8 *)(*(u8 **)(self + 0x28) + 0x70) != 0) {
        if (work[1] & 1) {
            *(u8 *)(anim + 0x2A) |= 0x40;
        } else {
            *(u8 *)(anim + 0x2A) &= 0xBF;
            work[1]++;
        }
        idx = (s8)work[0] * 4;
        camPtr = gCameraState + 0x1278 + (gMainWorkspace[0x18A8] + 1) * 0x40;
        camword = *(s32 *)camPtr;
        *(s32 *)(anim + 0x14) = *(s32 *)(work + 4 + idx) - ((camword + 0x8000) & 0xFFFF0000);
        camPtr = gCameraState + 0x127C + (gMainWorkspace[0x18A8] + 1) * 0x40;
        camword = *(s32 *)camPtr;
        *(s32 *)(anim + 0x18) = *(s32 *)(work + 0xC + idx) - (camword & 0xFFFF8000);
        if (*(u8 *)(*(u8 **)(self + 0x28) + 0x6C) != 0)
            *(u16 *)(anim + 2) |= 0x10;
        else
            *(u16 *)(anim + 2) &= 0xFFEF;
    } else {
        *(u8 *)(anim + 0x2A) &= 0xBF;
    }

    idx = (s8)work[0] * 4;
    *(s32 *)(self + 0x4C) = *(s32 *)(work + 4 + idx);
    *(s32 *)(self + 0x5C) = *(s32 *)(work + 0xC + idx);
    *(u8 *)(self + 0x6C) = *(u8 *)(*(u8 **)(self + 0x28) + 0x6C);
}
