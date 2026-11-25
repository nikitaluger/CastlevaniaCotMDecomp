extern vu32 D_02025FF0;

void sub_08011368(u32 scene, void *anim, u32 frame, u32 mode);
void sub_080C31E0(void *, u32);

struct MainObj {
    u8 pad_0x00[0x22];
    s16 scriptSlot;
    u32 callback;      /* per-frame script handler */
    u8 pad_0x28[0x38 - 0x28];
    u32 scene;
    u32 sub;           /* script/animation sub-object; its animation state is at +0x34 */
};

/* Start animation frame 0x34 on the entity's animation state and, when the
 * state's bit 1 is set afterwards, run the entity's script callback. */
void MainObj_CallUpdate2(struct MainObj *arg0) {
    u32 scene;
    u8 *state;

    scene = arg0->scene;
    state = (u8 *)arg0->sub + 0x34;
    sub_08011368(scene, state, 0x34, 0);
    if ((state[0] & 2) != 0) {
        sub_080C31E0(arg0, arg0->callback);
    }
}
