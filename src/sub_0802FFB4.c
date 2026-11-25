void sub_080C31E4(void *, void *, s32);

struct Timer { u8 _pad[0xC]; u16 count; };

/* Tick the entity's work countdown timer; when it expires, reset it to zero,
 * clear the current script step's progress byte and dispatch the next command. */
void sub_0802FFB4(void *arg0) {
    u8 *self = (u8 *)arg0;
    struct Timer *timer = (struct Timer *)(*(u8 **)(self + 0x3C) + 0x48);
    void **script;
    s32 count;
    u8 zero;

    count = timer->count - 1;
    timer->count = count;
    if ((s16)count <= 0) {
        zero = 0;
        timer->count = zero;
        zero = 0;
        *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = zero;
        script = (void **)0x08671BB0;
        sub_080C31E4(self + 0x18, self + 0x22, (s32)*script);
    }
}
