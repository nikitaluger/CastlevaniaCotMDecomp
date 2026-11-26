struct S_02025FF0_174C { u8 pad[0x174C]; s32 playerX; };
extern struct S_02025FF0_174C gMainWorkspace;
extern s32 sub_080057F8(void);   /* pseudo-random generator */

/* Classifies the player's horizontal position into one of three zones (0..2).
 * Inside the two transition bands between zones a pseudo-random bit dithers the
 * result, so the caller's zone choice alternates evenly instead of snapping. */
s32 sub_080BE8D4(void) {
    s32 x = gMainWorkspace.playerX;
    if (x <= 0x67FFFF) return 0;
    if (x <= 0xCFFFFF) {
        if (sub_080057F8() & 1) return 0;
        return 1;
    }
    if (x <= 0x012FFFFF) return 1;
    if (x <= 0x0197FFFF) {
        if (sub_080057F8() & 1) return 1;
        return 2;
    }
    return 2;
}
