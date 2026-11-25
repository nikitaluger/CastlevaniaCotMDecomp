void sub_080C050C(s32 soundId);
void sub_080C31E0(void *obj, s32 handler);

struct SubObj {
    u8 pad_0x00[0x18];
    s32 handler;                /* +0x18: script handler */
};

struct MainObj {
    u8 pad_0x00[0x6C];
    struct SubObj *state;       /* +0x6C: state block (data begins at +4) */
};

/* Play sound effect 0x1C0, then dispatch the script handler stored in this
 * object's state block. */
void sub_0808AF6C(struct MainObj *self) {
    u8 *stateData = (u8 *)self->state + 4;
    sub_080C050C(0x1C0);
    sub_080C31E0(self, *(s32 *)(stateData + 0x18));
}
