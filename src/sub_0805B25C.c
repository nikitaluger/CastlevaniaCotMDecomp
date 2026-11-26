extern void setAnimationFrame(s32 sprite, s32 anim, u16 frame, u8 mode);

struct AnimOwner {
    u8 _0[0x38];
    s32 sprite;
    s32 state;
};

/* Play frame 0x10 (mode 1) of the work-area animation owned by this entity. */
void sub_0805B25C(void *arg0) {
    struct AnimOwner *e = (struct AnimOwner *)arg0;

    setAnimationFrame(e->sprite, e->state + 0x34, 0x10, 1);
}
