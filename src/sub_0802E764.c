extern s32 sub_08011408(s32, void *, s32, s32, s32);
extern s32 getSpriteFacingSign(s32);
extern void *sub_0802EDF4(s32, s32);
extern void sub_080C31E8(void *, void *, s32, void *);
extern void *gScriptStepCallbacks;

/* Drives the entity's offset toward a limit according to its owner's direction,
 * spawning a pair of markers for one pose, then resets the pose and runs a script. */
void sub_0802E764(u8 *entity) {
    s32 ownerRef = *(s32 *)(entity + 0x38);
    u8 *data = *(u8 **)(entity + 0x3C);
    u8 *actionData = data + 0x34;
    s32 offset;
    s32 zero;
    u8 pose;

    *(u32 *)(data + 0x48) = 0x10000;
    pose = *(u8 *)(entity + (*(s16 *)(entity + 0x22)) * 2 + 0x19);
    if ((pose & 7) == 1) {
        sub_0802EDF4(*(s32 *)(data + 0x08) - 4, *(s32 *)(data + 0x0C));
        sub_0802EDF4(*(s32 *)(data + 0x08) + 4, *(s32 *)(data + 0x0C));
    }
    {
        s32 step = *(s32 *)(data + 0x48);
        zero = 0;
        sub_08011408(ownerRef, actionData, 9, step, zero);
    }
    if (getSpriteFacingSign(ownerRef) < 0) {
        offset = *(s32 *)(data + 0x10);
        offset = offset + 0x1800;
        *(s32 *)(data + 0x10) = offset;
        if (offset > 0) {
            *(s32 *)(data + 0x10) = zero;
            *(u8 *)(entity + (*(s16 *)(entity + 0x22)) * 2 + 0x19) = zero;
            { void **scriptTable = &gScriptStepCallbacks;
              sub_080C31E8(entity + 0x18, entity + 0x22, 0, *scriptTable); }
        }
    } else {
        offset = *(s32 *)(data + 0x10);
        offset = offset + (s32)0xFFFFE800;
        *(s32 *)(data + 0x10) = offset;
        if (offset < 0) {
            *(s32 *)(data + 0x10) = zero;
            *(u8 *)(entity + (*(s16 *)(entity + 0x22)) * 2 + 0x19) = zero;
            { void **scriptTable = &gScriptStepCallbacks;
              sub_080C31E8(entity + 0x18, entity + 0x22, 0, *scriptTable); }
        }
    }
}
