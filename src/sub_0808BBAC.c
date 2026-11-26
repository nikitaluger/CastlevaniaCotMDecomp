/* Block in the global game state where palette-effect requests are queued. */
struct S_02025FF0 {
    u8 pad[0x50];
};
extern struct S_02025FF0 gMainWorkspace;

/* Offsets of the palette-effect request fields inside gMainWorkspace. */
const u32 FX_EFFECT_OFF = 0x00001758;
const u32 FX_DURATION_OFF = 0x0000175C;
const u32 FX_TAIL_OFF = 0x00001764;

/* Queues a palette-effect request: records the three parameters in the request
 * block at gMainWorkspace+0x1758 and stores duration+1 in its trailing word. */
void sub_0808BBAC(u32 effect, u32 duration, u32 param) {
    const struct S_02025FF0 *state = &gMainWorkspace;

    *(u32 *)((u32)state + FX_EFFECT_OFF) = effect;
    *(u32 *)((u32)state + FX_DURATION_OFF) = duration;
    *(u32 *)((u32)state + FX_EFFECT_OFF + 0x08) = param;

    state = (const struct S_02025FF0 *)((u32)state + FX_TAIL_OFF);
    duration += 1;
    *(u32 *)state = duration;
}
