/* Spawned sound/effect entity; the behavior selector lives at +0x84. */
struct EffectEntity {
    u8 pad[0x84];
    u8 behavior;
};

/* Select the behavior byte (0 = idle, 1 = active, 2/3 = special) of an effect entity. */
void setEffectBehavior(struct EffectEntity *effect, u8 behavior) {
    effect->behavior = behavior;
}
