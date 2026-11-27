struct AttackGlobalFlags { u8 _0[0x18C2]; u16 flags; };
extern struct AttackGlobalFlags gMainWorkspace;
struct AttackEntity {
    u8 _0, active, kind, variant;
    u16 gfxId, extra0, extra1, extra2, extra3;
    s16 gfxId2;
    u32 sprite;
};
struct AttackState {
    u8 _0[4]; u16 flags; u8 _6[2];
    s32 spawnX, spawnY, velX, velY;
    u8 _18[4]; s16 configIndex; u8 _1E[4]; s16 _22; u8 _24[4];
    struct AttackEntity *entity;
};
struct SpriteCfgRow { u8 _0[0x1C]; u16 gfxId; u16 gfxId2; u8 _20[0x08]; };
struct VelRow { s32 vx; s32 vy; };
extern struct SpriteCfgRow gEffectGfxTable[];
extern struct VelRow gAttackVelTable[];
extern u16 gAttackLayerAttrs[];
extern u32 gScriptStepCallbackTable;
extern void *allocSpriteObject(void);
extern void allocWorkSlot(void *, s32, s32, s32);
extern void installUpdateHandler(void *, void *, void *);
extern void setSpriteFlipForDirection(void *, s32);
extern void initSharedSpriteGraphics(void *, void *);
extern void setAnimationFrame(void *, void *, s32, s32);
extern void *allocEffectPart(void);
extern void sub_080C31E0(u8 *, u32);
extern void sub_080C31E4(u8 *, u8 *, u32);
extern void updateActorEffectSubObject(void);

/* Spawns an attack: allocates a sprite, its logic state and an entity, fills them
 * from the velocity/sprite tables, then records the attack on its owner. */
/* Spawn the kind-0x66 attack: allocate a sprite, logic state and render entity, fill them from the attack velocity/sprite tables and the owner's facing, then record the attack on the owner and advance its script step. */ void spawnKind66Attack(u8 *owner) {
    u8 *sprite;
    struct AttackState *attack;
    u8 *animData;
    u16 *attrTable;
    u8 *attackLog;
    s32 *cmdTable;
    u8 *logEntry;

    sprite = allocSpriteObject();
    if (sprite == NULL) goto fail;
    *(u32 *)(owner + 0x38) = (u32)sprite;
    allocWorkSlot(owner, 0, 0x48, 0);
    if (*(u32 *)(owner + 0x3C) == 0) goto fail;
    *(u32 *)(sprite + 0x1C) = 0x8000000B;
    attack = (struct AttackState *)*(u32 *)(owner + 0x3C);
    animData = (u8 *)attack + 0x34;
    installUpdateHandler(owner, attack, updateActorEffectSubObject);
    attack->configIndex = 0x66;
    *(u16 *)sprite |= gMainWorkspace.flags;
    attack->spawnX = *(u32 *)(owner + 0x4C);
    attack->spawnY = *(u32 *)(owner + 0x5C);
    attack->velX = gAttackVelTable[*(u8 *)(owner + 0x70)].vx * (s8)*(u8 *)(owner + 0x6C);
    attack->velY = gAttackVelTable[*(u8 *)(owner + 0x70)].vy;
    setSpriteFlipForDirection(sprite, -attack->velX);
    initSharedSpriteGraphics(sprite, animData);
    setAnimationFrame(sprite, animData, 0x1A, 1);
    attrTable = gAttackLayerAttrs;
    attack->entity = allocEffectPart();
    if (attack->entity == NULL) goto fail;
    goto cont;
fail:
    sub_080C31E0(owner, *(u32 *)(owner + 0x24));
    return;
cont:
    attack->entity->active = 1;
    attack->entity->kind = 8;
    attack->entity->variant = 1;
    attack->entity->gfxId = gEffectGfxTable[attack->configIndex].gfxId;
    attack->entity->extra0 = attrTable[0];
    attack->entity->extra1 = attrTable[1];
    attack->entity->extra2 = attrTable[2];
    attack->entity->extra3 = attrTable[3];
    attack->entity->gfxId2 = gEffectGfxTable[attack->configIndex].gfxId2;
    attack->entity->sprite = (u32)sprite;
    attack->flags |= 0x10;
    {
        u16 oam = *(u16 *)sprite;
        *(u16 *)sprite = (oam & 0x0FFF) | ((0x0E - (oam >> 12)) << 12);
    }
    *(u32 *)(owner + 0x7C) = 0;
    *(u16 *)(owner + 2) |= 0x1000;
    *(u8 *)(owner + (u32)(*(s16 *)(owner + 0x22)) * 2 + 0x19) = 0;
    cmdTable = &gScriptStepCallbackTable;
    attackLog = owner + 0x18;
    sub_080C31E4(attackLog, owner + 0x22, *cmdTable);
    *(u8 *)(owner + (u32)(*(s16 *)(owner + 0x22)) * 2 + 0x19) += 1;
    logEntry = attackLog + (u32)(*(s16 *)(owner + 0x22)) * 2;
    sub_080C31E0(owner, *(u32 *)(*(u32 *)(owner + 0x14) + *(u8 *)logEntry * 4));
}
