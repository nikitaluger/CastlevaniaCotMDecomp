extern void stepAnimationTrack(void *, void *);
extern void setObjectAnimationFrame(s32, void *, u16, u8);
extern void *spawnBudgetedEffect(u32, s32);
extern s32 addFacingOffsetToX(void *, void *, s32);
extern s32 applyFacingSign(void *, s32);
extern void (*gScriptStepCallbacks)(void *, void *, s32);
extern u8 gMainWorkspace[];

struct PoseResultEntry { u32 param; u32 kind; };
extern struct PoseResultEntry gPoseResultParams[];

/* Advance a pose animation. When the track signals completion, reset the
 * earliest pose steps to frame 9 or cancel the script step for later ones.
 * At frame 0x13 spawn a budgeted result effect seeded from the entity's X and
 * the per-pose offset table, then advance the pose step. The tracker at
 * poseState+0xC is marked active only while the sprite is at frame 0xE. */
void updatePoseResultStep(void *entity) {
    u8 *entityBytes = (u8 *)entity;
    u8 *sprite = *(u8 **)(entityBytes + 0x38);
    u8 *state = *(u8 **)(entityBytes + 0x3C);
    u8 *animTrack = state + 0x34;
    u8 *poseState = state + 0x48;
    s32 animFlags;
    u8 *result;
    u32 kindOffset = POSE_WORKSPACE_KIND;
    u8 savedFlag;

    do { stepAnimationTrack(sprite, animTrack); } while (0);
    animFlags = 2 & *(u8 *)animTrack;
    if (animFlags != 0) {
        if (*(u8 *)(poseState + 0x11) <= 2) {
            *(u8 *)(poseState + 0x10) = 0;
            setObjectAnimationFrame((s32)sprite, animTrack, POSE_VARIANT_ANIM_FRAME, 0);
        } else {
            *(u8 *)(entityBytes + (s32)(s16)(*(s16 *)(entityBytes + 0x22)) * 2 + 0x19) = 0;
            gScriptStepCallbacks(entityBytes + 0x18, entityBytes + 0x22, 0);
        }
    }
    savedFlag = *(u8 *)(poseState + 0x10);
    if (savedFlag == 0 && *(u8 *)(poseState + 0x11) <= 2 && *(u16 *)(sprite + 0x28) == POSE_VARIANT_FINAL_FRAME) {
        result = spawnBudgetedEffect(*(u32 *)((u8 *)gMainWorkspace + kindOffset), POSE_VARIANT_RESULT_KIND);
        if (result != NULL) {
            u8 resultKind;
            resultKind = *(u8 *)(entityBytes + 0x4C);
            *(u8 *)(result + 0x4C) = resultKind;
            *(u32 *)(result + 0x5C) = addFacingOffsetToX(state, sprite, POSE_VARIANT_X_OFFSET);
            *(u32 *)(result + 0x6C) = *(u32 *)(state + 0xC) + POSE_VARIANT_Y_BIAS;
            *(u32 *)(result + 0x7C) = applyFacingSign(sprite, gPoseResultParams[*(u8 *)(poseState + 0x11)].param);
            *(u32 *)(result + 0x8C) = gPoseResultParams[*(u8 *)(poseState + 0x11)].kind;
            *(u8 *)(result + 0xA0) = savedFlag;
        }
        *(u8 *)(poseState + 0x11) = *(u8 *)(poseState + 0x11) + 1;
        *(u8 *)(poseState + 0x10) = 1;
    }
    if (*(u16 *)(sprite + 0x28) == POSE_VARIANT_VISIBLE_FRAME) {
        *(u8 *)(*(u8 **)(poseState + 0xC) + 1) = 1;
    } else {
        *(u8 *)(*(u8 **)(poseState + 0xC) + 1) = 0;
    }
}
