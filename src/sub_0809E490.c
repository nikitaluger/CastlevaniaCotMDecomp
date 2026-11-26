s32 signOf(s32);
s32 sub_080057F8(void);

struct S_02025FF0_174C {
    u8 pad[0x174C];
    s32 viewX;
    s32 viewY;
};
extern struct S_02025FF0_174C gMainWorkspace;

/* Pick a spawn point 0x480000 to the left or right of the view centre (a random
 * side when the entity is exactly centred) and 0x1C0000 above it, clamped to a
 * minimum y of 0x01080000. */
void sub_0809E490(void *arg0, s32 *arg1) {
    s32 side = signOf(*(s32 *)((u8 *)arg0 + 8));
    if (side == 0) {
        side = sub_080057F8() & 1;
        if (side == 0) {
            side = -1;
        }
    }
    arg1[0] = gMainWorkspace.viewX + side * 0x480000;
    arg1[1] = gMainWorkspace.viewY + 0xFFE40000;
    if (arg1[1] <= 0x0107FFFF) {
        arg1[1] = 0x01080000;
    }
}
