extern void forceAnimationFrame(void *, void *, u16, u8);
extern void sub_080C31E0(void *, s32);
extern void sub_080C31E4(void *, void *, s32);

void pad_080B4F94(void *arg0) {
    u8 *self = arg0;
    u8 *sprite = *(u8 **)(self + 0x38);
    u8 *body = *(u8 **)(self + 0x3C);
    u8 *animData = body + 0x34;
    u8 *q = *(u8 **)(*(u8 **)(self + 0x28) + 0x3C);
    u8 state = *(u8 *)(self + 0x4C);
    if (state != 0) {
        u8 *highlight = sprite + 0x2A;
        u8 zero;
        u32 newHighlight = 0x40 | *highlight;
        *highlight = (u8)newHighlight;
        {
            u32 n = *(u32 *)(self + 0x5C);
            u32 tmp = *(u32 *)(q + 8) + ((n * 5) << 18);
            *(u32 *)(body + 8) = tmp + (((*(u16 *)(*(u8 **)(*(u8 **)(self + 0x28) + 0x38) + 2) & 0x10) != 0) ? 0x80000 : (u32)-0x80000);
        }
        *(u32 *)(body + 0x0C) = *(u32 *)(q + 0x0C);
        *(u8 *)(*(u8 **)(body + 0x28) + 1) = (zero = 0, 1);
        do { forceAnimationFrame(sprite, animData, 0x70, 0); } while (0);
        {
            s16 stepIndex = *(s16 *)(self + 0x22);
            *(u8 *)(self + stepIndex * 2 + 0x19) = zero;
            {
                s32 *scriptTable = (s32 *)0x08671BB0;
                u8 *stepData = self + 0x18;
                sub_080C31E4(stepData, self + 0x22, *scriptTable);
                stepIndex = *(s16 *)(self + 0x22);
                *(u8 *)(self + stepIndex * 2 + 0x19) += 1;
                stepIndex = *(s16 *)(self + 0x22);
                stepData += stepIndex * 2;
                sub_080C31E0(self, *(s32 *)(*(u32 *)(self + 0x14) + *(u8 *)stepData * 4));
            }
        }
    } else {
        *(u8 *)(sprite + 0x2A) &= 0xBF;
        *(u8 *)(*(u8 **)(body + 0x28) + 1) = state;
    }
}
