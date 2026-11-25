struct DemoState { u8 pad[0xC]; u8 flags; };   /* +0xC: bit 7 = recording, low nibble = demo track+1 */
extern struct DemoState D_02025358;

struct InputState { u8 pad[0x10]; s32 scriptedInput; u8 pad2[0x10]; s32 useDemoInput; };
extern struct InputState D_02025FF0;

extern u32 sub_0808B3EC(u8 *recording);
extern u32 sub_0808B470(u8 *playback);
extern void sub_0808B5D8(void);

/* Per-frame demo input handler: while recording is enabled the current keys are
 * recorded; otherwise, when demo data exists, they are played back. Then the
 * global "demo input in use" flag is published and the pressed/held key state
 * is refreshed. */
void sub_0808B388(u8 *arg0) {
    struct DemoState *demo = &D_02025358;
    u8 *inputState = *(u8 **)((u8 *)arg0 + 0x6C) + 4;
    s32 useDemo;
    if ((!(demo->flags & 0x80)) || (sub_0808B3EC(inputState), ((demo->flags & 0x80) == 0))) {
        if (demo->flags != 0) {
            sub_0808B470(inputState);
        }
    }
    if ((D_02025FF0.scriptedInput != 0) || (((demo->flags & 0x80) == 0) && (demo->flags != 0))) {
        useDemo = 1;
    } else {
        useDemo = 0;
    }
    D_02025FF0.useDemoInput = useDemo;
    sub_0808B5D8();
}
