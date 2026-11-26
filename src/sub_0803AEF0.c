struct SpriteConfig {
    u8 unk0; u8 kind; u8 subKind; u8 active;
    u16 tableA; u16 offset0; u16 offset1; u16 offset2; u16 offset3; u16 tableB;
    u32 sprite;
};
struct ConfigEntry { u16 value0; u16 pad; u16 value4; };
struct SpriteConfig *allocEffectPart(void);
void sub_080C31E0(void *, void *);

/* Allocate the sprite-config record kept in the logic's +0x28 slot and fill it
 * from the fixed tables at 0x080CF1F0 / 0x080CB2B8 (indexed by the s16 at
 * logic+0x1C); if allocation fails, jump to the entity's state handler. */
void sub_0803AEF0(void *entity, u8 *logic, s32 sprite) {
    u16 *offsets = (u16 *)0x080CF1F0;
    struct SpriteConfig *config = allocEffectPart();
    *(struct SpriteConfig **)(logic + 0x28) = config;
    if (config == NULL) {
        sub_080C31E0(entity, *(void **)((u8 *)entity + 0x24));
        return;
    }
    config->kind = 5;
    (*(struct SpriteConfig **)(logic + 0x28))->subKind = 8;
    (*(struct SpriteConfig **)(logic + 0x28))->active = 1;
    {
        struct SpriteConfig *cfg;
        u8 *table;
        cfg = *(struct SpriteConfig **)(logic + 0x28);
        table = (u8 *)0x080CB2B8;
        cfg->tableA = ((struct ConfigEntry *)(table + *(s16 *)(logic + 0x1C) * 20))->value0;
        (*(struct SpriteConfig **)(logic + 0x28))->offset0 = offsets[0];
        (*(struct SpriteConfig **)(logic + 0x28))->offset1 = offsets[1];
        (*(struct SpriteConfig **)(logic + 0x28))->offset2 = offsets[2];
        (*(struct SpriteConfig **)(logic + 0x28))->offset3 = offsets[3];
        (*(struct SpriteConfig **)(logic + 0x28))->tableB =
            ((struct ConfigEntry *)(table + *(s16 *)(logic + 0x1C) * 20))->value4;
        (*(struct SpriteConfig **)(logic + 0x28))->sprite = sprite;
    }
}
