s32 sub_08003740(void *, s32);
s32 sub_0806D588(s32, void *);
s32 sub_080C31E4(void *, void *, s32);

/* Moves the effect's 16.16 x position by its per-frame delta; while it is still
 * within 14.0 the current script step is cleared and restarted, then the
 * animation timer is ticked and the sprite's screen position synced. */
void sub_08088DD4(void *arg0)
{
    s32 x;
    s32 sprite;
    void *motion;
    void *pos;
    int frameTable;
    motion = *((void **) (((s8 *) arg0) + 0x6C));
    pos = motion + 4;
    sprite = *((s32 *) (((s8 *) arg0) + 0x38));
    x = (*((s32 *) (((s8 *) motion) + 4))) + (*((s32 *) (((s8 *) pos) + 8)));
    *((s32 *) (((s8 *) motion) + 4)) = x;
    if (x <= 0xE00000)
    {
        *((s8 *) (((s8 *) (((*((s16 *) (((s8 *) arg0) + 0x22))) * 2) + arg0)) + 0x19)) = 0;
        frameTable = 0x08671BB0;
        sub_080C31E4(arg0 + 0x18, arg0 + 0x22, *((s32 *) frameTable));
    }
    sub_08003740(motion + 0x20, sprite);
    sub_0806D588(sprite, pos);
}
