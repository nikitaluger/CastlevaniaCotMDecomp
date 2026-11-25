extern s32 sub_08003740(void *, void *);
extern s32 sub_0806D518(void *, void *, void *);
extern void sub_0806D588(void *, void *);
extern s32 sub_080C31E0(void *, void *);

struct GameState {
    u8 _pad0[0x10];
    u32 field10;
    u8 _pad1[0x14ED - 0x14];
    u8 byte14ED;
    u8 _pad2[0x173A - 0x14EE];
    u8 byte173A;
    u8 _pad3[0x18C2 - 0x173B];
    u16 word18C2;
};
extern struct GameState D_02025FF0;

/* Updates a spawned projectile effect: honors game-state gates, copies the
 * shared value into it, runs its countdown, tweaks a special-case field, and
 * syncs its offset to the camera; resets graphics on any abort condition. */
void sub_08078240(void *entity) {
    void *slotObj;
    void *objData;
    void *effect;
    struct GameState *state;

    slotObj = *(void **)((u8 *)entity + 0x6C);
    objData = (u8 *)slotObj + 4;
    effect = *(void **)((u8 *)entity + 0x38);
    if (sub_0806D518(entity, effect, objData) != 0)
        return;
    state = &D_02025FF0;
    *(u16 *)effect = state->word18C2;
    if (sub_08003740((u8 *)slotObj + 0x20, effect) == 0) {
        sub_080C31E0(entity, *(void **)((u8 *)entity + 0x24));
        return;
    }
    if (*(u16 *)((u8 *)objData + 0x20) == 2) {
        *(u16 *)((u8 *)*(vu32 *)((u8 *)objData + 0x2C) + 6) = 0xC;
        *(u16 *)((u8 *)*(vu32 *)((u8 *)objData + 0x2C) + 8) = 0xC;
    }
    sub_0806D588(effect, objData);
    if (state->byte173A == 0x1C || (state->byte14ED == 0 && state->field10 != 0))
        sub_080C31E0(entity, *(void **)((u8 *)entity + 0x24));
}
