/* Play sound 0x189, spawn a falling effect at the entity's world position
 * (raised 4 pixels) with X velocity 8, then run the saved update handler. */
extern s32 sub_08005E80(s32 songId);
extern s32 sub_0808DBB4(s32 x, s32 y, s32 velX);
extern s32 sub_080C31E0(void *entity, s32 handler);

void sub_08047134(void *arg0) {
    u8 *work;

    work = *(u8 **)((u8 *)arg0 + 0x3C);
    sub_08005E80(0x189);
    sub_0808DBB4(*(s32 *)(work + 8), *(s32 *)(work + 0xC) + 0x40000, 8);
    sub_080C31E0(arg0, *(s32 *)((u8 *)arg0 + 0x24));
}
