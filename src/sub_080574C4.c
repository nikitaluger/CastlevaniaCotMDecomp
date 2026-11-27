extern void sub_08057B6C(void *, void *, void *, void *);
extern void sub_080C31E4(void *, void *, void *);
extern void *gMainObjTimerCallbacks;

/* Falling-object update: apply gravity to the target's y velocity during its
 * first 16 frames; on frame 30 mark the object and its linked effect as landed,
 * give it its horizontal run speed, clear the part's frame counter and advance
 * the animation step; then run the shared motion/render update. */
void sub_080574C4(void *arg0)
{
    void *sprite;
    void *target;
    u8 *motion;
    s16 idx;
    s32 idx2;
    u8 *part;

    sprite = *(void **)((u8 *)arg0 + 0x38);
    target = *(void **)((u8 *)arg0 + 0x3C);
    motion = (u8 *)target + 0x48;

    idx = *(s16 *)((u8 *)arg0 + 0x22);
    idx2 = idx * 2;
    part = (u8 *)idx2 + (s32)(u8 *)arg0;
    if (part[0x19] <= 0x0F) {
        *(u32 *)(motion + 0x0C) += *(u32 *)(motion + 0x18);
    }

    idx = *(s16 *)((u8 *)arg0 + 0x22);
    idx2 = idx * 2;
    part = (u8 *)idx2 + (s32)(u8 *)arg0;
    if (part[0x19] == 0x1E) {
        u8 *landed;
        s32 zero;

        landed = (u8 *)arg0 + 0x8C;
        zero = 0;
        *landed = 1;
        *(u8 *)(*(u8 **)((u8 *)arg0 + 0x30) + 0x8C) = 1;
        *(u32 *)(motion + 0x10) = 0x60000;

        idx = *(s16 *)((u8 *)arg0 + 0x22);
        idx2 = idx * 2;
        part = (u8 *)idx2 + (s32)(u8 *)arg0;
        part[0x19] = (u8)zero;

        {
            void **stepTable = &gMainObjTimerCallbacks;
            void *state = (u8 *)arg0 + 0x18;
            void *index = (u8 *)arg0 + 0x22;
            sub_080C31E4(state, index, *stepTable);
        }
    }

    sub_08057B6C(arg0, sprite, target, motion);
}
