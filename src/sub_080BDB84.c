extern void allocWorkSlot(void *self, s32 kind, s32 id, s32 slot);
extern void sub_080C31E0(void *arg, void *func);
extern void sub_080C31E4(void *stepData, void *stepIndex, s32 callback);

/* Script step: attaches a kind-0x48 body object to slot 0, initialises the
 * script entity's counters and flags, then advances the script and dispatches
 * the next step. Falls back to the stored callback if no body was created. */
void sub_080BDB84(void *arg0) {
    u8 *self = arg0;
    u8 *body;
    u8 *stepData;
    s32 *scriptCb;
    u32 flagAddr, flagAddr2, stepOffset;
    s32 zero;
    allocWorkSlot(self, 0, 0x48, 0);
    body = *(u8 **)(self + 0x3C);
    if (body == NULL) {
        sub_080C31E0(self, *(void **)(self + 0x24));
        return;
    }
    zero = 0;
    *(u16 *)(body + 0x1C) = 0x68;
    *(u8 *)(self + 0x4C) = zero;
    *(u8 *)(self + 0x50) = zero;
    *(u8 *)(self + 0x54) = 0xFF;
    *(u32 *)(self + 0x5C) = 0x80 << 9;
    *(s32 *)(self + 0x6C) = -1;
    *(u16 *)(self + 0x2) |= 0x80 << 5;
    flagAddr = *(s16 *)(self + 0x22);
    flagAddr <<= 1;
    flagAddr += (u32)self;
    *(u8 *)(flagAddr + 0x19) = zero;
    scriptCb = (s32 *)0x08671BB0;
    stepData = self + 0x18;
    sub_080C31E4(stepData, self + 0x22, *scriptCb);
    flagAddr2 = *(s16 *)(self + 0x22);
    flagAddr2 <<= 1;
    flagAddr2 += (u32)self;
    *(u8 *)(flagAddr2 + 0x19) += 1;
    stepOffset = *(s16 *)(self + 0x22);
    stepOffset <<= 1;
    stepData += stepOffset;
    sub_080C31E0(self, *(void **)(*(u8 *)stepData * 4 + *(u32 *)(self + 0x14)));
}
