void sub_0808DC40(s32 x, s32 y, u16 param);
void sub_080C31E0(void *obj, u32 handler);

struct SubObj {
    u8 pad_0x00[0x08];
    s32 x;
    s32 y;
};

struct MainObj {
    u8 pad_0x00[0x22];
    s16 unk_0x22;
    u32 handler;                /* +0x24: current script handler */
    u8 pad_0x28[0x38 - 0x28];
    u32 unk_0x38;
    struct SubObj *sub;         /* +0x3C: position/physics sub-object */
};

/* Spawn the variant-2 effect at this object's position (parameter 8), then
 * dispatch the object's script handler. */
void sub_0802B128(struct MainObj *obj) {
    struct SubObj *sub = obj->sub;
    sub_0808DC40(sub->x, sub->y, 8);
    sub_080C31E0(obj, obj->handler);
}
