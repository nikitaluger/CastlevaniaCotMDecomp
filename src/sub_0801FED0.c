extern void sub_08011368(void *, void *, s32, s32);

/* Play animation frame 0x11 (mode 1) on the object held at +0x38, using the
 * animation state at +0x34 of the work structure held at +0x3C; then tick the
 * work structure's countdown at +0x48 down, clamping it at zero. */
void sub_0801FED0(void *entity)
{
    void *obj = *(void **)((u8 *)entity + 0x38);
    void *work = *(void **)((u8 *)entity + 0x3C);
    sub_08011368(obj, (u8 *)work + 0x34, 0x11, 1);
    if (--*(s32 *)((u8 *)work + 0x48) < 0)
        *(s32 *)((u8 *)work + 0x48) = 0;
}
