extern u8 gCameraState[];

/* Store the three layer parameters (0x1439..0x143B) of the map-command script
 * state kept in the graphics workspace. */
void setMapLayerParams(u8 layer, u8 paramA, u8 paramB) {
    u8 *state = gCameraState;
    state[0x1439] = layer;
    state[0x143A] = paramA;
    state[0x143B] = paramB;
}
