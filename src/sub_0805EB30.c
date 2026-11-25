extern s32 sub_08007EA8(s32);
extern void sub_08007E24(s32);
extern void sub_0805F0C8(u16);
extern void sub_0805F104(u16, s32);
extern void sub_080C31E0(void *, s32);
extern u16 D_080D00BC[]; /* glyph tile ids */

/* Clear the entity's sprite highlight and pose, then spawn the glyph selected
 * by the entry in D_080D00BC (with tile 0x821D when the sprite slot is free)
 * and route to the handler held in slot 0x24. */
void sub_0805EB30(u8 *arg0)
{
    u8 *sprite = *(u8 **)(arg0 + 0x38);
    u8 *entry = arg0 + 0x4C;
    u8 *body = *(u8 **)(arg0 + 0x3C);
    u8 newFlags, zero;
    sprite += 0x2A;
    newFlags = *sprite & 0xBF;
    zero = 0;
    *sprite = newFlags;
    *(u8 *)(*(u8 **)(body + 0x28) + 1) = zero;
    if (sub_08007EA8(0xB1) == 0) {
        sub_0805F104(D_080D00BC[*(u16 *)(entry + 8)], 0x821D);
        sub_08007E24(0xB1);
    } else {
        sub_0805F0C8(D_080D00BC[*(u16 *)(entry + 8)]);
    }
    sub_080C31E0(arg0, *(s32 *)(arg0 + 0x24));
}
