extern void sub_08014DB4(void *, void *, s32, s32);
extern void sub_0801165C(void *, s32);
extern u8 gMainWorkspace[];

/* Steer the follow path at work+0xDC toward the shared player target, spin
 * the body by 0x800 of a 16-bit turn, then apply its velocity to its
 * position. */
void sub_080265DC(void *arg0) {
    u8 *work = *(u8 **)((u8 *)arg0 + 0x3C);
    u8 *motion = work + 0x48;
    u8 *body = work + 0xA8;
    u8 *path = work + 0xDC;
    u8 *base = gMainWorkspace;

    sub_08014DB4(body, path, *(s32 *)(base + 0x174C), *(s32 *)(base + 0x1750));
    *(u32 *)(motion + 0x18) = (*(u32 *)(motion + 0x18) + 0x800) & 0xFFFF;
    sub_0801165C(body, 0);
}
