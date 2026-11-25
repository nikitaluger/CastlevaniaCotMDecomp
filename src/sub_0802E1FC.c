extern void sub_08011368(s32 sprite, s32 anim, u16 frame, u8 mode);

struct AnimOwner {
    u8 _0[0x38];
    s32 sprite;
    s32 state;
};

/* Play frame 9 (mode 1) of the work-area animation owned by this entity. */
void sub_0802E1FC(void *arg0) {
    struct AnimOwner *e = (struct AnimOwner *)arg0;

    sub_08011368(e->sprite, e->state + 0x34, 9, 1);
}
