struct S_02025FF0_1750 { u8 pad[0x1750]; s32 playerY; };
extern struct S_02025FF0_1750 gMainWorkspace;
extern s32 sub_080057F8(void);   /* pseudo-random generator */

/* Classifies the player's vertical position into one of three zones (0..2).
 * Inside the two transition bands between zones a pseudo-random bit dithers the
 * result, so the caller's zone choice alternates evenly instead of snapping. */
s32 sub_080BE938(void) {
    s32 y = gMainWorkspace.playerY;
    if (y <= 0xF7FFFF) return 0;
    if (y <= 0x012FFFFF) {
        if (sub_080057F8() & 1) return 0;
        return 1;
    }
    if (y <= 0x016FFFFF) return 1;
    if (y <= 0x01A7FFFF) {
        if (sub_080057F8() & 1) return 1;
        return 2;
    }
    return 2;
}
