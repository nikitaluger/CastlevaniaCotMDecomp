void sub_080C31E0(void *obj, u32 handler);

struct MainObj {
    u8 pad_0x00[0x22];
    s16 step;                   /* +0x22: current script step index */
    u32 handler;                /* +0x24: saved update handler */
};

/* If the current script step's action byte is 0x2A, dispatch the saved
 * update handler. */
void sub_080A99D0(struct MainObj *obj) {
    if (*(u8 *)((u8 *)obj + obj->step * 2 + 0x19) == 0x2A) {
        sub_080C31E0(obj, obj->handler);
    }
}
