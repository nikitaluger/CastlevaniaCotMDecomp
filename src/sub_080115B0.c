/*
 * Animation setter: start animation `animId` on the animator, playing it
 * forward when `direction` is non-negative and backward otherwise; if the
 * animator already plays that animation, only merge `flags` into its status.
 */
extern s32 sub_08010F5C(s32, void *, s32, s32, s32, s32, s32);
extern s32 sub_08010FA4(s32, void *, s32, s32, s32, s32, s32);

void sub_080115B0(s32 sprite, void *anim, u16 animId, s32 direction, s32 flags) {
    s16 id;
    u8 flag;
    void *frames;
    void *backwardFrames;

    flag = (u8)flags;
    id = (s16)animId;
    if (*(s16 *)((s8 *)anim + 0xE) != id) {
        *(s16 *)((s8 *)anim + 0xE) = (s16)animId;
        if (direction >= 0) {
            frames = *(void **)((s8 *)anim + 8);
            sub_08010F5C(sprite, anim, *(s32 *)frames + (id * 4), *(s32 *)((s8 *)frames + 4), *(s32 *)((s8 *)frames + 8), *(s32 *)((s8 *)anim + 0x10), (s32)flag);
            return;
        }
        backwardFrames = *(void **)((s8 *)anim + 8);
        sub_08010FA4(sprite, anim, *(s32 *)backwardFrames + (id * 4), *(s32 *)((s8 *)backwardFrames + 4), *(s32 *)((s8 *)backwardFrames + 8), *(s32 *)((s8 *)anim + 0x10), (s32)flag);
        return;
    }
    *(u8 *)anim = (u8)((2 & *(u8 *)anim) | flag);
}
