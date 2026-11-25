extern u8 D_02021E90[];

/* Store the pending screen-transition byte (+0x143C) in the graphics workspace. */
void sub_0805FEB4(u8 value) {
    u8 *state = D_02021E90;
    state[0x143C] = value;
}
