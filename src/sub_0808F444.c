extern u8 D_0866F91C[];
void _call_via_r1(void *, void *);

/* Switch the entity to the command table at D_0866F91C, clear the work flag and
 * the sprite's 0x40 flag, then immediately run the new current step (the step
 * counter is bumped for the dispatch and restored afterwards). */
void sub_0808F444(void *arg0) {
    u8 *sprite = *(u8 **)((u8 *)arg0 + 0x38);
    u8 commandId;
    s16 stepIndex;
    s32 stepBaseOffset;
    s32 stepOffset;
    *(u8 *)(*(u8 **)(*(u8 **)((u8 *)arg0 + 0x3C) + 0x3C) + 1) = 0;
    *(u8 *)(sprite + 0x2A) &= 0xBF;
    *(u32 *)((u8 *)arg0 + 0x14) = (u32)D_0866F91C;
    *(u16 *)((u8 *)arg0 + 0x22) += 1;
    stepIndex = *(s16 *)((u8 *)arg0 + 0x22);
    *(u8 *)((u8 *)arg0 + stepIndex * 2 + 0x19) += 1;
    stepIndex = *(s16 *)((u8 *)arg0 + 0x22);
    stepBaseOffset = 0x18;
    stepOffset = stepIndex * 2;
    commandId = *(u8 *)((u8 *)arg0 + stepBaseOffset + stepOffset);
    _call_via_r1(arg0, *(void **)(commandId * 4 + *(void **)((u8 *)arg0 + 0x14)));
    *(u16 *)((u8 *)arg0 + 0x22) -= 1;
}
