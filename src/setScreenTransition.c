extern u8 gCameraState[];

/* Store the pending screen-transition byte (+0x143C) in the graphics workspace. */
void setScreenTransition(u8 value) {
    u8 *state = gCameraState;
    state[0x143C] = value;
}
