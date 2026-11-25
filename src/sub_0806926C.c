void sub_08003A6C(void *, u8, s32);

struct S_02025FF0 { u8 _0[0x24]; u32 modeFlags; u16 _28; u16 dirFlags; };
extern struct S_02025FF0 D_02025FF0;
extern u16 D_02021E90[];

/* Points the object's slot at +0x28 at one of three data tables, chosen by
 * the global direction flags, and records the chosen variant at +0x129. */
void sub_0806926C(u8 *arg0) {
    struct S_02025FF0 *gs;
    u32 modeFlags;
    u8 *obj = arg0;

    modeFlags = D_02025FF0.modeFlags;
    gs = &D_02025FF0;

    if (modeFlags != 0) {
        if (gs->dirFlags & 0x40) goto flag40;
        goto check80;
    } else {
        if (!(D_02021E90[0x146E / 2] & 0x40)) goto check80;
    }
flag40:
    sub_08003A6C(obj + 0x28, 0, 0x084FCABC);
    obj[0x129] = 0;
    return;
check80:
    if (gs->modeFlags != 0) {
        if (gs->dirFlags & 0x80) goto flag80;
        goto dflt;
    } else {
        if (!(D_02021E90[0x146E / 2] & 0x80)) goto dflt;
    }
flag80:
    sub_08003A6C(obj + 0x28, 0, 0x084FCAE8);
    obj[0x129] = 2;
    return;
dflt:
    sub_08003A6C(obj + 0x28, 0, 0x084FCA98);
    obj[0x129] = 1;
}
