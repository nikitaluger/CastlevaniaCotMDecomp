void allocWorkSlot(void *, s32, s32, s32);
s32 sub_08005820(s32);
void sub_080C31E0(void *, void *);
void sub_080C31E4(void *, void *, s32);

/* Set up an entity from a source object: map the source's kind to a work type,
 * seed a randomized work parameter, reset the state timer and dispatch a state. */
void sub_0802A8CC(void *entity) {
    u8 *self = (u8 *)entity;
    void *source = *(void **)(self + 0xAC);
    void *work;
    void *workCheck;
    s32 zero;
    u32 *handlerSlot;
    u8 *stateByte;
    u8 *stateIdxPtr;
    allocWorkSlot(entity, 0, 4, 0);
    workCheck = *(void **)(self + 0x3C);
    if (workCheck == 0) {
        sub_080C31E0(entity, *(void **)(self + 0x24));
        return;
    }
    work = workCheck;
    {
        void *srcField = *(void **)((u8 *)source + 0x04);
        s32 kind = *(s16 *)((u8 *)srcField + 0x04);
        switch (kind) {
        case 0xBE: *(s16 *)work = 1; break;
        case 0xBF: *(s16 *)work = 2; break;
        case 0xC0: *(s16 *)work = 3; break;
        }
    }
    {
        u32 randVal = ((u32)(sub_08005820(0x3D) + 0xB4)) >> 3;
        zero = 0;
        *(s16 *)((u8 *)work + 0x02) = (s16)randVal;
    }
    *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = zero;
    handlerSlot = (u32 *)0x08671BB0;
    stateByte = self + 0x18;
    stateIdxPtr = self + 0x22;
    sub_080C31E4(stateByte, stateIdxPtr, *handlerSlot);
    *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) += 1;
    stateByte += *(s16 *)(self + 0x22) * 2;
    sub_080C31E0(self, *(void **)(*(u8 *)stateByte * 4 + *(u32 *)(self + 0x14)));
}
