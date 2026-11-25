extern void sub_08011368(void *, void *, s32, s32);
extern s16 D_081008C8[];

/* Moving actor tick: play the pose selected by its pose-step counter, then
 * reverse its horizontal velocity when it reaches the movement bounds. */
void sub_08095058(void *arg0)
{
    u8 *self = (u8 *)arg0;
    void *sprite = *(void **)(self + 0x38);
    u8 *body = *(u8 **)(self + 0x3C);
    void *anim = body + 0x34;
    u8 *motion = body + 0x48;
    s16 *poseTable = D_081008C8;
    s32 pose = *(s32 *)(body + 0x48);
    s32 frame = poseTable[pose];

    sub_08011368(sprite, anim, frame, 1);

    if (*(s32 *)(body + 0x10) < 0) {
        if (*(s32 *)(body + 8) <= *(s32 *)(motion + 8))
            *(s32 *)(body + 0x10) = *(s32 *)(motion + 0x10);
    } else {
        if (*(s32 *)(body + 8) >= *(s32 *)(motion + 0x0C))
            *(s32 *)(body + 0x10) = -*(s32 *)(motion + 0x10);
    }
}
