extern void sub_080C31E0(void *, void *);
extern void sub_080C31E4(void *, void *, void *);
extern u16 D_03000830[];
extern void *gMainObjTimerCallback;

/* Drives a scripted sound effect: resets the script when its sound object is
 * gone, otherwise ramps an audio parameter up to its cap and restarts the
 * script once the ramp completes. */
void sub_080087A8(void *arg0)
{
    s16 step;
    u8 *scriptPc;
    s32 soundState;
    s32 zero;
    u8 *soundObj;

    soundObj = *(u8 **)((u8 *)arg0 + 0x3C);
    soundState = *(s32 *)(soundObj + 8);
    if (soundState == 0) {
        *(s32 *)((u8 *)arg0 + 4) = soundState;
        zero = 0;
        D_03000830[2] = 0xBF;
        step = *(s16 *)((u8 *)arg0 + 0x22);
        ((u8 *)arg0)[step * 2 + 0x19] = zero;
        {
            void **lit = &gMainObjTimerCallback;
            scriptPc = (u8 *)arg0 + 0x18;
            sub_080C31E4(scriptPc, (u8 *)arg0 + 0x22, *lit);
        }
        step = *(s16 *)((u8 *)arg0 + 0x22);
        ((u8 *)arg0)[step * 2 + 0x19]++;
        step = *(s16 *)((u8 *)arg0 + 0x22);
        scriptPc = scriptPc + step * 2;
        sub_080C31E0(arg0, *(void **)(*(u32 *)((u8 *)arg0 + 0x14) + scriptPc[0] * 4));
        return;
    }
    *(s32 *)((u8 *)arg0 + 0x4C) = 0;
    {
        s32 ramp = *(s32 *)(soundObj + 0x18) + 2;
        *(s32 *)(soundObj + 0x18) = ramp;
        if (ramp > 0x10) {
            *(s32 *)(soundObj + 0x18) = 0x10;
        }
        D_03000830[2] = 0xFD << 6;
        D_03000830[3] = (u16)(*(s32 *)(soundObj + 0x18) | ((0x10 - *(s32 *)(soundObj + 0x18)) << 8));
        if (*(s32 *)(soundObj + 0x18) == 0x10) {
            step = *(s16 *)((u8 *)arg0 + 0x22);
            ((u8 *)arg0)[step * 2 + 0x19] = 0;
            {
                void **lit = &gMainObjTimerCallback;
                sub_080C31E4((u8 *)arg0 + 0x18, (u8 *)arg0 + 0x22, *lit);
            }
        }
    }
}
