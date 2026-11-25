void sub_080161F0(void);
void sub_080C31E0(void *obj, s32 handler);

struct MainObj {
    u8 pad_0x00[0x3C];
    struct SubObj *sub;         /* +0x3C: state sub-object */
};

struct SubObj {
    u8 pad_0x00[0x0C];
    s32 handler;                /* +0x0C: script handler passed to sub_080C31E0 */
    s32 child;                  /* +0x10: child object unlinked when nonzero */
};

/* Dispatch this object's script handler, first unlinking a stale child object
 * recorded in its sub-object when one is present. */
void sub_080915F4(struct MainObj *self) {
    struct SubObj *sub = self->sub;
    if (sub->child != 0) {
        sub_080161F0();
    }
    sub_080C31E0(self, sub->handler);
}
