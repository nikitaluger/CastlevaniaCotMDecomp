extern void sub_080C31E0(void *, void *);

/* Per-stage scene state in the graphics workspace. +0x1780 is an array of
 * per-slot state words indexed by an entity's slot id (+0xAC). */
struct SceneState {
    u8 _p0[0x14ED];
    u8 a_14ED;
    u8 _p1[0x14F0 - 0x14EE];
    u8 a_14F0;
    u8 _p2[0x1780 - 0x14F1];
    u32 slotState[1];
};
extern struct SceneState D_02025FF0;

/* Clear the entity's per-slot scene state word, then run its pending update
 * callback. */
void sub_0806D2D0(void *entity) {
    D_02025FF0.slotState[*(u32 *)((u8 *)entity + 0xAC)] = 0;
    sub_080C31E0(entity, *(void **)((u8 *)entity + 0x24));
}
