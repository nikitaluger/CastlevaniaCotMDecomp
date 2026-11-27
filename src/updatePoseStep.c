void stepAnimationTrack(void *, void *);
void resolveTilemapCollision(u32, u32, u32, s32, void *);
void copyPoseAttrs(u32, void *);
void *spawnBudgetedEffect(u32, s32);
void sub_080C31E0(s32, s32);

extern u8 gMainWorkspace[];
extern u8 gScriptObjectAffineParams[];

/* Updates an entity's sprite animation and pose, clearing a visibility bit as
 * it animates and spawning the result object once the animation completes. */
void updatePoseStep(void *entity) {
    u8 *entityBytes = (u8 *)entity;
    u8 *sprite = *(u8 **)(entityBytes + 0x38);
    u8 *state = *(u8 **)(entityBytes + 0x3C);
    u8 *animTrack = state + 0x34;
    u8 *poseState = state + 0x48;
    u32 poseIndex = 0;
    s32 animFlags;
    u8 *result;
    u32 kindOffset = POSE_WORKSPACE_KIND;

    if (*(u8 *)(entityBytes + 0x70) == 0 &&
        (*(u8 *)(entityBytes + (s32)(s16)(*(s16 *)(entityBytes + 0x22)) * 2 + 0x19) & 1) != 0) {
        s32 spriteFlags = *(u8 *)(sprite + 0x2A) & 0xBF;
        *(u8 *)(sprite + 0x2A) = spriteFlags;
    } else {
        s32 spriteFlags = 0x40 | *(u8 *)(sprite + 0x2A);
        *(u8 *)(sprite + 0x2A) = spriteFlags;
    }

    stepAnimationTrack(sprite, animTrack);
    animFlags = 2 & *(u8 *)animTrack;
    if (animFlags != 0) {
        sub_080C31E0((s32)entityBytes, *(s32 *)(entityBytes + 0x24));
        return;
    }
    if (*(u8 *)(poseState + 0x18) <= 7) {
        resolveTilemapCollision(*(u32 *)(poseState + 0x0C), *(u32 *)(poseState + 0x10),
                     *(u32 *)(poseState + 0x14), 0, poseState);
        *(u32 *)(poseState + 0x0C) = *(u32 *)(poseState + 0x04);
        *(u32 *)(poseState + 0x10) = *(u32 *)(poseState + 0x08);
        *(u8 *)(poseState + 0x18) = *(u8 *)(poseState + 0x18) + 1;
    }
    switch (*(u16 *)(sprite + 0x28) - POSE_ANIM_BASE) {
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
    if (*(u8 *)(poseState + 0x18) == POSE_FINAL_STEP) {
        *(u8 *)(poseState + 0x18) |= 0x80;
        if ((*(u16 *)poseState & 1) == 0) {
            if ((*(u16 *)poseState & 2) == 0) {
                result = spawnBudgetedEffect(*(u32 *)((u8 *)gMainWorkspace + kindOffset), POSE_RESULT_KIND);
                if (result != NULL) {
                    u8 resultKind;
                    *(u32 *)(result + 0x4C) = *(u32 *)(poseState + 0x04);
                    *(u32 *)(result + 0x5C) = *(u32 *)(poseState + 0x08);
                    resultKind = *(u8 *)(entityBytes + 0x6C);
                    *(u8 *)(result + 0x6C) = resultKind;
                    *(u8 *)(result + 0x70) = 1;
                }
            }
        }
    }
}
