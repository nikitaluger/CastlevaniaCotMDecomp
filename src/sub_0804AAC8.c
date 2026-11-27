extern void advanceMotion(void *, s32);
extern void stepAnimationTrack(void *, void *);
extern void setAnimationFrame(void *, void *, s32, s32);
extern void sub_080C31E0(void *, void *);
extern void sub_080C31E4(void *, void *, void *);
extern void *gScriptStepCallbackTable;

/* Falling object update: integrate its motion with no gravity, refresh the
 * animation, and when it finishes (flag 2) switch to animation 7 and run the
 * next script command. */
void sub_0804AAC8(void *arg0)
{
    void *anim;
    u8 *motion;
    u8 *animDesc;
    s16 scriptIdx;
    u8 *scriptPos;

    anim = *(void **)((u8 *)arg0 + 0x38);
    motion = *(u8 **)((u8 *)arg0 + 0x3C);
    animDesc = motion + 0x34;

    advanceMotion(motion, 0);
    stepAnimationTrack(anim, animDesc);

    if (animDesc[0] & 2) {
        setAnimationFrame(anim, animDesc, 7, 1);

        scriptIdx = *(s16 *)((u8 *)arg0 + 0x22);
        ((u8 *)arg0)[scriptIdx * 2 + 0x19] = 0;

        {
            void **lit = &gScriptStepCallbackTable;
            scriptPos = (u8 *)arg0 + 0x18;
            sub_080C31E4(scriptPos, (u8 *)arg0 + 0x22, *lit);
        }

        scriptIdx = *(s16 *)((u8 *)arg0 + 0x22);
        ((u8 *)arg0)[scriptIdx * 2 + 0x19]++;

        scriptIdx = *(s16 *)((u8 *)arg0 + 0x22);
        scriptPos = scriptPos + scriptIdx * 2;
        sub_080C31E0(arg0, *(void **)(*(u32 *)((u8 *)arg0 + 0x14) + scriptPos[0] * 4));
    }
}
