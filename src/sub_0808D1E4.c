struct S_02025FF0 {
    u8 _0[0x14D8];
    s16 f14D8;
    s16 f14DA;
};
extern struct S_02025FF0 gMainWorkspace;
extern u8 gGameStatus[];
extern s32 isGameStatusFlagSet(s32);
extern s32 sub_08007E24(s32);
union U94 { u8 b; u16 h; };
struct S25368 { u8 _0[0x94]; union U94 f94; };

/* Reads the player's state value (byte/halfword at gGameStatus+0x94) and, for a few
 * specific states, sets a state flag or adjusts the global state halfwords at
 * +0x14D8/+0x14DA.
 */
void sub_0808D1E4(void) {
    struct S25368 *player = (struct S25368 *)gGameStatus;
    if (player->f94.b == 0) {
        if (isGameStatusFlagSet(0x33) == 0) gMainWorkspace.f14DA = 0x0E;
    }
    if (player->f94.b != 0) sub_08007E24(0x33);
    if (player->f94.h == 0x0307) {
        s32 check = isGameStatusFlagSet(0xB6);
        if (check == 0) gMainWorkspace.f14DA = (s16)check;
    }
    if (player->f94.h == 0x1507 && isGameStatusFlagSet(0xB6) != 0 && isGameStatusFlagSet(0xBD) == 0) {
        gMainWorkspace.f14D8 = 0xFFF6;
    }
    if (player->f94.h == 0x010D && isGameStatusFlagSet(0x34) != 0) {
        gMainWorkspace.f14DA = 3;
    }
}
