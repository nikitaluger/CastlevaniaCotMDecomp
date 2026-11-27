s32 sub_080A1894(void *, void *, void *, void *);
void sub_080A1780(void *, void *, void *);
void sub_080A1744(void *, void *);
void sub_080C31E8(void *, void *, s32, s32);

extern s32 gScriptStepCallbacks[];

/* Enemy step: run its ground check and, when the current animation finishes,
 * take a step in the facing direction, update the facing and run the next
 * script command. */
void sub_080A0DB4(void *arg0)
{
    void *anim = *(void **)((u8 *)arg0 + 0x38);
    void *motion = *(void **)((u8 *)arg0 + 0x3C);
    void *animDesc = (u8 *)motion + 0x34;
    void *params = (u8 *)motion + 0x48;

    if (sub_080A1894(anim, motion, animDesc, params) != 0) {
        s32 x = *(s32 *)((u8 *)motion + 0x08);
        if (*(u16 *)((u8 *)anim + 0x02) & 0x10) {
            *(s32 *)((u8 *)motion + 0x08) = x + 0x120000;
        } else {
            *(s32 *)((u8 *)motion + 0x08) = x + (s32)0xFFEE0000;
        }
        sub_080A1780(anim, animDesc, params);
        sub_080A1744(anim, motion);
        *(u8 *)((u8 *)arg0 + *(s16 *)((u8 *)arg0 + 0x22) * 2 + 0x19) = 0;
        {
            s32 *dp = gScriptStepCallbacks;
            sub_080C31E8((u8 *)arg0 + 0x18, (u8 *)arg0 + 0x22, 1, *dp);
        }
    }
}
