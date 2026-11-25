/* Child sprite/particle of a rotating effect: +0x5C is x, +0x6C is y and +0x7C
 * the 16-bit angle. */
struct RotatingChild {
    u8 pad[0x5C];
    s32 x;
    u8 pad60[0x6C - 0x60];
    s32 y;
    u8 pad70[0x7C - 0x70];
    s32 angle;
};

/* Position a child sprite at (x, y) with the given 16-bit angle. */
void sub_080B0698(struct RotatingChild *child, s32 x, s32 y, u16 angle) {
    child->x = x;
    child->y = y;
    child->angle = (s32)angle;
}
