extern void *allocEffectPart(void);
extern void cleanupFailedEffectSpawn(void *);
extern u16 scalePercentSaturate16(u16, s32);
extern void releaseEffectGroup(void);
extern void _call_via_r2(void *, void *, void *);
extern void _call_via_r1(void *, void *);

extern u8 gGameStatus[];
extern u8 gMainWorkspace[];
extern u32 gPoseCompanionOffsets[];
extern void *gMainObjTimerCallbacks;

/*
 * Creates the render layer for the entity's current pose step, installs
 * releaseEffectGroup as its new update handler, seeds the work state from the
 * scene's coordinates and variant table, then advances and dispatches the
 * current script step.
 */
void spawnPoseCompanionEffect(void *arg0)
{
    u8 *mgr = (u8 *)arg0;
    u8 *work = *(u8 **)(mgr + 0x6C) + 4;
    void *sprite = *(void **)(mgr + 0x38);
    u8 *status = gGameStatus;
    void *layer;

    layer = allocEffectPart();
    *(void **)(work + 0x3C) = layer;
    if (layer == 0) { cleanupFailedEffectSpawn(arg0); return; }

    {
        u8 *gs = gMainWorkspace;
        ((struct PoseCompanionLayer *)layer)->mode = gs[0x1510] & POSE_COMPANION_MODE_MASK;
    }
    ((struct PoseCompanionLayer *)(u32)*(vu32 *)(work + 0x3C))->kind = POSE_COMPANION_KIND;
    ((struct PoseCompanionLayer *)(u32)*(vu32 *)(work + 0x3C))->layer = POSE_COMPANION_LAYER;
    ((struct PoseCompanionLayer *)(u32)*(vu32 *)(work + 0x3C))->gfxIndex = 0;
    ((struct PoseCompanionLayer *)(u32)*(vu32 *)(work + 0x3C))->affine0 = POSE_COMPANION_AFFINE_0;
    ((struct PoseCompanionLayer *)(u32)*(vu32 *)(work + 0x3C))->affine1 = POSE_COMPANION_AFFINE_1;
    ((struct PoseCompanionLayer *)(u32)*(vu32 *)(work + 0x3C))->affine2 = 0;
    ((struct PoseCompanionLayer *)(u32)*(vu32 *)(work + 0x3C))->affine3 = 0;

    {
        u16 duration = *(u16 *)(status + 0x2DE);
        s32 cond = *(s16 *)(status + 0x8C);
        s32 percent = POSE_COMPANION_SCALE_100;
        if (cond == 1) percent = POSE_COMPANION_SCALE_ALT;
        ((struct PoseCompanionLayer *)(u32)*(vu32 *)(work + 0x3C))->palette = scalePercentSaturate16(duration, percent);
    }

    {
        struct PoseCompanionLayer *layerPtr = (struct PoseCompanionLayer *)(u32)*(vu32 *)(work + 0x3C);
        layerPtr->sprite = (u32)sprite;
        layerPtr->animSlot = POSE_COMPANION_ANIM_SLOT;
        ((struct PoseCompanionLayer *)(u32)*(vu32 *)(work + 0x3C))->extraFlags = POSE_COMPANION_FLAGS;
    }

    *(void **)(work + 0x18) = *(void **)(mgr + 0x24);
    *(void **)(mgr + 0x24) = (void *)releaseEffectGroup;

    {
        u8 *gs = gMainWorkspace;
        u32 *pos = (u32 *)(gs + 0x1728);
        *(u32 *)(work + 0x4C) = *pos;
        pos++;
        *(u32 *)(work + 0x50) = *pos + POSE_COMPANION_Y_OFFSET;
        *(u32 *)(work + 0x54) = gPoseCompanionOffsets[(*(s32 *)(mgr + 0x7C) >> POSE_COMPANION_VARIANT_SHIFT) & POSE_COMPANION_VARIANT_MASK];
        *(u16 *)sprite = *(u16 *)(gs + 0x18C2);
    }

    {
        *(u8 *)(mgr + *(s16 *)(mgr + 0x22) * 2 + 0x19) = 0;
        {
            void **spawnFunc = &gMainObjTimerCallbacks;
            u8 *poseBase = mgr + 0x18;
            _call_via_r2(poseBase, mgr + 0x22, *spawnFunc);
            {
                u8 *slot = (u8 *)(*(s16 *)(mgr + 0x22) * 2);
                u8 *poseSlot = poseBase;
                u8 handlerIndex;
                void *handler;
                slot += (u32)mgr;
                slot[0x19]++;
                poseSlot += *(s16 *)(mgr + 0x22) * 2;
                handlerIndex = *poseSlot;
                handler = ((void **)*(void **)(mgr + 0x14))[handlerIndex];
                _call_via_r1(arg0, handler);
            }
        }
    }
}
