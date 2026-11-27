extern void sub_08011528(s32, void *);
extern void copyPoseAttrs(void *, void *, u32 *);
extern void _call_via_r1(void *, s32);
extern u32 gKind65LinkedLayerAttrs[];

/* Updates the entity's facing from its movement track, maps the resulting
 * direction to one of six pose entries in gKind65LinkedLayerAttrs and copies that pose into
 * the FX object; finally it advances the script step when the track's flag is
 * set.
 */
void sub_080B2F1C(void *self) {
    void *entity;
    s32 poseIndex;
    void *component;
    u8 *track;
    u32 **dirTablePtr;
    u32 *dirTable;
    s32 dirIndex;
    u8 *dirEntryAddr;
    u32 dirDelta;
    s32 fxObj;

    entity = self;
    poseIndex = 0;
    fxObj = *(s32 *)((u8 *)entity + 0x38);
    component = *(void **)((u8 *)entity + 0x3C);
    track = (u8 *)component + 0x34;

    sub_08011528(fxObj, track);

    dirTablePtr = *(u32 ***)((u8 *)track + 8);
    dirIndex = *(s16 *)((u8 *)track + 0x0E) + *(u8 *)((u8 *)track + 1);
    dirTable = *dirTablePtr;
    dirEntryAddr = (u8 *)((u32)dirIndex * 4 + (u32)dirTable) - 4;
    dirDelta = *(u16 *)(dirEntryAddr + 2) - 8;

    switch (dirDelta) {
        case 0: poseIndex = 0; break;
        case 2: poseIndex = 1; break;
        case 5: poseIndex = 2; break;
        case 8: poseIndex = 3; break;
        case 12: poseIndex = 4; break;
        case 14: poseIndex = 5; break;
        default: break;
    }

    copyPoseAttrs(*(void **)((u8 *)component + 0x28), (void *)((u8 *)gKind65LinkedLayerAttrs + (u32)poseIndex * 8), gKind65LinkedLayerAttrs);
    if (*(u8 *)track & 0x02) {
        _call_via_r1(entity, *(s32 *)((u8 *)entity + 0x24));
    }
}
