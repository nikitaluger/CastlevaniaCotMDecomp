void sub_080B7298(void *obj);
void sub_080C31E0(void *obj, s32 handler);

struct MainObj {
    u8 pad_0x00[0x24];
    s32 handler;                /* +0x24: saved update handler */
};

/* Spawn the effect object at the parent's stored position, then dispatch the
 * entity's saved update handler. */
void sub_080B6740(struct MainObj *obj) {
    sub_080B7298(obj);
    sub_080C31E0(obj, obj->handler);
}
