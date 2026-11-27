void sub_08011344(s32, void *, s16, s32);
void sub_080C31E8(void *, void *, s32, u32);

struct S_02025FF0
{
    u8 _0[0x1848];
    u32 flags1848;
    u8 _184C[0x18C5 - 0x184C];
    u8 byte18C5;
    u8 byte18C6;
};
extern struct S_02025FF0 gMainWorkspace;
extern s16 D_08100B98[][2];
extern u32 gMenuScriptCallback;

struct ScriptStep
{
    u8 _0[0x16];
    u16 frame;
    u8 _18[0x22 - 0x18];
    s16 index;
    u8 _24[0x30 - 0x24];
    u32 guard;
    u32 unused34;
    u32 animId;
    u32 targetPtr;
};

/* Clear global flags, then set a child object's animation frame and advance
 * the script step. */
void sub_08097920(struct ScriptStep *step)
{
    u32 animId;
    u32 *target;
    u32 *scriptArg;
    s32 zero = 0;

    if (step->guard != 0)
        return;
    gMainWorkspace.flags1848 &= 0xB281FFFF;
    gMainWorkspace.byte18C6 = 0;
    gMainWorkspace.byte18C5 = 0;
    animId = step->animId;
    target = (u32 *)step->targetPtr;
    sub_08011344(animId, (u8 *)target + 0x1C, D_08100B98[*target][1], 0);
    *(u16 *)((u8 *)target + 0x16) = 1 | zero;
    *(u8 *)((u8 *)step + step->index * 2 + 0x17) = (u8)zero;
    scriptArg = &gMenuScriptCallback;
    sub_080C31E8((u8 *)step + 0x18, (u8 *)step + 0x22, 2, *scriptArg);
}
