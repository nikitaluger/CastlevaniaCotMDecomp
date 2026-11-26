extern s32 setAnimationFrame(s32, void *, s32, s32);
extern void sub_080C31E0(void *, s32);

/* Clear the entity's two script delta words (+0x14 then +0x10), refresh its
 * sprite descriptor in mode 0x0E, and if the descriptor reports completion
 * (bit 1) chain to the entity's previous update handler. */
void sub_0802CB08(void *arg0) {
    s32 spriteId = *(s32 *)((s8 *)arg0 + 0x38);
    s32 *state = *(s32 **)((s8 *)arg0 + 0x3C);
    void *sprite = (void *)((s8 *)state + 0x34);
    state[5] = 0;
    state[4] = 0;
    setAnimationFrame(spriteId, sprite, 0xE, 0);
    if (2 & *(u8 *)sprite) {
        sub_080C31E0(arg0, *(s32 *)((s8 *)arg0 + 0x24));
    }
}
