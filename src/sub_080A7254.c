/* 0x080C31E0/E4/E8 are indirect-call thunks: the last argument is a function
 * pointer called with the preceding arguments (via r1/r2/r3). */
extern void _call_via_r2(void *, void *, s32);
extern void _call_via_r3(void *, void *, s32, s32);
extern void _call_via_r1(void *, s32);

/* At sub-step 0x1E, clear it and restart the actor's script. */
void sub_080A6F10(void *arg0) {
    u8 *actor = (u8*)arg0;
    if (*(u8*)(actor + *(s16*)(actor + 0x22) * 2 + 0x19) == 0x1E) {
        s32 *advanceCb;
        *(u8*)(actor + *(s16*)(actor + 0x22) * 2 + 0x19) = 0;
        advanceCb = (s32*)0x08671BB0;
        _call_via_r2(actor + 0x18, actor + 0x22, *advanceCb);
    }
}

/* At sub-step 0x1E, clear the step's command byte and restart via the
 * three-argument callback table. */
void sub_080A706C(void *arg0) {
    u8 *actor = (u8*)arg0;
    if (*(u8*)(actor + *(s16*)(actor + 0x22) * 2 + 0x19) == 0x1E) {
        s32 *advanceCb;
        *(u8*)(actor + *(s16*)(actor + 0x22) * 2 + 0x17) = 0;
        advanceCb = (s32*)0x08671BD8;
        _call_via_r3(actor + 0x18, actor + 0x22, 0, *advanceCb);
    }
}

/* Clear the work counter, restart the script, advance the sub-step by one and
 * dispatch the current script command from the actor's handler table. */
void sub_080A709C(void *arg0) {
    u8 *actor = (u8*)arg0;
    u8 *steps;
    s32 *advanceCb;
    *(u32*)((u8*)*(u32*)(actor + 0x3C) + 0x144) = 0;
    *(u8*)(actor + *(s16*)(actor + 0x22) * 2 + 0x19) = 0;
    advanceCb = (s32*)0x08671BB0;
    steps = actor + 0x18;
    _call_via_r2(steps, actor + 0x22, *advanceCb);
    *(u8*)(actor + *(s16*)(actor + 0x22) * 2 + 0x19) += 1;
    steps += *(s16*)(actor + 0x22) * 2;
    _call_via_r1(actor, *(u32*)(*(u32*)(actor + 0x14) + *(u8*)steps * 4));
}

/* Report the script sub-step as a coarse level (0/1/2) on the work object, and
 * restart the script when the sub-step reaches 0x2D. */
void sub_080A7254(void *arg0) {
    u8 *actor = (u8*)arg0;
    u8 *work = *(u8**)(actor + 0x3C);
    u8 subStep = *(u8*)(actor + *(s16*)(actor + 0x22) * 2 + 0x19);
    if (subStep <= 7) {
        *(u8*)(work + 0xEE) = 0;
    } else if (subStep <= 0x0F) {
        *(u8*)(work + 0xEE) = 1;
    } else {
        *(u8*)(work + 0xEE) = 2;
    }
    if (*(u8*)(actor + *(s16*)(actor + 0x22) * 2 + 0x19) == 0x2D) {
        s32 *advanceCb;
        *(u8*)(actor + *(s16*)(actor + 0x22) * 2 + 0x19) = 0;
        advanceCb = (s32*)0x08671BB0;
        _call_via_r2(actor + 0x18, actor + 0x22, *advanceCb);
    }
}
