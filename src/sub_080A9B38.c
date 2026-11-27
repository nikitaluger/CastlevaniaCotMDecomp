s32 updateObjectDisplayState(void *, void *);
void sub_08013C8C(void *, void *);
void sub_080C31E0(void *, void *);

/* If the sprite's timed display did not consume this frame, switch the entity to
 * the script handler table at 0x08670098, bump the step index so its action byte
 * is advanced, dispatch that step's handler, then restore the index; finally
 * refresh the sprite's screen position. */
void sub_080A9B38(u8 *self) {
    u8 *sprite = *(u8 **)(self + 0x38);
    if (updateObjectDisplayState(sprite, *(void **)(self + 0x3C)) == 0) {
        s32 stepOffset;
        u8 action;
        u8 *scriptState;
        *(u32 *)(self + 0x14) = 0x08670098;
        *(u16 *)(self + 0x22) = *(u16 *)(self + 0x22) + 1;
        stepOffset = *(s16 *)(self + 0x22) * 2;
        *(u8 *)((u32)stepOffset + (u32)self + 0x19) = *(u8 *)((u32)stepOffset + (u32)self + 0x19) + 1;
        stepOffset = *(s16 *)(self + 0x22) * 2;
        scriptState = self;
        scriptState += 0x18;
        scriptState += stepOffset;
        action = *(u8 *)scriptState;
        sub_080C31E0(self, *(void **)(action * 4 + *(u32 *)(self + 0x14)));
        *(u16 *)(self + 0x22) = *(u16 *)(self + 0x22) - 1;
    }
    sub_08013C8C(self, sprite);
}
