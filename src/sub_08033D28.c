void sub_0803B0D0(void *moveState);
void sub_0803B0D8(void *work, void *moveState, s32 speed);
void sub_08011344(void *sprite, void *animState, s32 frame, s32 flag);
void setSpriteFlipForDirection(void *sprite, void *direction);
void sub_080C31E0(void *actor, void *handler);
void sub_080C31E4(void *actionList, void *scriptIndex, s32 scriptId);

/* Enemy AI step: refresh facing velocity and animation, run the current
 * script action, then switch to the state handler named by the action list. */
void sub_08033D28(void *arg0) {
    u8 *self = (u8 *)arg0;
    void *sprite = *(void **)(self + 0x38);
    void *work = *(void **)(self + 0x3C);
    void *animState = (u8 *)work + 0x34;
    void *moveState = (u8 *)work + 0x48;
    u32 *scriptTable;
    u8 *actionList;
    u8 *scriptIndexPtr;

    sub_0803B0D0(moveState);
    sub_0803B0D8(work, moveState, 0x4000);
    *(void **)((u8 *)work + 0x10) = *(void **)((u8 *)work + 0x48);
    sub_08011344(sprite, animState, 0, 1);
    setSpriteFlipForDirection(sprite, *(void **)((u8 *)work + 0x10));
    *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = 0;
    scriptTable = (u32 *)0x08671BB0;
    actionList = self + 0x18;
    scriptIndexPtr = self + 0x22;
    sub_080C31E4(actionList, scriptIndexPtr, *scriptTable);
    *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) += 1;
    actionList += *(s16 *)(self + 0x22) * 2;
    sub_080C31E0(self, *(void **)(*(u8 *)actionList * 4 + *(u32 *)(self + 0x14)));
}
