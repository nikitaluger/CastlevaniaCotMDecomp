/* Action-script state object used by the 0x080986xx helper family. */
struct ActionScriptState {
    u8 pad[0x14];
    s32 f14;
    s32 f18;
};

/* Set the two 32-bit fields at +0x14 and +0x18 of the action-script state. */
void sub_0809865C(struct ActionScriptState *state, s32 a14, s32 a18) {
    state->f14 = a14;
    state->f18 = a18;
}
