extern struct FixedEffectWorkspace gMainWorkspace;
extern u8 gCameraState[];
extern u8 gSpriteAnimDataTable[];
extern u8 *allocSpriteObject(void);
extern s32 allocWorkSlot(u8 *, s32, s32, s32);
extern s32 findKindIndex(s32);
extern void sub_0801C00C(void *);
extern void _call_via_r1(u8 *, s32);

void sub_0801BEA4(struct FixedEffectEntity *entity) {
    struct FixedEffectState *state;
    u8 *sprite;
    u8 *cameraState;
    s32 animSlot;
    u32 spriteAttr;

    sprite = allocSpriteObject();
    if (sprite == NULL) {
        _call_via_r1((u8 *)entity, *(s32 *)((u8 *)entity + 0x24));
        return;
    }
    entity->sprite = sprite;
    allocWorkSlot((u8 *)entity, 0, 0x34, 0);
    if (entity->state == NULL) {
        _call_via_r1((u8 *)entity, *(s32 *)((u8 *)entity + 0x24));
        return;
    }
    state = entity->state;
    state->kind = SPRITE_KIND_KIND87_EFFECT;
    state->f18 = 1;
    state->worldX = entity->posX << 16;
    state->worldY = entity->posY << 16;
    animSlot = findKindIndex(SPRITE_KIND_KIND87_EFFECT);
    state->animSlot = animSlot;
    if ((animSlot << 16) < 0) {
        _call_via_r1((u8 *)entity, *(s32 *)((u8 *)entity + 0x24));
        return;
    }
    spriteAttr = (*(u16 *)sprite & 0xC00) |
        (((state->animSlot << 6) + 0x200) | ((animSlot + 8) << 12));
    *(u16 *)sprite = spriteAttr;
    *(u16 *)sprite = spriteAttr | gMainWorkspace.gfxFlags;
    *(u32 *)(sprite + 0x1C) = ATTACK_EFFECT_GFX_ID;
    cameraState = (u8 *)(&gCameraState);
    {
        u32 k = 0x1278;
        *(u32 *)(sprite + 0x14) = state->worldX - (((*((u32 *)((cameraState + k) + ((gMainWorkspace.frameCounter + 1) << 6)))) + 0x8000) & 0xFFFF0000);
    }
    {
        u32 k = 0x127C;
        *(u32 *)(sprite + 0x18) = state->worldY - (((*((u32 *)((cameraState + k) + ((gMainWorkspace.frameCounter + 1) << 6)))) + 0xFFFF8000) & 0xFFFF0000);
    }
    if (entity->effectParam < 0)
        *(u16 *)(sprite + 2) &= 0xFFEF;
    else
        *(u16 *)(sprite + 2) |= 0x10;
    *(u32 *)(sprite + 0x24) = *(u32 *)((u8 *)gSpriteAnimDataTable + 4 + state->kind * 0xC);
    *(u16 *)(sprite + 0x28) = 7;
    *(u16 *)sprite = (*(u16 *)sprite & 0xFFF) | 0xD000;
    entity->flags |= 0x1000;
    entity->flags |= 0x800;
    entity->scriptStep = 0;
    *(u32 *)((u8 *)entity + 0x14) = (u32)sub_0801C00C;
}
