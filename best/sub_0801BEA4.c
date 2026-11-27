extern struct FixedEffectWorkspace gMainWorkspace;
extern struct FixedEffectScroll gCameraState;
extern u8 gSpriteAnimDataTable[];
extern void *allocSpriteObject(void);
extern s32 allocWorkSlot(u8 *, s32, s32, s32);
extern s32 findKindIndex(s32);
extern void sub_0801C00C(void *);
extern void sub_080C31E0(u8 *, s32);

void sub_0801BEA4(struct FixedEffectEntity *entity) {
    struct FixedEffectState *state;
    u8 *sprite;
    s32 animSlot;
    u32 spriteAttr;

    sprite = allocSpriteObject();
    if (sprite == NULL) {
        sub_080C31E0((u8 *)entity, *(s32 *)((u8 *)entity + 0x24));
        return;
    }
    entity->sprite = sprite;
    allocWorkSlot((u8 *)entity, 0, 0x34, 0);
    state = entity->state;
    if (state == NULL) {
        sub_080C31E0((u8 *)entity, *(s32 *)((u8 *)entity + 0x24));
        return;
    }
    state->kind = SPRITE_KIND_KIND87_EFFECT;
    state->f18 = 1;
    state->worldX = entity->posX << 16;
    state->worldY = entity->posY << 16;
    animSlot = findKindIndex(SPRITE_KIND_KIND87_EFFECT);
    state->animSlot = animSlot;
    if ((animSlot << 16) < 0) {
        sub_080C31E0((u8 *)entity, *(s32 *)((u8 *)entity + 0x24));
        return;
    }
    spriteAttr = (*(u16 *)sprite & 0xC00) |
        (((state->animSlot << 6) + 0x200) | ((animSlot + 8) << 12));
    *(u16 *)sprite = spriteAttr;
    *(u16 *)sprite = spriteAttr | gMainWorkspace.gfxFlags;
    *(u32 *)(sprite + 0x1C) = ATTACK_EFFECT_GFX_ID;
    *(u32 *)(sprite + 0x14) = state->worldX -
        ((*(u32 *)((u8 *)&gCameraState + 0x1278 + ((gMainWorkspace.frameCounter + 1) << 6)) + 0x8000) & 0xFFFF0000);
    *(u32 *)(sprite + 0x18) = state->worldY -
        ((*(u32 *)((u8 *)&gCameraState + 0x127C + ((gMainWorkspace.frameCounter + 1) << 6)) + 0xFFFF8000) & 0xFFFF0000);
    if (entity->effectParam < 0)
        *(u16 *)(sprite + 2) &= 0xFFEF;
    else
        *(u16 *)(sprite + 2) |= 0x10;
    {
        u8 *animTable = gSpriteAnimDataTable + 4;
        *(u32 *)(sprite + 0x24) = *(u32 *)(animTable + state->kind * 0xC);
    }
    *(u16 *)(sprite + 0x2A) = 7;
    *(u16 *)sprite = (*(u16 *)(sprite + 2) & 0xFFF) | 0xD000;
    entity->flags |= 0x1800;
    entity->scriptStep = 0;
    *(u32 *)((u8 *)entity + 0x14) = (u32)sub_0801C00C;
}
