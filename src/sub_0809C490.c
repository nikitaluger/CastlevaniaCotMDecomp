/* Initialise an entity from its animation state: copy two parameters, set the
 * facing direction from the sprite's flip flag, and set the +0x80 flag to 0
 * only when the current animation frame's graphic is 0x8F. */
void sub_0809C490(void *arg0, void *sprite, void *params, void *anim) {
    if (arg0 != NULL) {
        u8 *self = arg0;
        *(u32 *)(self + 0x4C) = *(u32 *)((u8 *)params + 8);
        *(u32 *)(self + 0x5C) = *(u32 *)((u8 *)params + 0xC);
        *(s32 *)(self + 0x6C) = (0x10 & *(u16 *)((u8 *)sprite + 2)) ? 1 : -1;
        {
            u8 *animState = anim;
            u8 ***ppFrameTable = (u8 ***)(animState + 8);
            u8 **frameTable = *ppFrameTable;
            s32 idx = *(s16 *)(animState + 0xE) + animState[1];
            u8 *frames = *frameTable;
            u16 *frame = (u16 *)(idx * 4 + (u32)frames - 4);
            u16 graphic = frame[1];
            if (graphic == 0x8F) {
                *(u8 *)(self + 0x80) = 0;
            } else {
                *(u8 *)(self + 0x80) = 1;
            }
        }
    }
}
