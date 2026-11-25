extern void sub_080113A8(void *target, void *anim);
extern void sub_08011EE8(void *actor, s32 velocity, s32 height);

/* Per-frame callback: advances the animation state at actor+0x34, which also
 * refreshes the linked object's current-frame value, then updates the actor's
 * movement with no added velocity. */
void sub_080B6720(void *arg0) {
    void *target = (void *)*(s32 *)((u8 *)arg0 + 0x38);
    u8 *actor = *(u8 **)((u8 *)arg0 + 0x3C);
    sub_080113A8(target, actor + 0x34);
    sub_08011EE8(actor, 0, 0);
}
