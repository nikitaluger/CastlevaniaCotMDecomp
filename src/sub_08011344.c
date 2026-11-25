extern s32 sub_08010D50(s32, void *, s32, u8);

/* Selects animation frame `frame` for `obj`: records the frame index in the
 * animation state at +0xE, then configures the state from the matching entry
 * of its frame table using `mode`. */
void sub_08011344(s32 obj, void *anim, u16 frame, u8 mode) {
    u16 frameIndex;

    frameIndex = frame;
    *(u16 *)((u8 *)anim + 0xE) = frameIndex;
    sub_08010D50(obj, anim,
        **(s32 **)((u8 *)anim + 8) + ((s32)(frameIndex << 0x10) >> 0xE),
        mode);
}
