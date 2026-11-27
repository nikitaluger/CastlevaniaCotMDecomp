/* Per-frame update for a script-driven actor. Bails out when the actor is
 * off-screen with no active step; otherwise ticks the current step's timer,
 * resolves a contact hit, dispatches a callback from SCRIPT_EVENT_CALLBACK_TABLE,
 * advances the script through SCRIPT_OBJECT_STEP_HANDLERS, and runs the shared
 * animation/cleanup helpers. */
#define STEP_OPCODE(obj) (*(u8 *)((u32)(*(s16 *)((u8 *)(obj) + 0x22)) * 2 + (u32)(obj) + 0x1A))
#define STEP_TIMER(obj) (*(u8 *)((u32)(*(s16 *)((u8 *)(obj) + 0x22)) * 2 + (u32)(obj) + 0x1B))
void playSound(s32);
void stepAnimationTrack(void *, void *);
void sub_08011EE8(void *, void *, s32);
s32 sub_08013558(void *, void *, void *);
void spawnContactEffectOnHit(void *, void *);
void updateActorWorldPosition(void *);
s32 updateObjectDisplayState(void *, void *);
void applySpritePaletteVariant(void *, void *);
void syncSpriteToWorldPosition(void *, void *);
s32 checkActorViewBounds(void *, void *);
void uploadPendingSpriteGraphic(void *, void *);
void sub_08053DFC(void *, void *);
s32 _call_via_r1(s32, s32);
void _call_via_r3(void *, void *, u32, u32);

void updateTimedScriptedActor(void *obj) {
    void *sprite;
    void *work;
    void *animTrack;
    u8 *stepState;
    u8 *stepByte;
    u32 *callbackSlot;
    u8 *stepBase;
    u8 opcode;
    u32 stepHandlers;
    s32 handler;
    s32 byteOffset;
    s32 timer;

    sprite = *(void **)((u8 *)obj + 0x38);
    work = *(void **)((u8 *)obj + 0x3C);
    animTrack = (u8 *)work + 0x34;
    stepState = (u8 *)work + 0x48;
    if (checkActorViewBounds(sprite, work) == 1 && STEP_OPCODE(obj) == 0) {
        return;
    }
    applySpritePaletteVariant(obj, sprite);
    if (STEP_OPCODE(obj) != 0) {
        timer = *(u16 *)(stepState + 6) - 1;
        *(u16 *)(stepState + 6) = timer;
        if ((s32)((u32)timer << 16) < 0) {
            *(u16 *)(stepState + 6) = 0;
            if (sub_08013558(sprite, work, *(void **)((u8 *)work + 0x28)) != 0)
                spawnContactEffectOnHit(obj, *(void **)((u8 *)work + 0x28));
        }
    }
    uploadPendingSpriteGraphic(obj, *(void **)((u8 *)work + 0x28));
    if ((*(u16 *)work & 1) && STEP_OPCODE(obj) != 5) {
        updateActorWorldPosition(obj);
        playSound(0x80);
        STEP_TIMER(obj) = 0;
        callbackSlot = (u32 *)SCRIPT_EVENT_CALLBACK_TABLE;
        _call_via_r3((u8 *)obj + 0x18, (u8 *)obj + 0x22, 5, *callbackSlot);
    }
    if (updateObjectDisplayState(sprite, work) == 0 || STEP_OPCODE(obj) == 0) {
        *(u32 *)((u8 *)obj + 0x14) = SCRIPT_OBJECT_STEP_HANDLERS;
        *(u16 *)((u8 *)obj + 0x22) = *(u16 *)((u8 *)obj + 0x22) + 1;
        stepBase = (u8 *)((u32)(*(s16 *)((u8 *)obj + 0x22)) * 2 + (u32)obj);
        *(u8 *)(stepBase + 0x19) = *(u8 *)(stepBase + 0x19) + 1;
        byteOffset = (s32)(s16)(*(s16 *)((u8 *)obj + 0x22)) * 2;
        stepByte = (u8 *)obj;
        stepByte += 0x18;
        stepByte += byteOffset;
        opcode = *stepByte;
        stepHandlers = *(u32 *)((u8 *)obj + 0x14);
        handler = *(s32 *)((u32)(opcode * 4) + stepHandlers);
        _call_via_r1((s32)obj, handler);
        *(u16 *)((u8 *)obj + 0x22) = *(u16 *)((u8 *)obj + 0x22) - 1;
        if (*(u16 *)((u8 *)obj + 2) & 0x8000) {
            return;
        }
        stepAnimationTrack(sprite, animTrack);
        if (STEP_OPCODE(obj) != 0) {
            sub_08011EE8(work, *(void **)stepState, 0);
        }
    }
    sub_08053DFC(sprite, work);
    syncSpriteToWorldPosition(obj, sprite);
}
