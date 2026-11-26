s32 copyPoseAttrs(void *, void *);
s32 sub_080C31E0(s32, void *);
extern void *D_08671BFC;
extern u8 gPairedEffectLayerAttrs[];

struct B { u8 pad[8]; u16 angle; };

/* Position a projectile from its parameter block (using trig lookups when
 * requested), copy the angle-indexed graphics parameters into its sprite
 * state, and store the resulting coordinates into the target object. */
void sub_08057B6C(void *target, void *state, void *work, void *params)
{
    u32 *out = (u32 *)target;
    u16 *stateWords = (u16 *)state;
    u32 *workWords = (u32 *)work;
    u32 *paramsWords = (u32 *)params;
    void **trigTable;
    s32 tableIndex;
    void *gfxState;

    ((struct B *)state)->angle = (u16)paramsWords[3];
    if (*(u8 *)paramsWords != 0)
    {
        trigTable = &D_08671BFC;
        workWords[2] = paramsWords[1] - (sub_080C31E0(paramsWords[3] + 0x4000, *trigTable) << 4);
        workWords[3] = paramsWords[2] + (sub_080C31E0(paramsWords[3], *trigTable) << 4);
    }
    else
    {
        workWords[2] = paramsWords[1];
        workWords[3] = paramsWords[2];
    }
    gfxState = (void *)workWords[10];
    tableIndex = (s32)(((u32)stateWords[4] + 0x800) & 0xFFFF);
    copyPoseAttrs(gfxState, gPairedEffectLayerAttrs + ((tableIndex >> 12) * 8));
    out[0x17] = workWords[2];
    out[0x1B] = workWords[3];
    out[0x1F] = paramsWords[3];
}
