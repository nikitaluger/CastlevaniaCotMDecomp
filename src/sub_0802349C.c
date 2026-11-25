void sub_08011368(void *, void *, s32, s32);
void sub_080C31E0(void *, void *);
s32 sub_08023F34(s32, s32, s32);
void sub_080C31E4(void *, void *, void *);
extern void *D_08671BB0;

/* Enter the next state of this object: give it its state-handler table, bump
 * the state index and that index's counter, then dispatch to the handler. */
void sub_0802349C(void *arg0) {
    u8 *obj = arg0;
    u8 arrOffset;
    s32 entryOff;
    sub_08011368(*(void **)(obj + 0x38), (u8 *)*(void **)(obj + 0x3C) + 0x34, 0, 0);
    *(u32 *)(obj + 0x14) = 0x0866D8B0;
    *(u16 *)(obj + 0x22) = *(u16 *)(obj + 0x22) + 1;
    ((u8 *)(obj + (*(s16 *)(obj + 0x22)) * 2))[0x19]++;
    entryOff = (*(s16 *)(obj + 0x22)) * 2;
    arrOffset = 0x18;
    sub_080C31E0(arg0, (void *)((u32 *)*(u32 **)(obj + 0x14))[((u8 *)(arrOffset + obj))[entryOff]]);
    *(u16 *)(obj + 0x22) = *(u16 *)(obj + 0x22) - 1;
}

/* Free the ten companion-effect slots held by this object's sub-object:
 * flag each live one as finished and clear its slot. */
void sub_080235C0(void *arg0) {
    s32 count;
    void **slot;
    void *effect;

    slot = (void **)(*(u32 *)((u8 *)arg0 + 0x3C) + 0x70);
    count = 9;
    do {
        effect = *slot;
        if (effect != NULL) {
            *(u16 *)((u8 *)effect + 0x6C) = (u16)(*(u16 *)((u8 *)effect + 0x6C) | 2);
            *slot = NULL;
        }
        slot += 1;
        count -= 1;
    } while (count >= 0);
}

/* State handler: restart both animations; if the effect spawn fails, fall
 * back to the object's base handler, otherwise reset to state 9 and dispatch. */
void sub_08023A7C(void *arg0) {
    u8 *obj = arg0;
    void *sub = *(void **)(obj + 0x3C);
    u8 *state = (u8 *)sub + 0x48;
    *((u8 *)*(void **)((u8 *)sub + 0x28) + 1) = 0;
    *((u8 *)*(void **)(state + 4) + 1) = 0;
    if (sub_08023F34(*(s32 *)((u8 *)sub + 8), *(s32 *)((u8 *)sub + 0xC), 1) == 0) {
        sub_080C31E0(arg0, *(void **)(obj + 0x24));
        return;
    }
    *(u16 *)(state + 2) = 9;
    *((u8 *)(obj + (*(s16 *)(obj + 0x22)) * 2) + 0x19) = 0;
    sub_080C31E4(obj + 0x18, obj + 0x22, D_08671BB0);
}

/* Leave this state: clear the busy flags on both animations and, when the
 * sub-object is flagged as finished, switch back to the base handler. */
void sub_08023B3C(void *arg0) {
    u8 *obj = arg0;
    void *sub = *(void **)(obj + 0x3C);
    u8 *flags = (u8 *)sub + 0x34;
    u8 *animA;
    u8 *animB;
    animA = *(u8 **)((u8 *)sub + 0x28);
    animA[1] &= 0xFB;
    animB = *(u8 **)((u8 *)sub + 0x4C);
    animB[1] &= 0xFE;
    if (flags[0] & 2) {
        sub_080C31E0(arg0, *(void **)(obj + 0x24));
    }
}
