void sub_080113A8(void *, void *);
void sub_08012704(u32, u32, u32, s32, void *);
void copyPoseAttrs(u32, void *);
void *sub_0805FAEC(u32, s32);
void sub_080C31E0(s32, s32);

extern u8 gMainWorkspace[];
extern u8 gScriptObjectAffineParams[];

/* Updates an entity's sprite animation and pose, clearing a visibility bit as
 * it animates and spawning the result object once the animation completes. */
void sub_080368E4(void *entity) {
    u8 *entityData = (u8 *)entity;
    u8 *sprite = *(u8 **)(entityData + 0x38);
    u8 *state = *(u8 **)(entityData + 0x3C);
    u8 *anim = state + 0x34;
    u8 *extra = state + 0x48;
    u32 poseIndex = 0;
    s32 animFlags;
    u8 *resultObj;
    u32 kindOffset = 0x1870;

    if (*(u8 *)(entityData + 0x70) == 0 &&
        (*(u8 *)(entityData + (s32)(s16)(*(s16 *)(entityData + 0x22)) * 2 + 0x19) & 1) != 0) {
        s32 flags = *(u8 *)(sprite + 0x2A) & 0xBF;
        *(u8 *)(sprite + 0x2A) = flags;
    } else {
        s32 flags = 0x40 | *(u8 *)(sprite + 0x2A);
        *(u8 *)(sprite + 0x2A) = flags;
    }

    sub_080113A8(sprite, anim);
    animFlags = 2 & *(u8 *)anim;
    if (animFlags != 0) {
        sub_080C31E0((s32)entityData, *(s32 *)(entityData + 0x24));
        return;
    }
    if (*(u8 *)(extra + 0x18) <= 7) {
        sub_08012704(*(u32 *)(extra + 0x0C), *(u32 *)(extra + 0x10),
                     *(u32 *)(extra + 0x14), 0, extra);
        *(u32 *)(extra + 0x0C) = *(u32 *)(extra + 0x04);
        *(u32 *)(extra + 0x10) = *(u32 *)(extra + 0x08);
        *(u8 *)(extra + 0x18) = *(u8 *)(extra + 0x18) + 1;
    }
    switch (*(u16 *)(sprite + 0x28) - 0x27) {
    case 0: poseIndex = 1; break;
    case 1: poseIndex = 2; break;
    case 3: poseIndex = 3; break;
    case 5: poseIndex = 4; break;
    case 6: poseIndex = 5; break;
    case 7: poseIndex = 6; break;
    case 15: poseIndex = 7; break;
    case 22: poseIndex = 8; break;
    case 27: break;
    case 28: poseIndex = 9; break;
    }
    copyPoseAttrs(*(u32 *)(state + 0x28), gScriptObjectAffineParams + poseIndex * 8);
    if (*(u8 *)(extra + 0x18) == 8) {
        *(u8 *)(extra + 0x18) |= 0x80;
        if ((*(u16 *)extra & 1) == 0) {
            if ((*(u16 *)extra & 2) == 0) {
                resultObj = sub_0805FAEC(*(u32 *)((u8 *)gMainWorkspace + kindOffset), 0xE9);
                if (resultObj != NULL) {
                    u8 resultKind;
                    *(u32 *)(resultObj + 0x4C) = *(u32 *)(extra + 0x04);
                    *(u32 *)(resultObj + 0x5C) = *(u32 *)(extra + 0x08);
                    resultKind = *(u8 *)(entityData + 0x6C);
                    *(u8 *)(resultObj + 0x6C) = resultKind;
                    *(u8 *)(resultObj + 0x70) = 1;
                }
            }
        }
    }
}
