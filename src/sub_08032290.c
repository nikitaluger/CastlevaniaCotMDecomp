void unlinkAndFreeObject(void);
void sub_080C31E0(void *obj, u32 handler);

struct SubObj {
    u8 pad_0x00[0x24];
    u32 handler;                /* +0x24: current script handler */
    u32 unk_0x28;               /* +0x28: cleanup-request flag */
};

struct MainObj {
    u8 pad_0x00[0x22];
    s16 unk_0x22;
    u32 unk_0x24;
    u8 pad_0x28[0x38 - 0x28];
    u32 unk_0x38;
    struct SubObj *sub;         /* +0x3C: position/script sub-object */
};

/* Per-frame update: run the object-list cleanup when the sub-object asks for
 * it, then dispatch the sub-object's script handler. */
void sub_08032290(struct MainObj *obj) {
    struct SubObj *sub = obj->sub;
    if (sub->unk_0x28 != 0) {
        unlinkAndFreeObject();
    }
    sub_080C31E0(obj, sub->handler);
}
