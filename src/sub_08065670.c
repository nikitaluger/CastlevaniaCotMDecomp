extern u8 gMainWorkspace[];
extern u32 gMainObjTimerCallbacks[];
extern u32 gMenuScriptCallback[];

s32 syncViewPosition(void*, void*);
void resetActionResultState(void*, void*, void*, void*);
void sub_0806AB04(void*, void*, void*, void*);
void sub_0806A7AC(void*, void*, s32);
s32 spawnKind2CEntity(void*, s32, s32, s32);
s32 sub_08005E80(s32);
void sub_080C31E4(void*, void*, u32);
void sub_0806A884(void*, void*);
u16 sub_0806BCD8(void*, void*, void*, void*);
void sub_080C31E8(void*, void*, s32, u32);
void stepDelayTimer(void*, void*);
void sub_0806C6B0(void*, void*, void*, void*);

/* Enemy state-machine tick: run the shared animation/movement helpers, pick a
   script branch from the state flags, dispatch the matching indirect callback,
   and store the resulting action id back into the state block. */
void sub_08065670(u8 *self) {
    u8 *body;
    u8 *sceneState;
    u8 *state;
    u8 *sprite;
    u8 *actionPtr;
    s32 checkResult;
    s32 playerCounter;
    u32 *actionPtrOut;
    u32 actionId;
    s32 counterAddr;
    s32 timeLeft;

    sceneState = *(u8 **)(self + 0x6C);
    state = sceneState + 4;
    sprite = *(u8 **)(self + 0x38);
    body = state;
    checkResult = syncViewPosition(state, body);
    if (checkResult != 0) {
        goto end;
    }
    resetActionResultState(self, sprite, body, body);
    sub_0806AB04(self, sprite, body, body);
    if (*(u32 *)(sceneState + 0x8C) == 0) {
        if (*(u32 *)(body + 0x0C) != 0) goto label_714;
    } else {
        goto label_BC;
    }
label_BC:
    sub_0806A7AC(sprite, body, 0x0E);
    {
        u32 stateX = *(u32 *)(sceneState + 0x04);
        u32 bodyX = *(u32 *)(body + 0x04);
        spawnKind2CEntity(self, 5, (s32)stateX, (s32)bodyX);
    }
    *(u32 *)(body + 0x08) = 0;
    *(u32 *)(body + 0x0C) = 0;
    counterAddr = 0x1754;
    counterAddr = counterAddr + (s32)gMainWorkspace;
    playerCounter = *(s32 *)counterAddr;
    if (playerCounter <= 4) {
        *(s32 *)counterAddr = 5;
    }
    sub_08005E80(0x68);
    {
        s32 actionIndex = *(s16 *)(self + 0x22);
        s32 byteOffset = actionIndex * 2;
        u8 *ptr = (u8 *)byteOffset;
        ptr = (u8 *)((u32)ptr + (u32)self);
        *(u8 *)(ptr + 0x19) = 0;
    }
    {
        u32 *callback = gMainObjTimerCallbacks;
        u8 *scriptArgs = self + 0x18;
        u8 *scriptIndex = self + 0x22;
        sub_080C31E4(scriptArgs, scriptIndex, *callback);
    }
    goto label_73A;

label_714:
    timeLeft = *(s32 *)(body + 0x58) - 1;
    *(s32 *)(body + 0x58) = timeLeft;
    if (timeLeft != 0) goto label_73A;
    {
        s32 actionIndex = *(s16 *)(self + 0x22);
        s32 byteOffset = actionIndex * 2;
        u8 *ptr = (u8 *)byteOffset;
        ptr = (u8 *)((u32)ptr + (u32)self);
        *(u8 *)(ptr + 0x17) = 0;
    }
    {
        u32 *callback = gMenuScriptCallback;
        u8 *scriptArgs = self + 0x18;
        u8 *scriptIndex = self + 0x22;
        u32 callbackFn = *callback;
        sub_080C31E8(scriptArgs, scriptIndex, 3, callbackFn);
    }

label_73A:
    sub_0806A884(sprite, body);
    actionId = (u32)sub_0806BCD8(self, sprite, state, body);
    actionPtrOut = (u32 *)(state + 0xC4);
    actionId = (u32)(u16)actionId;
    *actionPtrOut = actionId;
    if (actionId != 0) {
        s32 actionIndex = *(s16 *)(self + 0x22);
        s32 byteOffset = actionIndex * 2;
        u8 *ptr = (u8 *)byteOffset;
        ptr = (u8 *)((u32)ptr + (u32)self);
        *(u8 *)(ptr + 0x17) = 0;
        {
            u32 *callback = gMenuScriptCallback;
            u8 *scriptArgs = self + 0x18;
            u8 *scriptIndex = self + 0x22;
            u32 prevAction = *(u32 *)(state + 0xC4);
            u32 callbackFn = *callback;
            sub_080C31E8(scriptArgs, scriptIndex, (s32)prevAction, callbackFn);
        }
    }
    {
        u8 *effect = state + 0x28;
        stepDelayTimer(effect, sprite);
    }
    sub_0806C6B0(self, sprite, state, body);

end:
    return;
}
