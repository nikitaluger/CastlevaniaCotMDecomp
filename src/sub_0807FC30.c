/* Initializes an entity's child state and graphic callback, copies a couple
   of global values into it, then dispatches the next behavior in its list. */
extern void releaseActorEffectParts(void);
extern void _call_via_r1(void *, void *);
extern void _call_via_r2(void *, void *, void *);
extern void *gMainObjTimerCallbacks;
extern u8 gMainWorkspace[];

void sub_0807FC30(u8 *arg0)
{
    u8 *child;
    u8 *state;
    u8 *gfx;
    s32 zero;
    u8 *args;
    void **callbackPtr;
    s16 index;
    u8 *globals;

    child = *(u8 **)(arg0 + 0x6C);
    state = child + 4;
    gfx = *(u8 **)(arg0 + 0x38);

    zero = 0;
    *(s32 *)(state + 0x2C) = zero;
    *(s32 *)(state + 0x30) = zero;
    *(s32 *)(state + 0x34) = zero;
    *(s32 *)(state + 0x38) = zero;
    *(s32 *)(state + 0x3C) = zero;

    *(u32 *)(state + 0x18) = *(u32 *)(arg0 + 0x24);
    *(void **)(arg0 + 0x24) = &releaseActorEffectParts;
    *(u32 *)(gfx + 0x24) = 0x084EBCCC;

    *(u8 *)(gfx + 0x2A) &= 0xBF;

    globals = gMainWorkspace;
    *(u32 *)(child + 4) = *(u32 *)(globals + 0x14FC);
    *(u32 *)(state + 4) = *(u32 *)(globals + (0xA8 << 5));
    *(s32 *)(state + 0x54) = -1;

    index = *(s16 *)(arg0 + 0x22);
    *(u8 *)(arg0 + index * 2 + 0x19) = 0;

    callbackPtr = &gMainObjTimerCallbacks;
    args = arg0 + 0x18;
    _call_via_r2(args, arg0 + 0x22, *callbackPtr);

    index = *(s16 *)(arg0 + 0x22);
    *(u8 *)(arg0 + index * 2 + 0x19) += 1;

    index = *(s16 *)(arg0 + 0x22);
    args = args + index * 2;
    _call_via_r1(arg0, *(void **)(*(u8 **)(arg0 + 0x14) + *(u8 *)args * 4));
}
