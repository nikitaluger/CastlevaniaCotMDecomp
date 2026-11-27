extern void stepAnimationTrack(void *, void *);
extern void setObjectAnimationFrame(s32, void *, u16, u8);
extern void *spawnBudgetedEffect(u32, s32);
extern s32 sub_080148C0(void *, void *, s32);
extern s32 sub_080148AC(void *, s32);
extern void (*gScriptStepCallbacks)(void *, void *, s32);
extern u8 gMainWorkspace[];

struct PoseResultEntry { u32 param; u32 kind; };
extern struct PoseResultEntry D_080CF07C[];

/* Pose-step updater variant: advance the pose animation, optionally reset the
 * step state, and spawn the result object when the sprite reaches step 0x13. */
void sub_08038438(void *entity) {
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
            setObjectAnimationFrame((s32)sprite, animTrack, 9, 0);
        } else {
            *(u8 *)(entityBytes + (s32)(s16)(*(s16 *)(entityBytes + 0x22)) * 2 + 0x19) = 0;
            gScriptStepCallbacks(entityBytes + 0x18, entityBytes + 0x22, 0);
        }
    }
    savedFlag = *(u8 *)(poseState + 0x10);
    if (savedFlag == 0 && *(u8 *)(poseState + 0x11) <= 2 && *(u16 *)(sprite + 0x28) == 0x13) {
        result = spawnBudgetedEffect(*(u32 *)((u8 *)gMainWorkspace + kindOffset), 0xEE);
        if (result != NULL) {
            u8 resultKind;
            resultKind = *(u8 *)(entityBytes + 0x4C);
            *(u8 *)(result + 0x4C) = resultKind;
            *(u32 *)(result + 0x5C) = sub_080148C0(state, sprite, -0xC0000);
            *(u32 *)(result + 0x6C) = *(u32 *)(state + 0xC) + 0xFFD70000;
            *(u32 *)(result + 0x7C) = sub_080148AC(sprite, D_080CF07C[*(u8 *)(poseState + 0x11)].param);
            *(u32 *)(result + 0x8C) = D_080CF07C[*(u8 *)(poseState + 0x11)].kind;
            *(u8 *)(result + 0xA0) = savedFlag;
        }
        *(u8 *)(poseState + 0x11) = *(u8 *)(poseState + 0x11) + 1;
        *(u8 *)(poseState + 0x10) = 1;
    }
    if (*(u16 *)(sprite + 0x28) == 0xE) {
        *(u8 *)(*(u8 **)(poseState + 0xC) + 1) = 1;
    } else {
        *(u8 *)(*(u8 **)(poseState + 0xC) + 1) = 0;
    }
}
