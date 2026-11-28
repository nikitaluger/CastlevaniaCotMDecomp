extern void *allocSpriteObject(void);
extern s32 allocWorkSlot(void *, s32, s32, s32);
extern void installUpdateHandler(void *, void *, void *);
extern s32 findKindIndex(s32);
extern void initSpriteGraphics(void *, void *, s32);
extern void setAnimationFrame(void *, void *, s32, s32);
extern void setSpriteFlipForDirection(void *, s32);
extern void sub_080C31E0(void *, void *);
extern void sub_080C31E4(void *, void *, s32);

extern u8 gCameraState[];
extern u8 gMainWorkspace[];
extern u8 gSpriteAnimDataTable[];
extern u32 gEffectKindBySelector[];

/* Spawns a sprite and its work state for a scripted effect whose kind is looked
 * up from gEffectKindBySelector by the parent's selector byte, positions it
 * against the scrolling camera, and dispatches its first script step. */
void spawnKindTableEffectObject(u8 *entity)
{
    void *sprite;
    void *work;
    void *gfxInit;
    s32 kindSlot;
    s32 slotCheck;

    sprite = allocSpriteObject();
    if (sprite == 0)
        goto fail;

    *(void **)(entity + 0x38) = sprite;
    allocWorkSlot(entity, 0, KIND_TABLE_EFFECT_WORK_SIZE, 0);

    if (*(u32 *)(entity + 0x3C) == 0)
        goto fail;

    *(u32 *)((u8 *)sprite + 0x1C) = KIND_TABLE_EFFECT_GFX_ID;
    work = *(void **)(entity + 0x3C);
    gfxInit = (u8 *)work + 0x34;
    installUpdateHandler(entity, work, (void *)KIND_TABLE_EFFECT_UPDATE_CB);

    *(u16 *)((u8 *)work + 0x1C) = gEffectKindBySelector[*(u8 *)(entity + 0x4C)];
    *(u32 *)((u8 *)work + 0x08) = *(u32 *)(entity + 0x5C);
    *(u32 *)((u8 *)work + 0x0C) = *(u32 *)(entity + 0x6C);
    *(s32 *)((u8 *)work + 0x10) = *(s8 *)(entity + 0x7C);

    kindSlot = findKindIndex(*(s16 *)((u8 *)work + 0x1C));
    slotCheck = kindSlot;
    *(s16 *)((u8 *)work + 0x22) = kindSlot;
    if ((slotCheck << 16) >= 0)
        goto cont;

fail:
    sub_080C31E0(entity, *(void **)(entity + 0x24));
    return;

cont:
    {
        s16 storedSlot = *(s16 *)((u8 *)work + 0x22);
        u32 oamAttrs = (((s32)storedSlot << 6) + 0x200) | ((u32)(slotCheck + 8) << 12);
        *(u16 *)((u8 *)sprite + 0x00) = (u16)oamAttrs;
    }

    {
        u8 *workspace = gMainWorkspace;
        *(u16 *)((u8 *)sprite + 0x00) |= *(u16 *)(workspace + 0x18C2);

        initSpriteGraphics(sprite, gfxInit, (s32)gSpriteAnimDataTable + *(s16 *)((u8 *)work + 0x1C) * KIND_TABLE_EFFECT_ANIM_STRIDE);
        setAnimationFrame(sprite, gfxInit, KIND_TABLE_EFFECT_ANIM_FRAME, 0);
        setSpriteFlipForDirection(sprite, *(u32 *)((u8 *)work + 0x10));

        {
            u8 *camera = gCameraState;
            u8 *frameCounter = workspace;
            u8 *scrollXBase;
            u8 *scrollYBase;
            u32 scrollIndex;

            frameCounter += 0x18A8;
            scrollIndex = ((u32)*frameCounter + 1) * 0x40;
            scrollXBase = camera + 0x1278;
            *(u32 *)((u8 *)sprite + 0x14) = *(u32 *)((u8 *)work + 0x08) - ((*(u32 *)(scrollXBase + scrollIndex) + 0x8000) & 0xFFFF0000);
            scrollIndex = ((u32)*frameCounter + 1) * 0x40;
            scrollYBase = camera + 0x127C;
            *(u32 *)((u8 *)sprite + 0x18) = *(u32 *)((u8 *)work + 0x0C) - ((*(u32 *)(scrollYBase + scrollIndex) + 0xFFFF8000) & 0xFFFF0000);
        }
    }

    *(u16 *)(entity + 0x02) |= KIND_TABLE_EFFECT_READY;
    *(u8 *)((u32)(*(s16 *)(entity + 0x22) * KIND_TABLE_EFFECT_STEP_STRIDE) + (u32)entity + 0x19) = 0;

    {
        u32 *scriptTable = (u32 *)MAIN_OBJ_TIMER_CALLBACK_TABLE;
        u8 *scriptSteps = entity + 0x18;
        sub_080C31E4(scriptSteps, entity + 0x22, *scriptTable);

        {
            u8 *stepCounter = (u8 *)((u32)(*(s16 *)(entity + 0x22) * KIND_TABLE_EFFECT_STEP_STRIDE) + (u32)entity + 0x19);
            *stepCounter = (u8)(*stepCounter + 1);
            stepCounter = scriptSteps;
            stepCounter += *(s16 *)(entity + 0x22) * KIND_TABLE_EFFECT_STEP_STRIDE;
            {
                u8 stepCode = *stepCounter;
                sub_080C31E0(entity, *(void **)(*(u32 *)(entity + 0x14) + stepCode * 4));
            }
        }
    }
}
