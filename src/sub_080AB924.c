extern void sub_08005E80(s32);
extern void sub_080C31E0(void *, void *);
extern void sub_080C31E4(void *, void *, s32);

/* Spawn-step script callback: invoke the callback stored in each of the three
 * child objects, play sound 0x17C, then reset the script step and dispatch the
 * script handler and the next handler from the entity's function table. */
void sub_080AB924(void *actor) {
    u8 *self = (u8 *)actor;
    u8 *work = *(u8 **)(self + 0x3C);
    u32 i = 0;
    u8 **childList = (u8 **)(work + 0x68);
    u8 *stepPtr;
    s32 *dispatchArg;

    do {
        u8 *child = *childList++;
        sub_080C31E0(child, *(void **)(child + 0x24));
        i++;
    } while (i <= 2);
    sub_08005E80(0x17C);
    *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = 0;
    dispatchArg = (s32 *)0x08671BB0;
    stepPtr = self + 0x18;
    sub_080C31E4(stepPtr, self + 0x22, *dispatchArg);
    *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) += 1;
    stepPtr += *(s16 *)(self + 0x22) * 2;
    sub_080C31E0(self, *(void **)(*(u32 *)(self + 0x14) + *(u8 *)stepPtr * 4));
}
