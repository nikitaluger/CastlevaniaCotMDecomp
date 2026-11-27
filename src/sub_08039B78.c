s32 checkActorViewBounds(void *, void *);
void sub_080C31E0(void *, void *);
s32 updateObjectDisplayState(void *, void *);
void syncSpriteToWorldPosition(void *, void *);

/* Entity update: leave to the state handler when off-camera or flagged;
 * otherwise, if this frame was not handled by updateObjectDisplayState, dispatch the next
 * script step from the table installed at +0x14 (0x0866DF00 here), then
 * refresh the sprite's screen coordinates. */
void sub_08039B78(void *arg0) {
    u8 *self = arg0;
    void *sprite = *(void **)(self + 0x38);
    void *work = *(void **)(self + 0x3C);
    if (checkActorViewBounds(sprite, work) == 1 || *(u8 *)(self + 0x88) != 0) {
        sub_080C31E0(arg0, *(void **)(self + 0x24));
        return;
    }
    if (updateObjectDisplayState(sprite, work) == 0) {
        *(u32 *)(self + 0x14) = 0x0866DF00;
        *(u16 *)(self + 0x22) = (u16)(*(u16 *)(self + 0x22) + 1);
        {
            u8 *scriptEntry = (u8 *)((u32)(*(s16 *)(self + 0x22)) * 2 + (u32)self);
            scriptEntry[0x19] = (u8)(scriptEntry[0x19] + 1);
        }
        {
            s32 stepIndex = (*(s16 *)(self + 0x22)) * 2;
            u8 *scriptBase = self + 0x18;
            u8 scriptByte = *(scriptBase + stepIndex);
            void **scriptTable = *(void **)(self + 0x14);
            void *scriptFunc = scriptTable[scriptByte];
            sub_080C31E0(arg0, scriptFunc);
        }
        *(u16 *)(self + 0x22) = (u16)(*(u16 *)(self + 0x22) - 1);
    }
    syncSpriteToWorldPosition(arg0, sprite);
}
