extern s32 sub_0805F9B4(s32, s32);
extern void sub_080C31E0(void *, void *);
extern void sub_0801165C(void *, s32);
extern u8 gCameraState[];
extern u8 gMainWorkspace[];
extern u32 D_0866FAC4[];

/* Entity reaction update: set the visibility flag from an off-screen test,
 * dispatch the current script step, and when not hidden copy the entity's
 * position into its work state and convert it to camera-relative coordinates. */
void sub_080952DC(u8 *arg0)
{
    u8 *self;
    u8 *motion;
    u8 *work;
    u8 *entry;
    s32 offscreen;
    u8 *sprite;
    u8 *coords;
    u8 *xCoords;
    u8 *roomByte;
    u32 scriptId;
    u32 originX;
    u32 originY;
    int recordOffset;
    u32 stepOffset;
    u8 *stepBase;
    s32 stepOffset2;
    u16 flags;
    u32 mask8000;
    u16 hidden;
    u32 fracMask;
    u16 *valuePtr;

    self = *(u8 **)(arg0 + 0x38);
    motion = *(u8 **)(arg0 + 0x3C);
    work = motion + 0x48;
    offscreen = sub_0805F9B4(*(s32 *)(motion + 8), *(s32 *)(motion + 0xC));
    if (offscreen == 1) {
        sprite = *(u8 **)(work + 4);
        *(u8 *)(sprite + 1) = 0;
        flags = *(u8 *)(self + 0x2A);
        *(u8 *)(self + 0x2A) = (u8)(flags & 0xBF);
    } else {
        sprite = *(u8 **)(work + 4);
        *(u8 *)(sprite + 1) = 1;
        flags = *(u8 *)(self + 0x2A);
        *(u8 *)(self + 0x2A) = (u8)(flags | 0x40);
    }
    *(u32 *)(arg0 + 0x14) = (u32)D_0866FAC4;
    *(u16 *)(arg0 + 0x22) = *(u16 *)(arg0 + 0x22) + 1;
    stepOffset = (u32)(*(s16 *)(arg0 + 0x22)) * 2;
    entry = (u8 *)(stepOffset + (u32)arg0);
    *(u8 *)(entry + 0x19) = *(u8 *)(entry + 0x19) + 1;
    stepOffset2 = *(s16 *)(arg0 + 0x22) * 2;
    stepBase = arg0;
    stepBase += 0x18;
    scriptId = *(u8 *)((u32)stepBase + (u32)stepOffset2);
    sub_080C31E0(arg0, (void *)*(u32 *)(*(u32 *)(arg0 + 0x14) + scriptId * 4));
    *(u16 *)(arg0 + 0x22) = *(u16 *)(arg0 + 0x22) - 1;
    flags = *(u16 *)(arg0 + 2);
    mask8000 = 0x8000;
    hidden = (u16)(mask8000 & flags);
    if (!hidden) {
        *(u16 *)(*(u8 **)(work + 4) + 4) = *(u16 *)(motion + 0xA);
        valuePtr = (u16 *)(*(u8 **)(work + 4) + 6);
        fracMask = 0xFFFF0000;
        *valuePtr = *(u16 *)(motion + 0xE) + 1;
        *(u32 *)(work + 0x14) = *(u32 *)(motion + 8);
        *(u32 *)(work + 0x18) = *(u32 *)(motion + 0xC);
        *(u16 *)(work + 0x1C) = hidden;
        sub_0801165C(motion, 0);
        coords = gCameraState;
        roomByte = gMainWorkspace;
        roomByte += 0x18A8;
        recordOffset = ((u32)*roomByte + 1) * 0x40;
        xCoords = coords + 0x1278;
        originX = *(u32 *)(xCoords + recordOffset);
        *(u32 *)(self + 0x14) = *(u32 *)(work + 0x14) - ((originX + mask8000) & fracMask);
        recordOffset = ((u32)*roomByte + 1) * 0x40;
        coords += 0x127C;
        originY = *(u32 *)(coords + recordOffset);
        *(u32 *)(self + 0x18) = *(u32 *)(work + 0x18) - ((originY + 0xFFFF8000) & fracMask);
    }
}
