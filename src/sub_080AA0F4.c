s32 updateObjectDisplayState(void *, void *);
void sub_08013C8C(void *, void *);
void sub_080C31E0(void *, void *);
void sub_080AA1DC(void *);

/* If the sprite's timed display did not consume this frame, switch the entity to
 * the script handler table at 0x086700C4, bump the step index so its action byte
 * is advanced, dispatch that step's handler, then restore the index; finally
 * recompute the limb transform stored at work+0x48. */
void sub_080AA0F4(u8 *self) {
    u8 *sprite = *(u8 **)(self + 0x38);
    u8 *work = *(u8 **)(self + 0x3C);
    u8 *limbs = work + 0x48;
    if (updateObjectDisplayState(sprite, work) == 0) {
        s32 stepOffset;
        u8 action;
        u8 *scriptState;
        *(u32 *)(self + 0x14) = 0x086700C4;
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
    sub_080AA1DC(limbs);
}
