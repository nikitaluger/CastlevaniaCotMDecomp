extern void sub_080C31E4(void *, void *, s32);
extern s32 gMainObjTimerCallback;

static inline u8 zero_byte(void) { u8 v = 0; return v; }
static inline u16 zero_half(void) { u16 v = 0; return v; }

/* Reset two u16 script-state fields (+0x12, +0x14) and the current command
 * byte, then invoke the gMainObjTimerCallback script-advance callback. */
void sub_080282BC(void *obj) {
    u8 *self = (u8 *)obj;
    u8 *script = *(u8 **)(self + 0x3C) + 0x48;
    s32 *lit;
    register u16 zero16 = zero_half();
    register u8 zero8 = zero_byte();

    *(u16 *)(script + 0x14) = zero16;
    *(u16 *)(script + 0x12) = zero16;
    *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = zero8;

    lit = &gMainObjTimerCallback;
    sub_080C31E4(self + 0x18, self + 0x22, *lit);
}
