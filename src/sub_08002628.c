void sub_080C31E0(void *, void *);
void sub_080C31E4(void *, void *, s32);

struct S_03000830 { u8 pad[8]; u16 counter; };
extern struct S_03000830 D_03000830;

/* Decrements a hardware counter by five; once it runs out, clears a flag,
 * fires a callback, advances to the next entry and calls its function pointer. */
void sub_08002628(void *obj) {
    u8 *self = (u8 *)obj;
    u8 *entry;
    s32 *callbackEntry;
    u16 v;

    v = D_03000830.counter;
    if (v <= 5) {
        u8 clearValue;
        D_03000830.counter = 0;
        clearValue = 0;
        *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = clearValue;
        callbackEntry = (s32 *)0x08671BB0;
        entry = self + 0x18;
        sub_080C31E4(entry, self + 0x22, *callbackEntry);
        *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) += 1;
        entry += *(s16 *)(self + 0x22) * 2;
        sub_080C31E0(obj, *(void **)((u8 *)*(u32 *)(self + 0x14) + *(u8 *)entry * 4));
    } else {
        D_03000830.counter = v - 5;
    }
}
