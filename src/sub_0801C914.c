void sub_080C31E4(void *, void *, u32);
void sub_08011368(u32, void *, u32, u32);

struct MainObj {
    u8 pad_0x00[0x22];
    s16 slot;
    u32 unk_0x24;
    u8 pad_0x28[0x38 - 0x28];
    u32 sprite;
    u32 work;
};

/* Main-object update: switch the animation to frame 0x2B, then, once the
 * current command slot's timer exceeds 30, reset it and dispatch the next
 * script command. */
void sub_0801C914(struct MainObj *arg0) {
    u8 *step;
    s16 idx;
    void *a;
    void *b;
    u32 *p;

    sub_08011368(arg0->sprite, (u8 *)arg0->work + 0x34, 0x2B, 1);
    idx = arg0->slot;
    step = (u8 *)((idx << 1) + (u32)arg0);
    if (step[0x19] > 0x1E) {
        step[0x19] = 0;
        p = (u32 *)0x08671BB0;
        a = (u8 *)arg0 + 0x18;
        b = (u8 *)arg0 + 0x22;
        sub_080C31E4(a, b, *p);
    }
}
