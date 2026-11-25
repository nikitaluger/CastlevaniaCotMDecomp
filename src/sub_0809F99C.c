void sub_080C31E0(void *obj, u32 handler);

struct WorkState {
    u8 _0[0x97];
    u8 teardown;                /* +0x97: set when the work state is torn down */
};

struct MainObj {
    u8 pad_0x00[0x24];
    u32 handler;                /* +0x24: saved update handler */
    u8 pad_0x28[0x14];
    struct WorkState *work;     /* +0x3C: work state */
};

/* Clear the work state's teardown flag, then dispatch the saved update handler. */
void sub_0809F99C(struct MainObj *obj) {
    obj->work->teardown = 0;
    sub_080C31E0(obj, obj->handler);
}
