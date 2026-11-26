extern s32 allocWorkSlot(void *, s32, s32, s32);
extern void *sub_0805FAEC(void *, u16);
extern s32 sub_080C31E0(void *, s32);
extern s32 sub_0809F330;

/* Allocates a work object for this script step, fills it from the actor's
 * parameters, spawns a child actor linked back to it, and installs the
 * follow-up handler. */
void sub_0809F2A0(void *arg0) {
    void *work;
    u8 *workData;
    u8 *objectIdPtr;
    void *child;
    u16 spriteFlags;
    u16 value;
    allocWorkSlot(arg0, 0, 0x14, 0);
    work = *(void **)((u8 *)arg0 + 0x3C);
    if (work == NULL) {
        sub_080C31E0(arg0, *(s32 *)((u8 *)arg0 + 0x24));
        return;
    }
    workData = (u8 *)work + 8;
    *(void **)((u8 *)work + 4) = workData;
    *(u16 *)((u8 *)work + 8) = *(s32 *)((u8 *)arg0 + 0x4C) >> 16;
    *(u16 *)(workData + 2) = *(s32 *)((u8 *)arg0 + 0x5C) >> 16;
    objectIdPtr = (u8 *)arg0 + 0x6C;
    *(u16 *)(workData + 4) = *(u16 *)objectIdPtr;
    spriteFlags = 0x84 << 6;
    *(u16 *)(workData + 0xA) = spriteFlags;
    *(u16 *)(workData + 6) = 1;
    child = sub_0805FAEC(arg0, *(u16 *)objectIdPtr);
    *(void **)((u8 *)child + 0xAC) = work;
    if (*(u16 *)objectIdPtr == 0xBB) {
        value = *(u16 *)((u8 *)work + 8);
        *(u16 *)((u8 *)child + 0x4C) = value;
        value = *(u16 *)(workData + 2);
        *(u16 *)((u8 *)child + 0x54) = value;
    }
    sub_0805FAEC(child, 0x185);
    *(u16 *)((u8 *)arg0 + 2) |= 0x800;
    *(u16 *)((u8 *)arg0 + 0x22) = 0;
    *(void **)((u8 *)arg0 + 0x14) = &sub_0809F330;
}
