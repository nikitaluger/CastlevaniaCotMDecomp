extern struct FixedEffectWorkspace gMainWorkspace;
extern struct FixedEffectScroll gCameraState;
extern u8 gSpriteAnimDataTable[];
extern void *allocSpriteObject(void);
extern s32 allocWorkSlot(u8 *, s32, s32, s32);
extern s32 findKindIndex(s32);
extern void sub_08018868(void *);
extern void sub_080C31E0(u8 *, s32);

typedef struct Rec_sub_08018700_sprite {
    u8 pad0[0x2];
    u16 m2;
    u16 m4;
    u8 pad6[0xE];
    u32 m14;
    u32 m18;
    u32 m1C;
    u8 pad20[0x2];
    u16 m22;
    volatile u32 m24;
    volatile u16 m2A;
} Rec_sub_08018700_sprite;
void sub_08018700(struct FixedEffectEntity *entity) {
    u8 *__base_gSpriteAnimDataTable;
    struct FixedEffectState *state;
    Rec_sub_08018700_sprite *sprite;
    s32 animSlot;
    u32 spriteAttr;
    u8 *temp;

    sprite = allocSpriteObject();
    if (sprite == NULL) {
        do { sub_080C31E0((u8 *)entity, *(s32 *)((u8 *)entity + 0x24)); } while (0);
        return;
    }
    entity->sprite = sprite;
    allocWorkSlot((u8 *)entity, 0, 0x34, 0);
    state = entity->state;
    if (state == NULL) {
        sub_080C31E0((u8 *)entity, *(s32 *)((u8 *)entity + 0x24));
        return;
    }
    state->kind = SPRITE_KIND_FIXED_EFFECT;
    state->f18 = 1;
    state->worldX = entity->posX << 16;
    state->worldY = entity->posY << 16;
    do { do { do { animSlot = findKindIndex(SPRITE_KIND_FIXED_EFFECT); } while (0); } while (0); } while (0);
    do { state->animSlot = animSlot; } while (0);
    if ((animSlot << 16) < 0) {
        sub_080C31E0((u8 *)entity, *(s32 *)((u8 *)entity + 0x24));
        return;
    }
    do { spriteAttr = (*(u16 *)sprite & 0xC00) |
        (((state->animSlot << 6) + 0x200) | ((animSlot + 8) << 12)); } while (0);
    *(u16 *)sprite = spriteAttr;
    *(u16 *)sprite = spriteAttr | gMainWorkspace.gfxFlags;
    sprite->m1C = ATTACK_EFFECT_GFX_ID;
    do { temp = (u8 *)&gCameraState; } while (0);
    sprite->m14 = state->worldX -
        ((*(u32 *)(temp + 0x1278 + ((gMainWorkspace.frameCounter + 1) << 6)) + 0x8000) & 0xFFFF0000);
    sprite->m18 = state->worldY -
        ((*(u32 *)((u8 *)&gCameraState + 0x127C + ((gMainWorkspace.frameCounter + 1) << 6)) + 0xFFFF8000) & 0xFFFF0000);
    if (entity->effectParam < 0)
        sprite->m2 &= 0xFFEF;
    else
        sprite->m2 |= 0x10;
    __base_gSpriteAnimDataTable = gSpriteAnimDataTable;
    sprite->m24 = *(u32 *)(__base_gSpriteAnimDataTable + 4 + (state->kind * 0xC));
    sprite->m2A = 7;
    *(u16 *)sprite = (*(u16 *)sprite & 0xFFF) | 0xD000;
    entity->flags |= 0x1000;
    entity->flags |= 0x800;
    entity->scriptStep = 0;
    *(u32 *)((u8 *)entity + 0x14) = (u32)sub_08018868;
}
