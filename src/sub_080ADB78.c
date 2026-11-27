extern void sub_080B0698(void *, s32, s32, u16);
extern s32 sub_080C31E0(s32, s32);
extern void sub_080C31E8(void *, void *, s32, s32);
extern s32 gTrigFuncPtr;
extern u8 D_081022A0[];
extern s32 gScriptStepCallbacks;

/* Positions seven child objects around an origin using a trig function and a distance
 * table, then (at state 22) clears their flags and dispatches a completion handler. */
void sub_080ADB78(u8 *arg0) {
    u8 *self = arg0;
    void *state = *(void **)(self + 0x3C);
    void **objList = (void **)((u8 *)state + 0x48);
    s32 *trigSlot = &gTrigFuncPtr;
    s32 sinVal = sub_080C31E0(*(s32 *)(self + 0x6C), *trigSlot) >> 8;
    s32 cosVal = sub_080C31E0(*(s32 *)(self + 0x6C) + 0x4000, *trigSlot) >> 8;
    u32 i = 0;
    void **objPtr = objList;
    s16 animIndex;
    u8 stateByte;
    s32 steps, offset, radius, posX, posY;
    void *child;
    u16 angle;
    s32 a, b;
    u16 c;
    do {
        animIndex = *(s16 *)(self + 0x22);
        stateByte = self[animIndex * 2 + 0x19];
        steps = 0x16 - stateByte;
        offset = steps << 3;
        offset = offset - steps;
        offset = offset + i;
        offset = offset << 2;
        radius = *(s32 *)(D_081022A0 + offset) >> 8;
        a = *(s32 *)((u8 *)state + 0x08) + cosVal * radius;
        b = *(s32 *)((u8 *)state + 0x0C) + sinVal * radius;
        child = *objPtr;
        objPtr = objPtr + 1;
        c = (u16)*(s32 *)(self + 0x6C);
        sub_080B0698(child, a, b, c);
        i = i + 1;
    } while (i <= 6);
    animIndex = *(s16 *)(self + 0x22);
    if (self[animIndex * 2 + 0x19] == 0x16) {
        u8 *flag7C;
        s32 *handlerSlot;
        u8 *arg18;
        u8 *arg22;
        void **objIt;
        u8 zero;
        i = 0;
        flag7C = self + 0x7C;
        handlerSlot = &gScriptStepCallbacks;
        arg18 = self + 0x18;
        arg22 = self + 0x22;
        zero = 0;
        objIt = objList;
        do {
            void *p = *objIt;
            objIt = objIt + 1;
            *(u8 *)((u8 *)p + 0x90) = zero;
            i = i + 1;
        } while (i <= 6);
        *flag7C = 0;
        animIndex = *(s16 *)(self + 0x22);
        self[animIndex * 2 + 0x19] = 0;
        sub_080C31E8(arg18, arg22, 1, *handlerSlot);
    }
}
