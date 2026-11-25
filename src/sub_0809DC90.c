void sub_080A0204(s32, s32);
void sub_080A0294(s32);
void sub_080C31E0(void *, s32);
void sub_080C31E4(void *, void *, s32);

/* Tears down the actor's attached effect state: clears the attached object's
 * flag and the actor's timer, marks the linked object's state 4, releases the
 * two child objects through their own callbacks, clears the script action byte
 * and advances the script. */
void sub_0809DC90(void *arg0) {
    u8 *self = (u8 *)arg0;
    void *work = *(void **)(self + 0x3C);
    u8 *extra = (u8 *)work + 0x48;
    s32 zero;
    void *attached;
    void *childA;
    void *childB;
    s32 *scriptTable;
    attached = *(void **)((u8 *)work + 0x28);
    zero = 0;
    *(u8 *)((u8 *)attached + 1) = zero;
    *(s32 *)(self + 4) = zero;
    sub_080A0204(*(s32 *)(extra + 0x24), 4);
    *(s32 *)(extra + 0x24) = zero;
    sub_080A0294(*(s32 *)(extra + 0x20));
    childA = *(void **)(extra + 0x18);
    if (childA != NULL) sub_080C31E0(childA, *(s32 *)((u8 *)childA + 0x24));
    *(void **)(extra + 0x18) = NULL;
    childB = *(void **)(extra + 0x1C);
    if (childB != NULL) sub_080C31E0(childB, *(s32 *)((u8 *)childB + 0x24));
    *(void **)(extra + 0x1C) = NULL;
    *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = zero;
    scriptTable = (s32 *)0x08671BB0;
    sub_080C31E4(self + 0x18, self + 0x22, *scriptTable);
}
