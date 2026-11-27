extern void copyPoseAttrs(void *, void *);

void sub_0803A820(void *arg0)
{
    u8 *self = (u8 *)arg0;
    u8 *sprite = *(u8 **)(self + 0x38);
    u8 *work = *(u8 **)(self + 0x3C);
    u8 *anim = work + 0x48;
    u8 *attached;
    u8 *source;
    u8 *attrPtr;
    u8 zero;
    s32 stateOffset;
    void *posePtr;
    u16 spriteIndex;

    if (*(u32 *)(self + 0x2C) != 0 && *(u8 *)(self + 0x80) != 0) {
        stateOffset = *(s16 *)(self + 0x22) * 2;
        switch (*(u8 *)((u32)stateOffset + (u32)self + 0x19) & 3) {
        case 0:
            *(u16 *)sprite = (*(u16 *)sprite & 0xFFF) | 0xD000;
            break;
        case 1:
            *(u16 *)sprite = (*(u16 *)sprite & 0xFFF) | 0xE000;
            break;
        case 2:
            *(u16 *)sprite = (*(u16 *)sprite & 0xFFF) | 0xC000;
            break;
        case 3:
            *(u16 *)sprite = (*(u16 *)sprite & 0xFFF) | 0xF000;
            break;
        }
    }
copyPos:
    attached = *(u8 **)(self + 0x28);
    source = *(u8 **)(attached + 0x38);
    *(u16 *)sprite = *(u16 *)source;
    source = *(u8 * volatile *)(self + 0x28);
    source = *(u8 * volatile *)(source + 0x38);
    *(u16 *)(sprite + 2) = *(u16 *)(source + 2);

    attrPtr = sprite + 0x2A;
    *attrPtr &= 0xBF;
    *(u8 *)(*(u8 **)(work + 0x28) + 1) = zero;
    *(u8 *)(*(u8 **)anim + 1) = zero;

    switch (*(u16 *)(*(u8 **)(*(u8 **)(self + 0x28) + 0x38) + 0x28)) {
    case 0x1A:
        posePtr = (void *)0x080CF190;
        copyPoseAttrs(*(void **)(work + 0x28), posePtr);
        copyPoseAttrs(*(void **)anim, (u8 *)posePtr + 8);
        spriteIndex = 0x26;
        break;
    case 0x1E:
        posePtr = (void *)0x080CF1A0;
        copyPoseAttrs(*(void **)(work + 0x28), posePtr);
        copyPoseAttrs(*(void **)anim, (u8 *)posePtr + 8);
        spriteIndex = 0x27;
        break;
    case 0x22:
        posePtr = (void *)0x080CF1B0;
        copyPoseAttrs(*(void **)(work + 0x28), posePtr);
        copyPoseAttrs(*(void **)anim, (u8 *)posePtr + 8);
        spriteIndex = 0x28;
        break;
    default:
        *(u8 *)(*(u8 **)(work + 0x28) + 1) = 1;
        *(u8 *)(*(u8 **)anim + 1) = 1;
        return;
    }
    *(u16 *)(sprite + 0x28) = spriteIndex;
    *attrPtr |= 0x40;
}
