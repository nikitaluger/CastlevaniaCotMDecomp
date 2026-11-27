extern void *allocEffectPart(void);
extern void cleanupFailedEffectSpawn(void *);
extern u16 scalePercentSaturate16(u16, s32);
extern void releaseEffectGroup(void);
extern void _call_via_r2(void *, void *, void *);
extern void _call_via_r1(void *, void *);

extern u8 gGameStatus[];
extern u8 gMainWorkspace[];
extern u32 D_080E0110[];
extern u32 D_084748AC;
extern void *gMainObjTimerCallbacks;

/*
 * Creates the render layer for the entity's current pose step, installs
 * releaseEffectGroup as its new update handler, seeds the owner sprite with
 * animation/state data from the global tables, then advances and dispatches
 * the current script step.
 */
void initPoseCompanionSprite(void *arg0)
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
    ((struct PoseCompanionLayer *)(u32)*(vu32 *)(work + 0x3C))->affine0 = POSE_COMPANION_SPRITE_AFFINE_0;
    ((struct PoseCompanionLayer *)(u32)*(vu32 *)(work + 0x3C))->affine1 = POSE_COMPANION_SPRITE_AFFINE_1;
    ((struct PoseCompanionLayer *)(u32)*(vu32 *)(work + 0x3C))->affine2 = 0;
    ((struct PoseCompanionLayer *)(u32)*(vu32 *)(work + 0x3C))->affine3 = 0;

    {
        u16 duration = *(u16 *)(status + 0x2DE);
        s32 cond = *(s16 *)(status + 0x8C);
        s32 percent = POSE_COMPANION_SPRITE_SCALE_100;
        if (cond == 1) percent = POSE_COMPANION_SPRITE_SCALE_ALT;
        ((struct PoseCompanionLayer *)(u32)*(vu32 *)(work + 0x3C))->palette = scalePercentSaturate16(duration, percent);
    }

    {
        struct PoseCompanionLayer *layerPtr = (struct PoseCompanionLayer *)(u32)*(vu32 *)(work + 0x3C);
        layerPtr->sprite = (u32)sprite;
        layerPtr->animSlot = POSE_COMPANION_ANIM_SLOT;
        ((struct PoseCompanionLayer *)(u32)*(vu32 *)(work + 0x3C))->extraFlags = POSE_COMPANION_SPRITE_FLAGS;
    }

    *(void **)(work + 0x18) = *(void **)(mgr + 0x24);
    *(void **)(mgr + 0x24) = (void *)releaseEffectGroup;

    {
        u8 *gs = gMainWorkspace;
        *(u32 *)((u8 *)sprite + 0x24) = (u32)&D_084748AC;
        *(u32 *)((u8 *)sprite + 0x14) = D_080E0110[(*(u32 *)(gs + 0x14F4) & 0x3C) >> 2];
        *(u32 *)((u8 *)sprite + 0x18) = 0xFFE00000;
        *(u32 *)((u8 *)sprite + 0x1C) = 0x80000004;
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
