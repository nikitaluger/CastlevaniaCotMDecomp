/* Builds the scripted angle-driven effect: allocate a sprite and its work
 * block, fill the work and render-layer state from the script thread and the
 * shared effect tables, install the per-frame callback, then advance the
 * script to its next command. */
struct GameState { u8 _0[0x18C2]; u16 spriteFlags; };
extern struct GameState gMainWorkspace;
extern struct ScriptedAngleGfxEntry gEffectGfxTable[];
extern u16 gAngleEffectAltLayerAttrs[];
extern u32 gTrigFuncPtr;
extern u32 gScriptStepCallbackTable;

extern void *allocSpriteObject(void);
extern void allocWorkSlot(void *, s32, s32, s32);
extern void installUpdateHandler(void *, void *, void *);
extern s32 findKindIndex(s32);
extern void *allocEffectPart(void);
extern s32 divideInt(s32, s32);
extern s32 sub_080C31E0(s32, u32);
extern void sub_080C31E4(u8 *, u8 *, u32);
extern void updateActorEffectSubObject(void);

void spawnScriptedAngleEffect(u8 *script)
{
    u8 *actor;
    struct ScriptedAngleEffectWork *body;
    u32 *calcFn;
    u16 *initParams;
    s32 entryIndex;
    u8 *scriptPc;
    u8 *scriptState;
    u32 *cmdTable;
    u32 firstCmd;
    u8 *scriptIdx;

    actor = allocSpriteObject();
    if (actor == 0) {
        sub_080C31E0((s32)script, *(u32 *)(script + SCRIPT_ANGLE_CLEANUP_CB));
        return;
    }
    *(u32 *)(script + SCRIPT_ANGLE_SPRITE_PTR) = (u32)actor;
    allocWorkSlot(script, 0, ANGLE_EFFECT_WORK_SLOT, 0);
    if (*(u32 *)(script + SCRIPT_ANGLE_WORK_PTR) == 0) {
        sub_080C31E0((s32)script, *(u32 *)(script + SCRIPT_ANGLE_CLEANUP_CB));
        return;
    }

    *(u32 *)(actor + 0x1C) = SCRIPT_OBJECT_GFX_ID;
    body = (struct ScriptedAngleEffectWork *)*(u32 *)(script + SCRIPT_ANGLE_WORK_PTR);
    installUpdateHandler(script, body, updateActorEffectSubObject);
    body->kind = ANGLE_EFFECT_KIND;
    body->x = *(u32 *)(script + SCRIPT_ANGLE_POS_X);
    body->y = *(u32 *)(script + SCRIPT_ANGLE_POS_Y);

    calcFn = &gTrigFuncPtr;
    body->adjustedX = ((sub_080C31E0(*(s32 *)(script + SCRIPT_ANGLE_VALUE) + ANGLE_SCRIPT_ANGLE_BIAS, *calcFn) >> 8) * 3) << 8;
    body->adjustedY = ((sub_080C31E0(*(s32 *)(script + SCRIPT_ANGLE_VALUE), *calcFn) >> 8) * 3) << 8;

    entryIndex = findKindIndex((s16)body->kind);
    body->gfxIndex = (u16)entryIndex;
    if ((entryIndex << 16) < 0) {
        sub_080C31E0((s32)script, *(u32 *)(script + SCRIPT_ANGLE_CLEANUP_CB));
        return;
    }

    *(u16 *)actor |= gMainWorkspace.spriteFlags;
    *(u32 *)(actor + 0x24) = *(u32 *)(script + SCRIPT_ANGLE_ANIM_PARAM);
    *(u16 *)(actor + 8) = ANGLE_SCRIPT_ANGLE_BIAS - *(u32 *)(script + SCRIPT_ANGLE_VALUE);
    *(u16 *)(actor + 2) |= ANGLE_SCRIPT_ATTR_FLAG;

    initParams = gAngleEffectAltLayerAttrs;
    body->layer = allocEffectPart();
    if (body->layer == 0) {
        sub_080C31E0((s32)script, *(u32 *)(script + SCRIPT_ANGLE_CLEANUP_CB));
        return;
    }

    body->layer->mode = 1;
    body->layer->layer = 8;
    body->layer->priority = 1;
    body->layer->gfxA = gEffectGfxTable[(s16)body->kind].gfxA;
    body->layer->affine0 = initParams[0];
    body->layer->affine1 = initParams[1];
    body->layer->affine2 = initParams[2];
    body->layer->affine3 = initParams[3];
    body->layer->palette = gEffectGfxTable[(s16)body->kind].palette;
    body->layer->sprite = (u32)actor;

    if (*(u8 *)(script + SCRIPT_ANGLE_SCALE_FLAG) != 0)
        body->layer->palette = divideInt((s16)body->layer->palette * 5, 4);

    *(u16 *)(script + 2) |= EFFECT_SPRITE_READY;
    *(u8 *)(script + (s16)*(u16 *)(script + SCRIPT_STEP_INDEX_OFFSET) * 2 + 0x19) = 0;
    cmdTable = &gScriptStepCallbackTable;
    scriptPc = script + SCRIPT_STEP_BASE_OFFSET;
    scriptIdx = script + SCRIPT_STEP_INDEX_OFFSET;
    firstCmd = *cmdTable;
    sub_080C31E4(scriptPc, scriptIdx, firstCmd);
    *(u8 *)(script + (s16)*(u16 *)(script + SCRIPT_STEP_INDEX_OFFSET) * 2 + 0x19) += 1;
    scriptState = scriptPc + (s16)*(u16 *)(script + SCRIPT_STEP_INDEX_OFFSET) * 2;
    sub_080C31E0((s32)script, *(u32 *)(*(u32 *)(script + SCRIPT_STEP_TABLE_OFFSET) + *(u8 *)scriptState * 4));
    return;
}
