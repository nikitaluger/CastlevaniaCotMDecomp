extern u8 D_02021E90[];

/* Store the three layer parameters (0x1439..0x143B) of the map-command script
 * state kept in the graphics workspace. */
void sub_0805FE8C(u8 layer, u8 paramA, u8 paramB) {
    u8 *state = D_02021E90;
    state[0x1439] = layer;
    state[0x143A] = paramA;
    state[0x143B] = paramB;
}
