extern s32 scaleByRandom(s32);
void sub_080C31E0(void *, s32);
void sub_080C31E4(void *, void *, s32);
struct WorkState { u8 pad[0xEC]; u16 flipFlags; };

/* AI script step: reset the work state's phase and sprite-flip flag, pick a small
 * random counter (2 or 3), set the motion state, then advance the script and
 * dispatch the next handler. */
void sub_080A5FD0(void *arg0) {
    u8 *self = (u8 *)arg0;
    u8 *sprite = *(u8 **)(self + 0x38);
    u8 *work = *(u8 **)(self + 0x3C);
    u8 *phase;
    u8 *stepBase;
    s32 *scriptTable;
    u32 randValue;

    phase = work;
    phase += 0xEE;
    *phase = 0;
    phase += 1;
    *phase = 2;
    ((struct WorkState *)work)->flipFlags = 0x10 & *(u16 *)(sprite + 2);
    randValue = scaleByRandom(2);
    randValue += 2;
    *(u8 *)(work + 0x121) = (u8)randValue;
    *(u32 *)(work + 0x114) = 0x60;
    *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = 0;
    scriptTable = (s32 *)0x08671BB0;
    stepBase = self + 0x18;
    sub_080C31E4(stepBase, self + 0x22, *scriptTable);
    *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) += 1;
    stepBase += *(s16 *)(self + 0x22) * 2;
    sub_080C31E0(self, *(s32 *)(*(u32 *)(self + 0x14) + *(u8 *)stepBase * 4));
}
