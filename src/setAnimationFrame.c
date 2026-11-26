extern s32 sub_08010D50(s32, void *, s32, u8);

/* Switch the animation to a new frame: fetch its 4-byte descriptor and start
 * playback; if it is already on that frame, refresh the mode byte instead. */
void setAnimationFrame(s32 obj, void *anim, u16 frame, u8 mode) {
    s16 f;
    u8 m;

    m = mode;
    f = (s16) frame;
    if (*(s16 *)((u8 *)anim + 0xE) != f) {
        *(s16 *)((u8 *)anim + 0xE) = (s16) frame;
        sub_08010D50(obj, anim, **(s32 **)((u8 *)anim + 8) + (f * 4), m);
        return;
    }
    *(u8 *)anim = (u8) ((2 & *(u8 *)anim) | m);
}
