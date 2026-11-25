void sub_08015974(void);
void sub_080C31E0(void *obj, s32 handler);

struct MainObj {
    u8 pad_0x00[0x3C];
    struct SubObj *sub;         /* +0x3C: state sub-object */
};

struct SubObj {
    u8 pad_0x00[0x1C];
    s32 handler;                /* +0x1C: script handler passed to sub_080C31E0 */
    s32 child;                  /* +0x20: linked child object released when nonzero */
};

/* Release the sub-object's linked child (if any), then dispatch its saved
 * script handler on this entity. */
void sub_080928FC(struct MainObj *self) {
    struct SubObj *sub = self->sub;
    if (sub->child != 0) {
        sub_08015974();
    }
    sub_080C31E0(self, sub->handler);
}
