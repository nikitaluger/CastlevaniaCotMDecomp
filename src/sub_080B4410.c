void sub_08005E80(s32);
s32 advanceAnimTrack(s32, void *);
void sub_080C31E8(void *, void *, s32, s32);

extern s32 gMenuScriptCallback;

/* Walking update: advance the animation; when the frame's command value
 * changes to 0x42 play sound 0x195, and when the animation ends clear the
 * step flag and run script command 3. */
void sub_080B4410(void *arg0)
{
    void *motion;
    void *animDesc;
    s32 anim;
    u16 prevCmd;
    s32 *framePtr;
    s32 idx;
    s32 tbl;
    s32 entry;

    anim = *(s32 *)((s8 *)arg0 + 0x38);
    motion = *(void **)((s8 *)arg0 + 0x3C);
    animDesc = (s8 *)motion + 0x34;
    framePtr = *(s32 **)((s8 *)animDesc + 8);
    idx = *(s16 *)((s8 *)animDesc + 0xE) + *(u8 *)((s8 *)animDesc + 1);
    tbl = *framePtr;
    entry = idx * 4 + tbl - 4;
    prevCmd = *(u16 *)((s8 *)entry + 2);
    advanceAnimTrack(anim, animDesc);
    {
        s32 *framePtr2;
        s32 idx2;
        s32 tbl2;
        s32 entry2;
        u16 cmd;

        framePtr2 = *(s32 **)((s8 *)animDesc + 8);
        idx2 = *(s16 *)((s8 *)animDesc + 0xE) + *(u8 *)((s8 *)animDesc + 1);
        tbl2 = *framePtr2;
        entry2 = idx2 * 4 + tbl2 - 4;
        cmd = *(u16 *)((s8 *)entry2 + 2);
        if (prevCmd != cmd && cmd == 0x42) {
            sub_08005E80(0x195);
        }
    }
    if (2 & *(u8 *)((s8 *)animDesc + 0)) {
        *(s8 *)(((s8 *)(((*(s16 *)((s8 *)arg0 + 0x22)) * 2) + arg0)) + 0x17) = 0;
        {
            s32 *dp = &gMenuScriptCallback;
            sub_080C31E8((s8 *)arg0 + 0x18, (s8 *)arg0 + 0x22, 3, *dp);
        }
    }
}
