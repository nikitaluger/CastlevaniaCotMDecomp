/* Script command: allocate the sprite and three render parts for a scripted
 * entity, install the cleanup handler and animation, then run its entry script. */
extern void *allocSpriteObject(void);
extern s32 allocWorkSlot(u8 *, s32, s32, s32);
extern s32 findKindIndex(s32);
extern void installUpdateHandler(u8 *, u8 *, void *);
extern void initThreePartSpriteGfx(u8 *, u8 *, s32, s32);
extern void setObjectAnimation(u8 *, u8 *, s32, s32);
extern void *allocEffectPart(void);
extern void sub_080B5684(void);
extern s32 _call_via_r1(u8 *, s32);
extern s32 _call_via_r2(u8 *, u8 *, s32);

struct SpritePart { u8 unk0; u8 kind; u8 layer; u8 unk3; u16 tileStart; u16 frame0; u16 frame1; u16 frame2; u16 frame3; u16 tileEnd; u32 owner; u16 unk14; };
struct SpriteWork { u8 unk0[0x1C]; s16 animType; u8 unk1E[0x22 - 0x1E]; s16 variant; u8 unk24[0x28 - 0x24]; struct SpritePart *render0; u8 unk2C[0x48 - 0x2C]; struct SpritePart *render1; };
struct ScriptedEntity { u8 unk0[2]; u16 flags; u8 unk4[0x22 - 4]; s16 variant; u8 unk24[0x38 - 0x24]; u8 *sprite; struct SpriteWork *work; };
struct GlobalSpriteState { u8 unk0[0x18A8]; u8 unk18A8; u8 unk18A9[0x19]; u16 renderFlags; };
extern struct GlobalSpriteState gMainWorkspace;
struct SpriteTemplate { u8 unk0[8]; u16 tileStart; u16 tileEnd; u8 unkC[0x28 - 0xC]; };
extern struct SpriteTemplate gEffectGfxTable[];
extern u16 D_08102BBC[];
extern u8 D_08102CAC[];
extern u32 gScriptStepCallbackTable;

void scriptCmdSpawnThreePartSprite(struct ScriptedEntity *entity) {
    u8 *sprite;
    struct SpriteWork *work;
    u8 *gfxState;
    u8 *partSlots;
    u8 *framePtr;
    s32 variant;
    u32 zero;
    struct SpritePart *part0;
    struct SpritePart *part1;
    struct SpritePart *part2;
    u16 *frameData;
    u32 *scriptOps;

    sprite = allocSpriteObject();
    if (sprite == NULL)
        goto fail;
    entity->sprite = sprite;
    allocWorkSlot((u8 *)entity, 0, 0x50, 0);
    if (entity->work == NULL)
        goto fail;
    *(u32 *)(sprite + 0x1C) = 0x8000000B;
    work = *(struct SpriteWork *volatile *)((u8 *)entity + 0x3C);
    gfxState = (u8 *)work + 0x34;
    partSlots = (u8 *)work + 0x48;
    installUpdateHandler((u8 *)entity, (u8 *)work, (void *)sub_080B5684);
    work->animType = THREE_PART_SPRITE_KIND;
    variant = findKindIndex(THREE_PART_SPRITE_KIND);
    work->variant = variant;
    if ((s32)(variant << 16) < 0)
        goto fail;
    *(u16 *)sprite |= gMainWorkspace.renderFlags;
    initThreePartSpriteGfx(sprite, gfxState, 0x50, 3);
    setObjectAnimation(sprite, gfxState, 0x78, 0);

    frameData = D_08102BBC;

    part0 = allocEffectPart();
    work->render0 = part0;
    if (part0 == NULL)
        goto fail;
    work->render0->kind = D_08102CAC[0];
    work->render0->layer = 8;
    work->render0->unk3 = 1;
    work->render0->tileStart = gEffectGfxTable[work->animType].tileStart;
    work->render0->frame0 = frameData[0];
    work->render0->frame1 = frameData[1];
    work->render0->frame2 = frameData[2];
    work->render0->frame3 = frameData[3];
    work->render0->tileEnd = gEffectGfxTable[work->animType].tileEnd;
    work->render0->owner = (u32)sprite;

    framePtr = (u8 *)frameData + 8;
    part1 = allocEffectPart();
    work->render1 = part1;
    if (part1 == NULL)
        goto fail;
    work->render1->kind = D_08102CAC[1];
    work->render1->layer = 8;
    work->render1->unk3 = 1;
    work->render1->tileStart = gEffectGfxTable[work->animType].tileStart;
    work->render1->frame0 = frameData[4];
    work->render1->frame1 = *(u16 *)(framePtr + 2);
    work->render1->frame2 = *(u16 *)(framePtr + 4);
    work->render1->frame3 = *(u16 *)(framePtr + 6);
    work->render1->tileEnd = gEffectGfxTable[work->animType].tileEnd;
    work->render1->owner = (u32)sprite;

    framePtr = (u8 *)frameData + 0x10;
    part2 = allocEffectPart();
    *(struct SpritePart **)(partSlots + 4) = part2;
    if (part2 == NULL)
        goto fail;
    goto success;
fail:
    _call_via_r1((u8 *)entity, *(s32 *)((u8 *)entity + 0x24));
    return;
success:
    (*(struct SpritePart **)(partSlots + 4))->kind = D_08102CAC[2];
    (*(struct SpritePart **)(partSlots + 4))->layer = 8;
    (*(struct SpritePart **)(partSlots + 4))->unk3 = 1;
    (*(struct SpritePart **)(partSlots + 4))->tileStart = gEffectGfxTable[work->animType].tileStart;
    (*(struct SpritePart **)(partSlots + 4))->frame0 = frameData[8];
    (*(struct SpritePart **)(partSlots + 4))->frame1 = *(u16 *)(framePtr + 2);
    (*(struct SpritePart **)(partSlots + 4))->frame2 = *(u16 *)(framePtr + 4);
    (*(struct SpritePart **)(partSlots + 4))->frame3 = *(u16 *)(framePtr + 6);
    (*(struct SpritePart **)(partSlots + 4))->tileEnd = gEffectGfxTable[work->animType].tileEnd;
    (*(struct SpritePart **)(partSlots + 4))->owner = (u32)sprite;

    *(u16 *)(sprite + 2) |= 0x400;
    entity->flags |= THREAD_FLAG_WAIT_SPRITE;
    zero = 0;
    *(u8 *)((u8 *)entity + 2 * entity->variant + 0x19) = zero;
    scriptOps = &gScriptStepCallbackTable;
    {
        u8 *scriptPtr = (u8 *)entity + 0x18;
        _call_via_r2(scriptPtr, (u8 *)entity + 0x22, *scriptOps);
        *(u8 *)((u8 *)entity + 2 * entity->variant + 0x19) = *(u8 *)((u8 *)entity + 2 * entity->variant + 0x19) + 1;
        scriptPtr = scriptPtr + 2 * entity->variant;
        _call_via_r1((u8 *)entity, *(s32 *)((u32)(*(u32 **)((u8 *)entity + 0x14)) + 4 * (*scriptPtr)));
    }
}
