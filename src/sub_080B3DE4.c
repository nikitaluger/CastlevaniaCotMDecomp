s32 advanceAnimTrack(s32, void *);
void sub_08011EE8(void *, s32, s32);
void sub_080C31E4(void *, void *, s32);

// Animator step: set up the animator with its sprite, clear work+0x10 when
// certain sprite flags are set, then look up the current animation frame and
// advance the script step when its frame code is 0x19.
void sub_080B3DE4(void *arg0)
{
    void *work;
    void *animator;
    s32 *scriptTable;
    s32 sprite;
    s32 frame;
    s32 frameSum;
    s32 tableBase;
    s32 *frameTable;

    sprite = *(s32 *)((s8 *)arg0 + 0x38);
    work = *(void **)((s8 *)arg0 + 0x3C);
    animator = (s8 *)work + 0x34;
    advanceAnimTrack(sprite, animator);
    sub_08011EE8(work, 0x4000, 0);
    if (0x201 & *(u16 *)((s8 *)work + 2))
        *(s32 *)((s8 *)work + 0x10) = 0;
    if (4 & *(u16 *)((s8 *)work + 2))
        *(s32 *)((s8 *)work + 0x10) = 0;
    frameTable = *(s32 **)((s8 *)animator + 8);
    frameSum = *(s16 *)((s8 *)animator + 0xE) + *(u8 *)((s8 *)animator + 1);
    tableBase = *frameTable;
    frame = frameSum * 4 + tableBase - 4;
    if (*(u16 *)((s8 *)frame + 2) == 0x19)
    {
        *(s8 *)(((s8 *)(((*(s16 *)((s8 *)arg0 + 0x22)) * 2) + arg0)) + 0x19) = 0;
        scriptTable = (s32 *)0x08671BB0;
        sub_080C31E4((s8 *)arg0 + 0x18, (s8 *)arg0 + 0x22, *scriptTable);
    }
}
