/*
 * Global state-change check for an actor update: returns 0 while the actor may
 * update, 1 when the game asks to pause or leave (bit 0x80), and for the other
 * requests (bits 0x10, 0x20, 0x40) runs the actor's own interrupt handler and
 * returns -2, -3, -4.
 */
struct GameState {
    u8 _pad[0x14B8];
    u32 change;  /* bits 4..7: pending global state change */
};
extern struct GameState gMainWorkspace;

extern void sub_080C31E0(void *, s32);

s32 sub_0806D518(void *arg0) {
    u32 change = gMainWorkspace.change;
    if ((change & 0xF0) == 0) return 0;
    if (change & 0x80) return 1;
    if (change & 0x10) {
        sub_080C31E0(arg0, *(s32 *)((char *)arg0 + 0x24));
        return -2;
    }
    if (change & 0x20) {
        sub_080C31E0(arg0, *(s32 *)((char *)arg0 + 0x24));
        return -3;
    }
    if (change & 0x40) {
        sub_080C31E0(arg0, *(s32 *)((char *)arg0 + 0x24));
        return -4;
    }
    return 0;
}
