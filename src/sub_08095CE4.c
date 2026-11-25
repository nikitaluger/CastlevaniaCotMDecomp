void sub_080161F0(void);
void sub_080C31E0(void *obj, s32 handler);

struct MainObj {
    u8 pad_0x00[0x3C];
    struct SubObj *sub;
};

/* Sub-object of MainObj: a linked child object and the saved script handler. */
struct SubObj {
    u8 pad_0x00[0x24];
    s32 handler;
    s32 child;
};

/* Dispatch this object's script handler, first unlinking the stale child object
 * recorded in its sub-object when there is one. */
void sub_08095CE4(struct MainObj *self) {
    struct SubObj *sub = self->sub;

    if (sub->child != 0) {
        sub_080161F0();
    }
    sub_080C31E0(self, sub->handler);
}
