struct S_02025FF0 { u8 _[0x189C]; u32 f; };
extern struct S_02025FF0 gMainWorkspace;
extern s16 D_080D002C[];
void setAnimationFrame(void *, s32, s16, s32);
void sub_080C31E0(void *, s32);

/* Update a timed effect: reset/clamp its counter from state flags, set sprite
 * scale from a table, decrement its timer, and invoke a callback when it expires. */
void sub_0805D6B4(void *self) {
    void *animCtrl;
    s32 animState;
    u8 *render;
    u8 *state16;
    s32 remaining;
    s16 remaining16;
    s32 zero;
    s32 scale;
    void *body;

    animCtrl = *(void **)((u8 *)self + 0x38);
    state16 = (u8 *)self + 0x4C;
    body = *(void **)((u8 *)self + 0x3C);
    animState = 0x34 + (s32)body;
    render = (u8 *)body + 0x48;
    if ((*(u16 *)((u8 *)body + 2) & 1) != 0) {
        *(s32 *)((u8 *)body + 0x10) = 0;
        if (*(s32 *)((u8 *)body + 0x14) < 0)
            *(s32 *)((u8 *)body + 0x14) = 0;
        else
            goto skip;
    }
    if (*(s32 *)((u8 *)body + 0x14) < 0 && (*(u16 *)((u8 *)body + 2) & 8) != 0)
        *(s32 *)((u8 *)body + 0x14) = 0;
skip:
    if ((*(u16 *)((u8 *)body + 2) & 4) != 0) {
        zero = 0;
        scale = 0x80 << 1;
        *(u16 *)((u8 *)animCtrl + 4) = scale;
        *(u16 *)((u8 *)animCtrl + 6) = scale;
        *(s32 *)((u8 *)body + 0x10) = zero;
        {
            s16 tableval = D_080D002C[*(u16 *)((u8 *)state16 + 8) & 0xF];
            setAnimationFrame(animCtrl, (void *)animState, tableval, 1);
        }
    }
    remaining = *(u16 *)((u8 *)render + 0) - 1;
    *(u16 *)((u8 *)render + 0) = remaining;
    remaining16 = (s16)remaining;
    if (remaining16 < 0) {
        sub_080C31E0(self, *(s32 *)((u8 *)self + 0x24));
        return;
    }
    if (remaining16 <= 0x77 && (gMainWorkspace.f & 1) != 0) {
        u8 *p = (u8 *)animCtrl + 0x2A;
        *p = 0xBF & *p;
    }
}
