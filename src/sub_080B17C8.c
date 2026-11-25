extern u32 sub_080057F8(void);              /* pseudo-random number */
extern s32 sub_0800583C(s32);                /* random in [0, arg) */
extern void sub_08005FC4(s32, s32, s32, s32, void *);
extern void sub_0808DC40(s32, s32, s32);     /* spawn a particle at x, y */
extern void sub_08098428(s32, s32);          /* scale OBJ palettes by arg1/0x10000 */
extern s32 sub_080C31E0(s32, s32);           /* call the sine table entry */
extern void sub_080C31E4(void *, void *, s32);
extern s32 sub_080C0384;

/* Shared game state block: a state request at 0x10 and the current mode at 0x40. */
struct S_02025FF0 { u8 _0[0x10]; s32 state; u8 _14[0x2C]; s32 mode; };
extern struct S_02025FF0 D_02025FF0;

/* Update an expanding/rotating effect: drift the linked body sideways, fade its
 * palettes out, and while alive spray particles at random angles around it;
 * when the fade ends request state 8, and in mode 3 retune the audio player,
 * clear this effect's script byte and dispatch its next handler. */
void sub_080B17C8(void *arg0) {
    void *body = *(void**)((u8*)arg0+0x3C);
    void *fade = (u8*)body + 0x48;
    void *child = *(void**)((u8*)arg0+0x4C);
    s32 level;
    s32 *handlers;
    u8 zero;
    u8 *childAnim;
    if (2 & *((u8*)arg0 + *(s16*)((u8*)arg0+0x22)*2 + 0x19)) {
        *(s32*)((u8*)body+8) = *(s32*)((u8*)body+8) + 0x10000;
    } else {
        *(s32*)((u8*)body+8) = *(s32*)((u8*)body+8) + 0xFFFF0000;
    }
    sub_08098428(0x30, *(s32*)((u8*)fade+0x0C));
    level = *(s32*)((u8*)fade+0x0C) + 0xFFFFFEC0;
    *(s32*)((u8*)fade+0x0C) = level;
    if (level < 0) *(s32*)((u8*)fade+0x0C) = 0;
    if (*(s32*)((u8*)fade+0x0C) == 0 && *((u8*)fade+8) == 0) {
        *((u8*)fade+8) = 1;
        D_02025FF0.state = 8;
    }
    if (!(1 & *((u8*)arg0 + *(s16*)((u8*)arg0+0x22)*2 + 0x19))) {
        s32 spread = sub_0800583C(0x380000);
        u32 angle = sub_080057F8() & 0xFFFF;
        s32 *sinTable = (s32*)0x08671BFC;
        s32 x = *(s32*)((u8*)body+8) + ((spread >> 8) * (sub_080C31E0(angle + 0x4000, *sinTable) >> 8));
        sub_0808DC40(x, *(s32*)((u8*)body+0x0C) + ((spread >> 8) * (sub_080C31E0(angle, *sinTable) >> 8)) + 0x100000, 8);
    }
    if (D_02025FF0.mode == 3) {
        sub_08005FC4(0, 0x186, 3, 0, &sub_080C0384);
        childAnim = (u8*)child + 0x34;
        zero = 0;
        *childAnim = 1;
        *((u8*)arg0 + *(s16*)((u8*)arg0+0x22)*2 + 0x19) = zero;
        handlers = (s32*)0x08671BB0;
        sub_080C31E4((u8*)arg0+0x18, (u8*)arg0+0x22, *handlers);
    }
}
