extern void freeMotionTracker(void *);
extern void unlinkAndFreeObject(void *);
extern void sub_080C31E0(void *, s32);

/* Release the two sub-objects owned by the block at state+0x34 (fields +4 and
 * +8) when present, then chain to the actor's update handler saved at
 * state+0x24. */
void sub_0808F590(void *arg0) {
    void *self = arg0;
    void *state = *(void **)((u8 *)self + 0x3C);
    void *res = (u8 *)state + 0x34;

    if (*(s32 *)((u8 *)res + 4) != 0) {
        freeMotionTracker(*(void **)((u8 *)res + 4));
    }
    if (*(s32 *)((u8 *)res + 8) != 0) {
        unlinkAndFreeObject(*(void **)((u8 *)res + 8));
    }
    sub_080C31E0(self, *(s32 *)((u8 *)state + 0x24));
}
