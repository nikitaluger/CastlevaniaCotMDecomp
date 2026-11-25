extern void sub_08011368(void *, void *, s32, s32);
extern void sub_080C31E0(void *, s32);
extern void sub_080C31E4(void *, void *, s32);
extern void sub_08001480(void *, s32);
extern void sub_080113A8(void *, void *);
extern void sub_080415D4(s32, s32, void *, void *);

void sub_08029A7C(void *arg0) {
    u8 *r4 = (u8 *)arg0;
    u32 idx2;
    u8 *p18;
    sub_08011368(*(void **)(r4 + 0x38), *(void **)(r4 + 0x3C) + 0x34, 9, 1);
    *(u32 *)(r4 + 0x14) = 0x0866DA6C;
    *(u16 *)(r4 + 0x22) = (u16)(*(u16 *)(r4 + 0x22) + 1);
    *(u8 *)(r4 + *(s16 *)(r4 + 0x22) * 2 + 0x19) += 1;
    idx2 = (s32)*(s16 *)(r4 + 0x22) * 2;
    p18 = r4 + 0x18;
    sub_080C31E0(r4, *(void **)(*(u8 *)(p18 + idx2) * 4 + *(u32 *)(r4 + 0x14)));
    *(u16 *)(r4 + 0x22) = (u16)(*(u16 *)(r4 + 0x22) - 1);
}

/* Starts the animation in the object's current animation slot: sets up the
 * slot through the IWRAM helper, advances its frame counter and calls the
 * handler registered for the new frame. */
void sub_08040C70(void *obj) {
    void *started = obj + 0x74;
    u8 zero = 0;
    void *slot;
    const u32 *frameRoutine;
    *(u8 *)started = 1;
    *(u8 *)(obj + (s32)*(s16 *)(obj + 0x22) * 2 + 0x19) = zero;
    frameRoutine = (const u32 *)0x08671BB0;
    slot = obj + 0x18;
    sub_080C31E4(slot, obj + 0x22, *frameRoutine);
    *(u8 *)(obj + (s32)*(s16 *)(obj + 0x22) * 2 + 0x19) += 1;
    slot += (s32)*(s16 *)(obj + 0x22) * 2;
    sub_080C31E0(obj, *(u32 *)((u8 *)*(u32 *)((u8 *)obj + 0x14) + *(u8 *)slot * 4));
}

void sub_080412F8(void *arg0) {
    u8 *self = (u8 *)arg0;
    s32 r6 = *(s32 *)(self + 0x38);
    u8 *r7 = *(u8 **)(self + 0x3C);
    u8 *r4 = r7 + 0x34;
    s32 *lit;
    sub_080113A8((void *)r6, (void *)r4);
    if (*(u8 *)r4 & 2) {
        sub_080415D4(0, r6, (void *)r7, (void *)r4);
        *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = 0;
        lit = (s32 *)0x08671BB0;
        sub_080C31E4(self + 0x18, self + 0x22, *lit);
    }
}

void sub_080108FC(void *arg0) {
    u8 *self = (u8*)arg0;
    u8 *base18;
    s32 *lit;
    sub_08001480(self, 0x06);
    *(u8*)((s16)*(u16*)(self + 0x22) * 2 + self + 0x19) = 0;
    lit = (s32*)0x08671BB0;
    base18 = self + 0x18;
    sub_080C31E4(base18, self + 0x22, *lit);
    *(u8*)((s16)*(u16*)(self + 0x22) * 2 + self + 0x19) += 1;
    base18 += (s16)*(u16*)(self + 0x22) * 2;
    sub_080C31E0(self, *(u32*)(*(u32*)(self + 0x14) + *(u8*)base18 * 4));
}
