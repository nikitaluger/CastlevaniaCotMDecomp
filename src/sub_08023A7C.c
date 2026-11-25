void sub_080C31E0(void *, void *);
s32 sub_08023F34(s32, s32, s32);
void sub_080C31E4(void *, void *, u32);

/* State handler: restart both animations; if the effect spawn fails, fall
 * back to the object's base handler, otherwise reset to state 9 and dispatch. */
void sub_08023A7C(void *arg0) {
    u8 *obj = arg0;
    void *sub;
    u8 *state;
    u32 *handlerTable;
    u8 *ent;
    u8 zero;
    s16 idx;
    sub = *(void **)(obj + 0x3C);
    state = (u8 *)sub + 0x48;
    *(u8 *)((u8 *)*(void **)((u8 *)sub + 0x28) + 1) = 0;
    *(u8 *)((u8 *)*(void **)(state + 4) + 1) = 0;
    if (sub_08023F34(*(s32 *)((u8 *)sub + 8), *(s32 *)((u8 *)sub + 0xC), 1) == 0) {
        sub_080C31E0(arg0, *(void **)(obj + 0x24));
        return;
    }
    zero = 0;
    *(u16 *)(state + 2) = 9;
    idx = *(s16 *)(obj + 0x22);
    ent = (u8 *)((idx << 1) + (u32)obj);
    ent[0x19] = zero;
    handlerTable = (u32 *)0x08671BB0;
    sub_080C31E4(obj + 0x18, obj + 0x22, *handlerTable);
}
