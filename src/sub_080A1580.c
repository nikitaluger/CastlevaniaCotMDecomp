/* Update an effect-emitter entity from its current script step: spawn a
 * periodic projectile at the spawn point and reset when the script ends. */
extern s32 scaleByRandom(s32);
extern s32 randomSignedOffset(s32);
extern void sub_08005FC4(s32, s32, s32, s32, void *);
extern void spawnEffectParticle(s32, s32, s32, s32);
extern void sub_080C0384(void);
extern void sub_080C31E4(void *, void *, s32);
extern u32 gMainObjTimerCallbacks;

struct Entity {
    u8 _0[0x18];
    u8 _1[0x22 - 0x18];
    s16 f22;
    u8 _2[0x38 - 0x24];
    u32 f38;
    u32 f3C;
};
struct EffectState {
    u16 f0;
    u8 _0[2];
    u16 f4;
    u16 f6;
};
struct SpawnPoint {
    u8 _0[8];
    u32 f08;
    u32 f0C;
};
struct ScriptStep {
    u8 _0[0x19];
    u8 f19;
};

void sub_080A1580(struct Entity *entity) {
    struct EffectState *state;
    struct SpawnPoint *spawnPoint;
    u16 stepOpcode;
    u32 temp, spawnX, spawnY;
    s32 angle, speed;

    state = (struct EffectState *)entity->f38;
    spawnPoint = (struct SpawnPoint *)entity->f3C;
    if (!(((struct ScriptStep *)((u8 *)entity + entity->f22 * 2))->f19 & 2)) {
        temp = (0xFFF & state->f0) | 0xE000;
        state->f0 = temp;
    }
    if (((struct ScriptStep *)((u8 *)entity + entity->f22 * 2))->f19 > 0x96) {
        temp = state->f4 - 1;
        state->f4 = temp;
        state->f6 = temp;
    }
    stepOpcode = ((struct ScriptStep *)((u8 *)entity + entity->f22 * 2))->f19;
    if (!(stepOpcode & 0xF) && stepOpcode <= 0x95) {
        spawnX = spawnPoint->f08;
        spawnY = spawnPoint->f0C;
        angle = randomSignedOffset(0x8000);
        speed = scaleByRandom(0x20000) + 0x40000;
        spawnEffectParticle(spawnX, spawnY, angle, -speed);
    }
    if (((struct ScriptStep *)((u8 *)entity + entity->f22 * 2))->f19 == 0xF0) {
        sub_08005FC4(0, 0xC3 << 1, 3, 0, &sub_080C0384);
        ((struct ScriptStep *)((u8 *)entity + entity->f22 * 2))->f19 = 0;
        {
            u32 *p = &gMainObjTimerCallbacks;
            sub_080C31E4((u8 *)entity + 0x18, (u8 *)entity + 0x22, *p);
        }
    }
}
