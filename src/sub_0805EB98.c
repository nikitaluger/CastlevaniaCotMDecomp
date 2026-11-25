void sub_080161F0(void);
void sub_080C31E0(void *, u32);

struct MainObj {
    u8 pad_0x00[0x3C];
    struct SubObj *sub;         /* +0x3C: state sub-object */
};

struct SubObj {
    u8 pad_0x00[0x24];
    u32 handler;                /* +0x24: script handler passed to sub_080C31E0 */
    u32 child;                  /* +0x28: child object unlinked when nonzero */
};

/* Dispatch this object's script handler, first unlinking a stale child object
 * recorded in its sub-object when one is present. */
void sub_0805EB98(struct MainObj *self) {
    struct SubObj *sub = self->sub;
    if (sub->child != 0) {
        sub_080161F0();
    }
    sub_080C31E0(self, sub->handler);
}
