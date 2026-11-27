/* Per-frame update for one actor: handle off-screen and action-state changes,
 * tick the sub-state timer, run a scripted action from D_0866E6BC, and finish
 * with this family's shared cleanup/animation helpers. */
#define ACTION_STATE(e) (*(u8 *)((u32)(*(s16 *)((u8 *)(e) + 0x22)) * 2 + (u32)(e) + 0x1A))
#define ACTION_FLAG(e) (*(u8 *)((u32)(*(s16 *)((u8 *)(e) + 0x22)) * 2 + (u32)(e) + 0x1B))
void sub_08005E80(s32);
void stepAnimationTrack(void *, void *);
void sub_08011EE8(void *, void *, s32);
s32 sub_08013558(void *, void *, void *);
void spawnContactEffectOnHit(void *, void *);
void updateActorWorldPosition(void *);
s32 updateObjectDisplayState(void *, void *);
void applySpritePaletteVariant(void *, void *);
void sub_08013C8C(void *, void *);
s32 checkActorViewBounds(void *, void *);
void uploadPendingSpriteGraphic(void *, void *);
void sub_08053DFC(void *, void *);
s32 sub_080C31E0(s32, s32);
void sub_080C31E8(void *, void *, u32, u32);

void sub_08053A00(void *entity) {
    void *anim;
    void *actor;
    void *actorTarget;
    u8 *actorEx;
    u8 *frameEntry;
    u32 *actionData;
    u8 *base;
    u8 patternValue;
    u32 actionTable;
    s32 actionFunc;
    s32 frameOffset;
    s32 timerValue;

    anim = *(void **)((u8 *)entity + 0x38);
    actor = *(void **)((u8 *)entity + 0x3C);
    actorTarget = (u8 *)actor + 0x34;
    actorEx = (u8 *)actor + 0x48;
    if (checkActorViewBounds(anim, actor) == 1 && ACTION_STATE(entity) == 0) {
        return;
    }
    applySpritePaletteVariant(entity, anim);
    if (ACTION_STATE(entity) != 0) {
        timerValue = *(u16 *)(actorEx + 6) - 1;
        *(u16 *)(actorEx + 6) = timerValue;
        if ((s32)((u32)timerValue << 16) < 0) {
            *(u16 *)(actorEx + 6) = 0;
            if (sub_08013558(anim, actor, *(void **)((u8 *)actor + 0x28)) != 0)
                spawnContactEffectOnHit(entity, *(void **)((u8 *)actor + 0x28));
        }
    }
    uploadPendingSpriteGraphic(entity, *(void **)((u8 *)actor + 0x28));
    if ((*(u16 *)actor & 1) && ACTION_STATE(entity) != 5) {
        updateActorWorldPosition(entity);
        sub_08005E80(0x80);
        ACTION_FLAG(entity) = 0;
        actionData = (u32 *)0x08671BDC;
        sub_080C31E8((u8 *)entity + 0x18, (u8 *)entity + 0x22, 5, *actionData);
    }
    if (updateObjectDisplayState(anim, actor) == 0 || ACTION_STATE(entity) == 0) {
        *(u32 *)((u8 *)entity + 0x14) = 0x0866E6BC;
        *(u16 *)((u8 *)entity + 0x22) = *(u16 *)((u8 *)entity + 0x22) + 1;
        base = (u8 *)((u32)(*(s16 *)((u8 *)entity + 0x22)) * 2 + (u32)entity);
        *(u8 *)(base + 0x19) = *(u8 *)(base + 0x19) + 1;
        frameOffset = (s32)(s16)(*(s16 *)((u8 *)entity + 0x22)) * 2;
        frameEntry = (u8 *)entity;
        frameEntry += 0x18;
        frameEntry += frameOffset;
        patternValue = *frameEntry;
        actionTable = *(u32 *)((u8 *)entity + 0x14);
        actionFunc = *(s32 *)((u32)(patternValue * 4) + actionTable);
        sub_080C31E0((s32)entity, actionFunc);
        *(u16 *)((u8 *)entity + 0x22) = *(u16 *)((u8 *)entity + 0x22) - 1;
        if (*(u16 *)((u8 *)entity + 2) & 0x8000) {
            return;
        }
        stepAnimationTrack(anim, actorTarget);
        if (ACTION_STATE(entity) != 0) {
            sub_08011EE8(actor, *(void **)actorEx, 0);
        }
    }
    sub_08053DFC(anim, actor);
    sub_08013C8C(entity, anim);
}
