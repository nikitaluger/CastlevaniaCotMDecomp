void updateActorWorldPosition(void*);
/* Per-frame update for one scripted actor: bail out when off-screen, apply the
 * sprite palette variant, resolve contact hits and spawn their effect, dispatch
 * a scripted action from gActorActionCallbacks, and finally place the sprite at
 * the actor's camera-relative Y position. */
#define ACTION_STATE(e) (*(u8 *)((e) + (*(s16 *)((e) + 0x22)) * 2 + 0x1A))
#define ACTION_FLAG(e) (*(u8 *)((e) + (*(s16 *)((e) + 0x22)) * 2 + 0x1B))
extern u8 gCameraState[];
extern u8 gMainWorkspace[];
extern u8 gActorActionCallbacks[];
extern u32 gScriptEventCallbacks[];

s32 checkActorViewBounds(void *, void *);
void applySpritePaletteVariant(void *, void *);
s32 detectActorHit(void *, void *, void *);
void spawnContactEffectOnHit(void *, void *);
void uploadPendingSpriteGraphic(void *, void *);
void playSound(u32);
void _call_via_r3(void *, void *, s32, u32);
s32 updateObjectDisplayState(void *, void *);
void _call_via_r1(void *, s32);
void stepAnimationTrack(void *, void *);
void moveObjectHorizontally(void *, s32, s32);
void syncSpriteToWorldPosition(void *, void *);

void updateActorActionFrame(u8 *entity) {
    u8 *anim;
    u8 *actor;
    u8 *actorTarget;
    u8 *actorEx;
    u8 *stepEntry;
    u8 *cameraCoords;
    u8 *cameraIndex;
    u8 *actionBytes;
    u32 *callback;
    u8 actionId;
    s32 stepOffset;
    u32 screenY;
    u32 coordOffset;
    u32 frameCounter;

    anim = *(u8 **)(entity + 0x38);
    actor = *(u8 **)(entity + 0x3C);
    actorTarget = actor + 0x34;
    actorEx = actor + 0x48;

    if (checkActorViewBounds(anim, actor) == 1) {
        return;
    }

    applySpritePaletteVariant(entity, anim);

    if (detectActorHit(anim, actor, *(void **)(actor + 0x28)) != 0) {
        spawnContactEffectOnHit(entity, *(void **)(actor + 0x28));
        if (((*(u16 *)actor) & 0x0D) == 0) {
            *(u16 *)(actorEx + 0x04) = 0x0A;
        }
    }

    uploadPendingSpriteGraphic(entity, *(void **)(actor + 0x28));

    if ((*(u16 *)actor & 0x01)) {
        if (ACTION_STATE(entity) != 1) {
            updateActorWorldPosition(entity);
            playSound(0x85);
            ACTION_FLAG(entity) = 0;
            callback = gScriptEventCallbacks;
            _call_via_r3(entity + 0x18, entity + 0x22, 1, *callback);
        }
    }

    if (updateObjectDisplayState(anim, actor) == 0) {
        *(u32 *)(entity + 0x14) = (u32)gActorActionCallbacks;
        *(u16 *)(entity + 0x22) = *(u16 *)(entity + 0x22) + 1;
        stepEntry = (u8 *)((u32)(*(s16 *)(entity + 0x22)) * 2 + (u32)entity);
        *(u8 *)(stepEntry + 0x19) = *(u8 *)(stepEntry + 0x19) + 1;
        stepOffset = *(s16 *)(entity + 0x22);
        stepOffset = stepOffset * 2;
        actionBytes = entity;
        actionBytes += 0x18;
        actionId = *(u8 *)((u32)actionBytes + (u32)stepOffset);
        _call_via_r1(entity, *(u32 *)(*(u32 *)(entity + 0x14) + actionId * 4));
        *(u16 *)(entity + 0x22) = *(u16 *)(entity + 0x22) - 1;
        if (!((*(u16 *)(entity + 0x02)) & 0x8000)) {
            stepAnimationTrack(anim, actorTarget);
            moveObjectHorizontally(actor, 0x100000, 0x100000);
        } else {
            return;
        }
    }

    syncSpriteToWorldPosition(entity, anim);

    cameraCoords = gCameraState;
    cameraIndex = gMainWorkspace;
    cameraIndex += 0x18A8;
    frameCounter = *(u8 *)cameraIndex;
    frameCounter = frameCounter + 1;
    coordOffset = frameCounter << 6;
    cameraCoords += 0x127C;
    screenY = *(u32 *)(cameraCoords + coordOffset);
    screenY = screenY + 0xFFFF8000;
    screenY = screenY & 0xFFFF0000;
    screenY = screenY + 0x10000;
    *(u32 *)(anim + 0x18) = *(s32 *)(actor + 0x0C) - screenY;
}
