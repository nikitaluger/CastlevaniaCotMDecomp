extern void setAnimationFrame(s32, void *, s32, s32);
extern void sub_080C31E0(void *, s32);

/* Clear the entity's two script delta words (+0x14, +0x10), refresh its sprite
 * descriptor in mode 0x2D, and if the descriptor reports completion (bit 1)
 * chain to the entity's previous update handler. */
void sub_0802165C(void *arg0)
{
    s32 spriteId = *(s32 *)((u8 *)arg0 + 0x38);
    u8 *state = *(u8 **)((u8 *)arg0 + 0x3C);
    void *sprite = state + 0x34;
    *(u32 *)(state + 0x14) = 0;
    *(u32 *)(state + 0x10) = 0;
    setAnimationFrame(spriteId, sprite, 0x2D, 0);
    if (2 & *(u8 *)sprite)
        sub_080C31E0(arg0, *(s32 *)((u8 *)arg0 + 0x24));
}
