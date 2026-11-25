extern void sub_080C31E4(void *, void *, s32);

/* Update an effect sprite's attributes and animation table from its script
 * step flag, then advance the script when the flag reaches 0x40. */
void sub_0809DE9C(void *arg0)
{
    u8 *self = arg0;
    u8 *sprite = *(u8 **)(self + 0x38);
    u8 *step;
    s32 zero = 0;
    u16 tableValue;
    u16 *table;
    u8 stepFlag;
    u8 phase;

    if ((*(u8 *)((*(s16 *)(self + 0x22) * 2 + (s32)self) + 0x19) & 2) == 0)
        *(u16 *)sprite = (*(u16 *)sprite & 0xFFF) | 0xE000;
    *(u16 *)(sprite + 2) = zero | (*(u16 *)(sprite + 2) | 0x400);
    table = (u16 *)0x03000830;
    tableValue = 0x3F40;
    table[2] = tableValue;
    stepFlag = *(u8 *)((*(s16 *)(self + 0x22) * 2 + (s32)self) + 0x19);
    phase = stepFlag >> 2;
    table[3] = (phase << 8) | (0x10 - phase);
    *(u16 *)(sprite + 4) += 0x20;
    *(u16 *)(sprite + 6) -= 2;
    step = (u8 *)(*(s16 *)(self + 0x22) * 2 + (s32)self);
    if (*(u8 *)(step + 0x19) == 0x40)
    {
        *(u8 *)(step + 0x19) = zero;
        {
            s32 *scriptEvent = (s32 *)0x08671BB0;
            sub_080C31E4(self + 0x18, self + 0x22, *scriptEvent);
        }
    }
}
