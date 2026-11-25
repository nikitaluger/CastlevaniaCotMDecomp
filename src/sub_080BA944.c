void sub_080BB940(void *, void *);
s32 sub_08098754(void *);
void sub_080988B8(void *, s32);
void _call_via_r3(void *, void *, s32, s32);
void sub_080BB984(void *, void *);
void sub_080BB9C8(void *);
void sub_080BBA4C(void *);
void sub_080BBA08(void *);
void _call_via_r2(void *, void *, s32);

/* Track the mover's direction; when it finishes, reset the step byte and
 * advance the script through the alternate callback table. */
void sub_080BA7DA(void *arg0) {
    u8 *actor = (u8 *)arg0;
    void *work = *(void **)(actor + 0x3C);
    void *mover = *(void **)(actor + 0x4C);
    sub_080BB940(work, mover);
    if (sub_08098754(mover) != 0) {
        *(u8 *)(actor + *(s16 *)(actor + 0x22) * 2 + 0x17) = 0;
        {
            s32 *advanceCb;
            advanceCb = (s32 *)0x08671BD8;
            _call_via_r3(actor + 0x18, actor + 0x22, 0, *advanceCb);
        }
    }
}

/* Follow the mover, emit an effect while its flag is set, and restart the
 * script once the mover's state reaches 2. */
void sub_080BA944(void *arg0) {
    u8 *actor = (u8 *)arg0;
    void *work = *(void **)(actor + 0x3C);
    u8 *extra = (u8 *)work + 0x48;
    void *mover = *(void **)(actor + 0x4C);
    sub_080BB940(work, mover);
    if (*(s32 *)(extra + 0x64) != 0) {
        sub_080988B8(mover, *(s32 *)((u8 *)work + 8));
    }
    if (*(u8 *)((u8 *)mover + 0x25) == 2) {
        *(s32 *)(extra + 0x68) = 0;
        *(u8 *)(actor + *(s16 *)(actor + 0x22) * 2 + 0x19) = 0;
        {
            s32 *advanceCb;
            advanceCb = (s32 *)0x08671BB0;
            _call_via_r2(actor + 0x18, actor + 0x22, *advanceCb);
        }
    }
}

/* Tick the work extension, run step 0x0C's action, and restart the script at
 * sub-step 0x3C. */
void sub_080BA998(void *arg0) {
    u8 *actor = (u8 *)arg0;
    void *work = *(void **)(actor + 0x3C);
    sub_080BB984(work, (u8 *)work + 0x48);
    sub_080BB9C8(arg0);
    if (*(u8 *)(actor + *(s16 *)(actor + 0x22) * 2 + 0x19) == 0x0C) {
        sub_080BBA4C(arg0);
    }
    if (*(u8 *)(actor + *(s16 *)(actor + 0x22) * 2 + 0x19) == 0x3C) {
        *(u8 *)(actor + *(s16 *)(actor + 0x22) * 2 + 0x19) = 0;
        {
            s32 *advanceCb;
            advanceCb = (s32 *)0x08671BB0;
            _call_via_r2(actor + 0x18, actor + 0x22, *advanceCb);
        }
    }
}

/* Tick the work extension, run its action, and restart the script at sub-step
 * 0x18. */
void sub_080BACB0(void *arg0) {
    u8 *actor = (u8 *)arg0;
    void *work = *(void **)(actor + 0x3C);
    sub_080BB984(work, (u8 *)work + 0x48);
    sub_080BBA08(arg0);
    if (*(u8 *)(actor + *(s16 *)(actor + 0x22) * 2 + 0x19) == 0x18) {
        *(u8 *)(actor + *(s16 *)(actor + 0x22) * 2 + 0x19) = 0;
        {
            s32 *advanceCb;
            advanceCb = (s32 *)0x08671BB0;
            _call_via_r2(actor + 0x18, actor + 0x22, *advanceCb);
        }
    }
}
