extern void setAnimationFrame(s32, void *, s32, s32);
extern s32 divInt32(s32, s32);
extern s32 sub_080C31E0(s32, s32);
extern void sub_080C31E4(void *, void *, s32);
extern u32 gTrigFuncTable;
extern u8 D_0866E750[];

/* Run one step of a scripted effect: set its animation frame and draw offset,
 * dispatch the current script command through the callback table, and end the
 * script when the render state goes negative. */
void sub_08055524(u8 *self) {
    s32 animCtrl;
    u8 *body;
    u8 *animState;
    u8 *render;
    u32 *table;
    s32 scriptIdx;
    s32 scriptIdx2;
    u8 *scriptBase;
    u8 scriptByte;
    s32 quotient;

    animCtrl = *(s32 *)(self + 0x38);
    body = *(u8 **)(self + 0x3C);
    animState = body + 0x34;
    render = body + 0x48;
    setAnimationFrame(animCtrl, animState, 4, 1);

    if (*(u8 *)(animState + 1) == 1 && *(s32 *)(animState + 4) == 1) {
        *(s16 *)(render + 4) = 0;
    }

    table = &gTrigFuncTable;
    quotient = divInt32((s32)*(s16 *)(render + 4) << 16, 0x3C);
    *(s32 *)render = sub_080C31E0(quotient + 0x8000, *table) * 2;

    *(u16 *)(render + 4) = *(u16 *)(render + 4) + 1;
    *(u32 *)(self + 0x14) = (u32)D_0866E750;
    *(u16 *)(self + 0x22) = *(u16 *)(self + 0x22) + 1;

    {
        u8 *p2 = (u8 *)((u32)(*(s16 *)(self + 0x22)) * 2 + (u32)self);
        p2[0x19] = (u8)(p2[0x19] + 1);
    }

    scriptIdx = *(s16 *)(self + 0x22);
    scriptIdx2 = scriptIdx * 2;
    scriptBase = self;
    scriptBase += 0x18;
    scriptByte = *(u8 *)((u32)scriptBase + (u32)scriptIdx2);
    sub_080C31E0((s32)self, *(u32 *)(*(u32 *)(self + 0x14) + scriptByte * 4));

    *(u16 *)(self + 0x22) = *(u16 *)(self + 0x22) - 1;

    if (*(s16 *)(render + 6) < 0) {
        scriptIdx = *(s16 *)(self + 0x22);
        *(u8 *)(self + scriptIdx * 2 + 0x19) = 0;
        {
            s32 *nv = (s32 *)0x08671BC0;
            sub_080C31E4(self + 0x18, self + 0x22, *nv);
        }
    }
}
