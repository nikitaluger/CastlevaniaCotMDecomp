extern void *allocSpriteObject(void);
extern s32 allocWorkSlot(void *, s32, s32, s32);
extern void installUpdateHandler(void *, void *, void *);
extern void sub_08014290(void);
extern void sub_0803C70C(void *, s32, u32, u32, s32, s32);
extern s32 findKindIndex(s32);
extern void setSpriteFlipForDirection(void *, s32);
extern void initSpriteGraphics(void *, void *, s32);
extern void sub_080C31E0(void *, void *);
extern void sub_080C31E4(void *, void *, s32);

extern u8 gCameraState[];
extern u8 gMainWorkspace[];
extern u8 gSpriteAnimDataTable[];
extern u32 gMainObjTimerCallbacks[];

/* Spawn an attack at a randomized offset from its owner: allocate a sprite and
 * work state, pick the animation slot, set graphics/world position relative to
 * the scene scroll, then advance the owner's script to the recorded attack. */
void spawnRandomOffsetAttack(u8 *owner)
{
    void *sprite;
    void *logic;
    void *animData;
    s32 animSlot;
    s32 slotCheck;

    sprite = allocSpriteObject();
    if (sprite == 0)
        goto fail;

    *(void **)(owner + 0x38) = sprite;
    allocWorkSlot(owner, 0, RAND_ATTACK_WORK_SIZE, 0);

    if (*(u32 *)(owner + 0x3C) == 0)
        goto fail;

    *(u32 *)((u8 *)sprite + 0x1C) = ATTACK_EFFECT_GFX_ID;
    logic = *(void **)(owner + 0x3C);
    animData = (u8 *)logic + 0x34;
    installUpdateHandler(owner, logic, (void *)sub_08014290);

    *(u16 *)((u8 *)logic + 0x1C) = RAND_ATTACK_KIND;
    *(u32 *)((u8 *)logic + 0x08) = *(u32 *)(owner + 0x4C);
    *(u32 *)((u8 *)logic + 0x0C) = *(u32 *)(owner + 0x5C);

    sub_0803C70C(logic,
                 *(s8 *)(owner + RAND_ATTACK_X_DIR_MODE),
                 *(u8 *)(owner + RAND_ATTACK_X_MODE),
                 *(u8 *)(owner + RAND_ATTACK_Y_MODE),
                 *(s32 *)(owner + RAND_ATTACK_X_RANGE),
                 *(s32 *)(owner + RAND_ATTACK_Y_RANGE));

    animSlot = findKindIndex(*(s16 *)((u8 *)logic + 0x1C));
    slotCheck = animSlot;
    *(s16 *)((u8 *)logic + 0x22) = animSlot;
    if ((slotCheck << 16) >= 0)
        goto cont;

fail:
    sub_080C31E0(owner, *(void **)(owner + 0x24));
    return;

cont:
    {
        s16 slotField = *(s16 *)((u8 *)logic + 0x22);
        u32 graphics = (((s32)slotField << 6) + RAND_ATTACK_ATTR_BASE) | ((u32)(slotCheck + RAND_ATTACK_FRAME_BIAS) << 12);
        *(u16 *)((u8 *)sprite + 0x00) = (u16)graphics;
    }

    {
        u8 *sceneState = gMainWorkspace;
        *(u16 *)((u8 *)sprite + 0x00) |= *(u16 *)(sceneState + 0x18C2);

        setSpriteFlipForDirection(sprite, *(u32 *)((u8 *)logic + 0x10));

        initSpriteGraphics(sprite, animData, (s32)gSpriteAnimDataTable + *(s16 *)((u8 *)logic + 0x1C) * 12);

        {
            u8 *camera = gCameraState;
            u8 *frameCounter = sceneState;
            u8 *scrollXBase;
            u8 *scrollYBase;
            u32 scrollIndex;

            frameCounter += 0x18A8;
            scrollIndex = ((u32)*frameCounter + 1) * 0x40;
            scrollXBase = camera + 0x1278;
            *(u32 *)((u8 *)sprite + 0x14) = *(u32 *)((u8 *)logic + 0x08) - ((*(u32 *)(scrollXBase + scrollIndex) + 0x8000) & 0xFFFF0000);
            scrollIndex = ((u32)*frameCounter + 1) * 0x40;
            scrollYBase = camera + 0x127C;
            *(u32 *)((u8 *)sprite + 0x18) = *(u32 *)((u8 *)logic + 0x0C) - ((*(u32 *)(scrollYBase + scrollIndex) + 0xFFFF8000) & 0xFFFF0000);
        }
    }

    *(u16 *)(owner + 0x02) |= 0x1000;
    *(u8 *)((u32)(*(s16 *)(owner + 0x22) * 2) + (u32)owner + 0x19) = 0;

    {
        u32 *scriptTable = (u32 *)gMainObjTimerCallbacks;
        u8 *scriptSteps = owner + 0x18;
        sub_080C31E4(scriptSteps, owner + 0x22, *scriptTable);

        {
            u8 *stepCounter = (u8 *)((u32)(*(s16 *)(owner + 0x22) * 2) + (u32)owner + 0x19);
            *stepCounter = (u8)(*stepCounter + 1);
            stepCounter = scriptSteps;
            stepCounter += *(s16 *)(owner + 0x22) * 2;
            {
                u8 stepCode = *stepCounter;
                sub_080C31E0(owner, *(void **)(*(u32 *)(owner + 0x14) + stepCode * 4));
            }
        }
    }
}
