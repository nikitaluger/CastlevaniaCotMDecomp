/* Per-frame update for a three-part composite enemy: clears the extra parts'
 * hit flags, runs the movement/bounds check and each part's damage/display
 * update, uploads pending part graphics, switches to the state handler table
 * for the next phase, applies the palette/terrain parameters, and finishes the
 * part update. */
extern void sub_08005E80(s32);                    /* play sound */
extern void stepAnimationTrack(s32, void *);            /* step animation */
extern void sub_08011EE8(void *, s32, s32);       /* terrain/movement update */
extern s32 sub_08013558(s32, void *, void *);     /* part damage/hit update */
extern void spawnContactEffectOnHit(void *, void *);         /* spawn contact hit effect */
extern void updateActorWorldPosition(void *);                 /* final position/score update */
extern s32 updateObjectDisplayState(s32, void *);             /* apply part display state */
extern void applySpritePaletteVariant(void *, s32);            /* apply palette/flags to sprite */
extern void sub_08013C8C(void *, s32);            /* finish part update */
extern s32 checkActorViewBounds(s32, void *);             /* movement bounds check */
extern void uploadPendingSpriteGraphic(void *, void *);         /* upload pending part graphics */
extern void sub_08042900(s32, void *);            /* copy part palette/animation params */
extern void sub_080C31E0(void *, void *);         /* indirect call */
extern void sub_080C31E8(void *, void *, s32, s32); /* state machine dispatch */
extern u8 sScriptStepCallbacks[];   /* death-state handler table */
extern u8 gThreePartEnemyStateHandlers[];   /* next-phase state handler table */

/* AND helpers keep the mask in the destination register (see and-result wall). */
static inline u32 and1(u16 v)
{
    u32 m = 1;
    m &= v;
    return m;
}

static inline u32 and8000(u16 v)
{
    u32 m = 0x8000;
    m &= v;
    return m;
}

static inline u32 andD(u16 v)
{
    u32 m = 0x0D;
    m &= v;
    return m;
}

/* Per-frame update for a three-part composite enemy: check bounds, update each part's damage and graphics, run the next-phase state handler, and finish the part update. */ void updateThreePartEnemy(u8 *entity)
{
    s32 sprite = *(s32 *)(entity + 0x38);
    u8 *work = *(u8 **)(entity + 0x3C);      /* composite work block */
    u8 *gfxInit = work + 0x34;
    u8 *parts = work + 0x48;
    u8 *extraParts;
    u32 zero;
    s32 i;

    zero = 0;
    extraParts = work + 0x50;
    {
        u32 addr = (u32)gfxInit;
        u8 **slotPtr = (u8 **)(addr + 0x1C);
        for (i = 1; i >= 0; i--)
        {
            *((u8 *)(*slotPtr++) + 1) = zero;
        }
    }
    if (checkActorViewBounds(sprite, work) == 1) goto end;
    applySpritePaletteVariant(entity, sprite);
    if (sub_08013558(sprite, work, *(void **)(work + 0x28)) != 0)
        spawnContactEffectOnHit(entity, *(void **)(work + 0x28));
    uploadPendingSpriteGraphic(entity, *(void **)(work + 0x28));
    {
        u8 **slotPtr = (u8 **)extraParts;
        for (i = 1; i >= 0; i--)
        {
            uploadPendingSpriteGraphic(entity, *(void **)slotPtr);
            slotPtr++;
        }
    }
    if (and1(*(u16 *)work) && (*(u8 *)(entity + (*(s16 *)(entity + 0x22)) * 2 + 0x1A) != 2))
    {
        u32 *stateTable;
        updateActorWorldPosition(entity);
        sub_08005E80(0x85);
        *(u8 *)(entity + (*(s16 *)(entity + 0x22)) * 2 + 0x1B) = 0;
        stateTable = (u32 *)sScriptStepCallbacks;
        sub_080C31E8(entity + 0x18, entity + 0x22, 2, *stateTable);
    }
    if (updateObjectDisplayState(sprite, work) == 0)
    {
        s32 stateOffset;
        u8 *stateData;
        u8 stateId;
        u32 *handlerTable;
        u32 handler;
        *(u32 *)(entity + 0x14) = (u32)gThreePartEnemyStateHandlers;
        *(u16 *)(entity + 0x22) = (u16)(*(u16 *)(entity + 0x22) + 1);
        *(u8 *)(entity + (*(s16 *)(entity + 0x22)) * 2 + 0x19) =
            (u8)(*(u8 *)(entity + (*(s16 *)(entity + 0x22)) * 2 + 0x19) + 1);
        stateOffset = (*(s16 *)(entity + 0x22)) * 2;
        stateData = entity + 0x18;
        stateId = *(stateData + stateOffset);
        handlerTable = (u32 *)*(u32 *)(entity + 0x14);
        handler = handlerTable[stateId];
        sub_080C31E0(entity, (void *)handler);
        *(u16 *)(entity + 0x22) = (u16)(*(u16 *)(entity + 0x22) - 1);
        if (and8000(*(u16 *)(entity + 2))) goto end;
        if (*(s16 *)(parts + 4) == 1)
            stepAnimationTrack(sprite, gfxInit);
        sub_08011EE8(work, 0x16C1, 0);
    }
    sub_08042900(sprite, work);
    if ((andD(*(u16 *)work) == 0) && *(u16 *)(sprite + 0x28) == 0x14)
    {
        u32 mask = 1;
        u8 **slotPtr = (u8 **)extraParts;
        i = 1;
        while (i >= 0)
        {
            u8 *part = *slotPtr++;
            part[1] |= mask;
            i--;
        }
    }
    sub_08013C8C(entity, sprite);
end:
    ;
}
