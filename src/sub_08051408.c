extern s32 sub_08005820(s32);
extern void sub_080C31E0(void *, s32);
extern void sub_080C31E4(void *, void *, s32);

/* Give an entity a random diagonal velocity, then advance its state machine.
 * The motion state (via +0x3C) keeps vx/vy at +0x10/+0x14; sub_08005820 with
 * scale 0x28000 supplies the random magnitude, and the +0x6C flag flips vx.
 * Then reset the slot timer, dispatch the gMainObjTimerCallback callback, bump the timer,
 * and call the next handler from the function-pointer table at +0x14 indexed by
 * the slot byte at +0x18. */
void sub_08051408(void *entity) {
    void *state;
    s32 randomScale;
    s16 slotIndex;
    u8 *slotPtr;
    u32 *callbackTable;

    state = *(void **)((u8 *)entity + 0x3C);
    randomScale = 0x28000;
    *(s32 *)((u8 *)state + 0x10) = sub_08005820(randomScale) + 0x8000;
    *(s32 *)((u8 *)state + 0x14) = -(sub_08005820(randomScale) + 0x8000);
    if (*(u8 *)((u8 *)entity + 0x6C) & 1) {
        *(s32 *)((u8 *)state + 0x10) = -*(s32 *)((u8 *)state + 0x10);
    }
    slotIndex = *(s16 *)((u8 *)entity + 0x22);
    *(u8 *)((u8 *)entity + slotIndex * 2 + 0x19) = 0;
    callbackTable = (u32 *)0x08671BB0;
    slotPtr = (u8 *)entity + 0x18;
    sub_080C31E4(slotPtr, (u8 *)entity + 0x22, *callbackTable);
    slotIndex = *(s16 *)((u8 *)entity + 0x22);
    *(u8 *)((u8 *)entity + slotIndex * 2 + 0x19) += 1;
    slotIndex = *(s16 *)((u8 *)entity + 0x22);
    slotPtr += slotIndex * 2;
    {
        u8 next = *slotPtr;
        s32 *handlers = *(s32 **)((u8 *)entity + 0x14);
        sub_080C31E0(entity, handlers[next]);
    }
}
