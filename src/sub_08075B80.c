extern void releaseActorEffectParts(void);
extern void startEffectTimer(void *, s32, void *);
extern void _call_via_r1(void *, void *);
extern void _call_via_r2(void *, void *, void *);
extern void *gMainObjTimerCallbacks;
extern u8 gGameStatus[];
extern u8 gMainWorkspace[];

/* Initializes an entity's sub-object and graphics fields (including its
 * update callback), then resets/advances the active action and runs its
 * animation and action handlers. */
void sub_08075B80(u8 *entity)
{
    u8 *extra;
    u8 *fields;
    u8 *gfx;
    u8 *gameState;
    s32 zero;
    u8 *animList;
    void **animDef;
    s16 actionIdx;

    extra = *(u8 **)(entity + 0x6C);
    fields = extra + 4;
    gfx = *(u8 **)(entity + 0x38);
    gameState = gGameStatus;

    zero = 0;
    *(s32 *)(fields + 0x2C) = zero;
    *(s32 *)(fields + 0x30) = zero;
    *(s32 *)(fields + 0x34) = zero;
    *(s32 *)(fields + 0x38) = zero;
    *(s32 *)(fields + 0x3C) = zero;

    *(u32 *)(fields + 0x18) = *(u32 *)(entity + 0x24);
    *(void **)(entity + 0x24) = &releaseActorEffectParts;

    {
        u8 *flags = gMainWorkspace;
        u8 value = *(u8 *)(flags + 0x14F0);
        *(u8 *)(extra + 0x55) = value;
    }

    *(s32 *)(fields + 0x54) = *(s16 *)(gameState + 0x2E2);
    *(s32 *)(fields + 0x58) = *(s16 *)(gameState + 0x2EA);

    *(u32 *)(gfx + 0x24) = 0x084A4BB4;
    startEffectTimer(extra + 0x20, 0, (void *)0x084A4C84);
    *(u32 *)(gfx + 0x1C) = 0x80000006;

    actionIdx = *(s16 *)(entity + 0x22);
    *(u8 *)(entity + actionIdx * 2 + 0x19) = 0;

    animDef = &gMainObjTimerCallbacks;
    animList = entity + 0x18;
    _call_via_r2(animList, entity + 0x22, *animDef);

    actionIdx = *(s16 *)(entity + 0x22);
    *(u8 *)(entity + actionIdx * 2 + 0x19) += 1;

    actionIdx = *(s16 *)(entity + 0x22);
    animList = animList + actionIdx * 2;
    _call_via_r1(entity, *(void **)(*(u8 **)(entity + 0x14) + *(u8 *)animList * 4));
}
