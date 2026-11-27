extern u8 gCameraState[];    /* scroll-offset table */
extern u8 gMainWorkspace[];    /* global game state */
extern u32 gSpriteAnimDataTable[];   /* frame-control data */
extern u32 gScriptStepCallbackTable[];   /* step-script operation */

extern void allocWorkSlot(void *, u32, u32, u32);
extern void *allocSpriteObject(void *);          /* create the sprite object */
extern void installUpdateHandler(void *, void *, void *);
extern void initWorkStateForKind(void *, void *, void *, void *, u32);
extern void initSpriteGraphics(void *, void *, void *);
extern void setAnimationFrame(void *, void *, u32, u32); /* set animation/frame control */
extern void allocSpriteConfigPart(void *, void *, void *);
extern void initThreeSubObjects(void *, void *, void *, void *);
extern u32 spawnBudgetedEffect(void *, u32);
extern void syncChildObjectParams(void *, void *, void *);
extern void registerScriptObject(void *, u32);
extern void _call_via_r1(void *, void *);   /* cleanup callback */
extern void _call_via_r2(void *, void *, void *); /* run a script handler */
extern void cleanupKind15Sprite(void);

/* Spawn and initialise a scripted sprite using the calling entity's parameters,
 * align its world position to the scene scroll, then either finish setup or
 * abort to the script's cleanup path depending on a game-state flag. */
void spawnKind15ScriptSprite(void *arg0)
{
    u8 *ownerParams = *(u8 **)((u8 *)arg0 + 0xAC);
    u8 *sprite = allocSpriteObject(ownerParams);
    u8 *state;
    u8 *animTrack;
    s16 kindIndex;
    u8 *scriptSteps;
    u8 opcode;

    if (sprite == NULL) goto fail;
    *(u8 **)((u8 *)arg0 + 0x38) = sprite;
    allocWorkSlot(arg0, 0, KIND15_WORK_SLOT, 0);
    if (*(u8 *volatile *)((u8 *)arg0 + 0x3C) == NULL) goto fail;
    *(u32 *)((u8 *)sprite + 0x1C) = KIND15_SPRITE_GFX_ID;
    state = *(u8 **)((u8 *)arg0 + 0x3C);
    animTrack = state + 0x34;
    installUpdateHandler(arg0, state, (void *) cleanupKind15Sprite);
    initWorkStateForKind(arg0, sprite, state, ownerParams, KIND15_SPRITE_KIND);
    *(u16 *)((u8 *)state + 0x04) = KIND15_INIT_VALUE;
    kindIndex = *(s16 *)((u8 *)state + 0x1C);
    initSpriteGraphics(sprite, animTrack, (void *)((u32)kindIndex * KIND15_ANIM_STRIDE + (u32)gSpriteAnimDataTable));
    setAnimationFrame(sprite, animTrack, 0, 1);
    allocSpriteConfigPart(arg0, state, sprite);
    initThreeSubObjects(arg0, state, sprite, (u8 *)state + 0x54);

    if (spawnBudgetedEffect(arg0, KIND15_SPAWN_EFFECT) == 0) {
fail:
        _call_via_r1(arg0, *(void **)((u8 *)arg0 + 0x24));
    } else {
        syncChildObjectParams(arg0, state, sprite);

        {
            u8 *pt = gCameraState;
            u8 *pb = gMainWorkspace;
            u8 *base1;
            u8 *base2;
            u32 idx;

            pb += 0x18A8;

            idx = ((u32)*pb + 1) * 0x40;
            base1 = pt + 0x1278;
            *(u32 *)((u8 *)sprite + 0x14) = *(u32 *)((u8 *)state + 0x08) - ((*(u32 *)(base1 + idx) + 0x8000) & 0xFFFF0000);

            idx = ((u32)*pb + 1) * 0x40;
            base2 = pt + 0x127C;
            *(u32 *)((u8 *)sprite + 0x18) = *(u32 *)((u8 *)state + 0x0C) - ((*(u32 *)(base2 + idx) + 0xFFFF8000) & 0xFFFF0000);
        }

        registerScriptObject(arg0, 0);
        *(u16 *)((u8 *)arg0 + 0x02) |= KIND15_SPRITE_READY;
        *(u8 *)((u8 *)arg0 + *(s16 *)((u8 *)arg0 + 0x22) * 2 + 0x19) = 0;
        {
            u32 litaddr = (u32) gScriptStepCallbackTable;
            scriptSteps = (u8 *)arg0 + 0x18;
            _call_via_r2(scriptSteps, (u8 *)arg0 + 0x22, *(void **)litaddr);
        }
        *(u8 *)((u8 *)arg0 + *(s16 *)((u8 *)arg0 + 0x22) * 2 + 0x19) += 1;
        {
            s32 off = *(s16 *)((u8 *)arg0 + 0x22) * 2;
            opcode = *(u8 *)(scriptSteps + off);
        }
        _call_via_r1(arg0, *(void **)(*(u32 *)((u8 *)arg0 + 0x14) + opcode * 4));
    }
}
