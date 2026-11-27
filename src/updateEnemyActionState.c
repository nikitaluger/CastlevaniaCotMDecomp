extern u8 gMainWorkspace[];
extern u32 gMainObjTimerCallbacks[];
extern u32 gMenuScriptCallback[];

s32 syncViewPosition(void*, void*);
void resetActionResultState(void*, void*, void*, void*);
void sub_0806AB04(void*, void*, void*, void*);
void setEntityForm(void*, void*, s32);
s32 spawnKind2CEntity(void*, s32, s32, s32);
void playSound(u16);
void sub_080C31E4(void*, void*, u32);
void sub_0806A884(void*, void*);
u16 sub_0806BCD8(void*, void*, void*, void*);
void sub_080C31E8(void*, void*, s32, u32);
void stepDelayTimer(void*, void*);
void sub_0806C6B0(void*, void*, void*, void*);

/* Enemy action-state update: sync the view and run the shared setup helpers,
   then either spawn the attack entity/play its cue or run down the wait timer;
   dispatch the matching script callback and store the resulting action id for
   the next frame. */
void updateEnemyActionState(u8 *enemy) {
    u8 *entity;
    u8 *workBlock;
    u8 *workState;
    u8 *owner;
    u8 *actionPtr;
    s32 syncStatus;
    s32 counter;
    u32 *actionSlot;
    u32 nextAction;
    s32 counterPtr;
    s32 remaining;

    workBlock = *(u8 **)(enemy + 0x6C);
    workState = workBlock + 4;
    owner = *(u8 **)(enemy + 0x38);
    entity = workState;
    syncStatus = syncViewPosition(workState, entity);
    if (syncStatus != 0) {
        goto end;
    }
    resetActionResultState(enemy, owner, entity, entity);
    sub_0806AB04(enemy, owner, entity, entity);
    if (*(u32 *)(workBlock + 0x8C) == 0) {
        if (*(u32 *)(entity + 0x0C) != 0) goto label_714;
    } else {
        goto label_BC;
    }
label_BC:
    setEntityForm(owner, entity, 0x0E);
    {
        u32 blockX = *(u32 *)(workBlock + 0x04);
        u32 entityX = *(u32 *)(entity + 0x04);
        spawnKind2CEntity(enemy, 5, (s32)blockX, (s32)entityX);
    }
    *(u32 *)(entity + 0x08) = 0;
    *(u32 *)(entity + 0x0C) = 0;
    counterPtr = 0x1754;
    counterPtr = counterPtr + (s32)gMainWorkspace;
    counter = *(s32 *)counterPtr;
    if (counter <= 4) {
        *(s32 *)counterPtr = 5;
    }
    playSound(0x68);
    {
        s32 actionIndex = *(s16 *)(enemy + 0x22);
        s32 byteOffset = actionIndex * 2;
        u8 *ptr = (u8 *)byteOffset;
        ptr = (u8 *)((u32)ptr + (u32)enemy);
        *(u8 *)(ptr + 0x19) = 0;
    }
    {
        u32 *callback = gMainObjTimerCallbacks;
        u8 *scriptArgs = enemy + 0x18;
        u8 *scriptIndex = enemy + 0x22;
        sub_080C31E4(scriptArgs, scriptIndex, *callback);
    }
    goto label_73A;

label_714:
    remaining = *(s32 *)(entity + 0x58) - 1;
    *(s32 *)(entity + 0x58) = remaining;
    if (remaining != 0) goto label_73A;
    {
        s32 actionIndex = *(s16 *)(enemy + 0x22);
        s32 byteOffset = actionIndex * 2;
        u8 *ptr = (u8 *)byteOffset;
        ptr = (u8 *)((u32)ptr + (u32)enemy);
        *(u8 *)(ptr + 0x17) = 0;
    }
    {
        u32 *callback = gMenuScriptCallback;
        u8 *scriptArgs = enemy + 0x18;
        u8 *scriptIndex = enemy + 0x22;
        u32 callbackFn = *callback;
        sub_080C31E8(scriptArgs, scriptIndex, 3, callbackFn);
    }

label_73A:
    sub_0806A884(owner, entity);
    nextAction = (u32)sub_0806BCD8(enemy, owner, workState, entity);
    actionSlot = (u32 *)(workState + 0xC4);
    nextAction = (u32)(u16)nextAction;
    *actionSlot = nextAction;
    if (nextAction != 0) {
        s32 actionIndex = *(s16 *)(enemy + 0x22);
        s32 byteOffset = actionIndex * 2;
        u8 *ptr = (u8 *)byteOffset;
        ptr = (u8 *)((u32)ptr + (u32)enemy);
        *(u8 *)(ptr + 0x17) = 0;
        {
            u32 *callback = gMenuScriptCallback;
            u8 *scriptArgs = enemy + 0x18;
            u8 *scriptIndex = enemy + 0x22;
            u32 prevAction = *(u32 *)(workState + 0xC4);
            u32 callbackFn = *callback;
            sub_080C31E8(scriptArgs, scriptIndex, (s32)prevAction, callbackFn);
        }
    }
    {
        u8 *effect = workState + 0x28;
        stepDelayTimer(effect, owner);
    }
    sub_0806C6B0(enemy, owner, workState, entity);

end:
    return;
}
