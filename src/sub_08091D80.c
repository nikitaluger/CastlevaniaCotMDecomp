/* Update a view/entity from a motion state: abort if its position leaves the
 * current view rectangle, otherwise integrate velocity, refresh its animation
 * and set its scroll coordinates relative to the current camera tile. */
extern void sub_080113A8(void *, void *);
extern void sub_0801165C(void *, void *);
extern s32 sub_0805F9B4(s32, s32);
extern void sub_080C31E0(void *, void *);

extern u8 D_02021E90[];
extern u8 D_02025FF0[];

void sub_08091D80(void *entity)
{
    u8 *animIndexPtr;
    u8 *coordTable;
    void *view;
    u8 *motion;
    void *animTable;
    u8 *velocityPtr;

    view = *(void **)((u8 *)entity + 0x38);
    motion = *(u8 **)((u8 *)entity + 0x3C);
    animTable = (void *)(0x34 + (u32)motion);
    velocityPtr = motion;
    velocityPtr += 0x48;

    if (sub_0805F9B4(*(s32 *)(motion + 8), *(s32 *)(motion + 0xC)) == 1) {
        sub_080C31E0(entity, *(void **)((u8 *)entity + 0x24));
        return;
    }
    sub_0801165C(motion, *(s32 *)(velocityPtr + 4));
    sub_080113A8(view, animTable);

    coordTable = D_02021E90;
    animIndexPtr = D_02025FF0;
    animIndexPtr += 0x18A8;

    {
        u32 coordIdx;
        u8 *baseX;
        u8 *baseY;

        coordIdx = ((u32)*animIndexPtr + 1) * 0x40;
        baseX = coordTable + 0x1278;
        *(u32 *)((u8 *)view + 0x14) = *(u32 *)(motion + 8) - ((*(u32 *)(baseX + coordIdx) + 0x8000) & 0xFFFF0000);

        coordIdx = ((u32)*animIndexPtr + 1) * 0x40;
        baseY = coordTable + 0x127C;
        *(u32 *)((u8 *)view + 0x18) = *(u32 *)(motion + 0xC) - ((*(u32 *)(baseY + coordIdx) + 0xFFFF8000) & 0xFFFF0000);
    }
}
