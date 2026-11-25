struct S02025FF0 { u8 _0[0x14A8]; u32 f14A8; u32 f14AC; };
extern struct S02025FF0 D_02025FF0;
struct S03000830 { u8 _0[4]; u16 f4; u16 f6; };
extern struct S03000830 D_03000830;
extern u8 D_02021E90[];
extern u32 D_08671BB0;

extern void sub_08005E80(u16);
extern void sub_0806C5EC(u8 *, u8 *, u8 *, u8 *);
extern void sub_0806C6B0(u8 *, u8 *, u8 *, u8 *);
extern void sub_080C31E4(u8 *, u8 *, u32);

/* Draw an object's sprite within the graphics pass; in one particular scene
 * state also update the display setup, play a sound and advance its script. */
void sub_08069A2C(u8 *obj) {
    struct S02025FF0 *state;
    u8 *gfxData;
    u8 *sprite;
    u32 worldBase;
    u32 *table;
    u32 zero;

    gfxData = *(u8 **)(obj + 0x6C) + 4;
    sprite = *(u8 **)(obj + 0x38);
    sub_0806C5EC(obj, sprite, gfxData, gfxData);

    state = &D_02025FF0;
    if (state->f14AC == 3) {
        struct S03000830 *display = &D_03000830;
        display->f4 = 0x1542;
        display->f6 = 0x1010;
        zero = 0;
        worldBase = (u32)D_02021E90;
        *(u32 *)(worldBase + 0x12BC) = 0x80 << 17;
        *(u16 *)(worldBase + 0x12A0) &= 0xBFFF;
        state->f14A8 = 0;
        sub_08005E80(0xDD << 1);
        *(u8 *)(obj + *(s16 *)(obj + 0x22) * 2 + 0x19) = zero;
        table = &D_08671BB0;
        sub_080C31E4(obj + 0x18, obj + 0x22, *table);
    }
    sub_0806C6B0(obj, sprite, gfxData, gfxData);
}
