void sub_080C31E0(void *obj, u32 handler);

struct MainObj {
    u8 pad_0x00[0x24];
    u32 handler;                /* +0x24: saved update handler */
    u8 pad_0x28[0x08];
    void *children;             /* +0x30: head of the spawned-child list */
};

/* Once every spawned child is gone, resume the saved update handler. */
void sub_0809F330(struct MainObj *obj) {
    if (obj->children == 0) {
        sub_080C31E0(obj, obj->handler);
    }
}
