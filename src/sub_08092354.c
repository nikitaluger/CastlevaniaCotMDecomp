void sub_08015974(void);
void sub_080C31E0(void *obj, s32 handler);

struct MainObj {
    u8 pad_0x00[0x3C];
    struct SubObj *sub;         /* +0x3C: state sub-object */
};

struct SubObj {
    u8 pad_0x00[0x18];
    s32 handler;                /* +0x18: script handler passed to sub_080C31E0 */
    s32 child;                  /* +0x1C: child object unlinked when nonzero */
};

/* Dispatch this object's script handler, first unlinking a stale child object
 * recorded in its sub-object when one is present. */
void sub_08092354(struct MainObj *self) {
    struct SubObj *sub = self->sub;
    if (sub->child != 0) {
        sub_08015974();
    }
    sub_080C31E0(self, sub->handler);
}
