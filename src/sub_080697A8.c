extern struct { u8 _0[0x14ED]; u8 gameMode; } D_02025FF0;
extern s32 D_08671BD8;

s32 sub_0806C4B4(void *, void *);
void sub_0806C5EC(void *, void *, void *, void *);
void sub_0806C6B0(void *, void *, void *, void *);
u16 sub_08065CC8(void *, void *, void *, void *);
void sub_080C31E8(void *, void *, s32, s32);

/* Advance one step of this entity's script: set up the game-state-derived
 * position, clear the step counter, then dispatch the step's callback. */
void sub_080697A8(u8 *entity) {
    u8 *comp = *(u8 **)(entity + 0x6C);
    u8 *ctx = comp + 4;
    u8 *state = *(u8 **)(entity + 0x38);
    u8 *out = ctx;

    if (sub_0806C4B4(out, out) == 0) {
        sub_0806C5EC(entity, state, out, out);
        if (D_02025FF0.gameMode == 0xAA) {
            if (comp[0x12C] != 0) {
                s32 *hookSlot;
                entity[*(s16 *)(entity + 0x22) * 2 + 0x17] = 0;
                hookSlot = &D_08671BD8;
                sub_080C31E8(entity + 0x18, entity + 0x22, 0x29, *hookSlot);
            } else {
                s32 *hookSlot;
                entity[*(s16 *)(entity + 0x22) * 2 + 0x17] = 0;
                hookSlot = &D_08671BD8;
                sub_080C31E8(entity + 0x18, entity + 0x22, 0x24, *hookSlot);
            }
        } else {
            s32 *hookSlot;
            entity[*(s16 *)(entity + 0x22) * 2 + 0x17] = 0;
            hookSlot = &D_08671BD8;
            sub_080C31E8(entity + 0x18, entity + 0x22,
                         sub_08065CC8(entity, state, out, out), *hookSlot);
        }
        sub_0806C6B0(entity, state, ctx, out);
    }
}
