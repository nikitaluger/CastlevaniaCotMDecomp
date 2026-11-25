extern u8 D_02025FF0[];
void sub_080C31E4(void *, void *, s32);

/* Clears three words of the sub-object, sets the global flag bit 0x20000000,
 * clears the selected element's timer byte and fires the 0x08671BB0 callback. */
void sub_0808B33C(void *actor) {
    u8 *self;
    void *subObj;
    void *subObjTail;
    s32 zero;
    u8 *flagsBase;
    s32 flagOffset;
    u32 *flag;
    s32 *callbackTable;

    self = (u8 *)actor;
    subObj = *(void **)(self + 0x6C);
    subObjTail = (u8 *)subObj + 4;
    zero = 0;
    *(s32 *)((u8 *)subObj + 4) = 0;
    *(s32 *)((u8 *)subObjTail + 4) = 0;
    *(s32 *)((u8 *)subObjTail + 8) = 0;
    flagsBase = D_02025FF0;
    flagOffset = 0x1844;
    flag = (u32 *)(flagsBase + flagOffset);
    *flag |= 0x20000000;
    *(u8 *)(self + (*(s16 *)(self + 0x22)) * 2 + 0x19) = (u8)zero;
    callbackTable = (s32 *)0x08671BB0;
    sub_080C31E4(self + 0x18, self + 0x22, *callbackTable);
}
