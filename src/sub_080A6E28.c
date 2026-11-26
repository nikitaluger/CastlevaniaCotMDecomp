extern s32 sub_080C31E0(s32, s32);
extern void sub_080C31E4(void *, void *, void *);
extern void sub_080A8940(void *, void *);
extern void sub_080A845C(void *, void *);
extern void *gMainObjTimerCallback;

/* Advances a sine-driven entity effect: derives X/Y offsets from a base angle
 * and the entity's per-state lifetime, sets a movement phase from that
 * lifetime, updates the target's facing/deceleration, and finishes by
 * dispatching an effect and clearing the lifetime once it reaches 0x5A. */
void sub_080A6E28(void *arg0) {
    u8 *entity = (u8 *)arg0;
    u8 *targetObj = *(u8 **)(entity + 0x38);
    u8 *state = *(u8 **)(entity + 0x3C);
    u8 *ctrl = state + 0x48;
    s32 angle = *(s32 *)(state + 0x108);
    u8 *angleB = (u8 *)angle + 0x5000;
    u32 *sinFunc = (u32 *)0x08671BFC;
    s32 angleA = angle + 0x9000;

    *(s32 *)(state + 0xFC) = (sub_080C31E0(angleA, *sinFunc) * *(u8 *)(entity + *(s16 *)(entity + 0x22) * 2 + 0x19)) >> 8;
    *(s32 *)(state + 0x100) = (sub_080C31E0((s32)angleB, *sinFunc) * *(u8 *)(entity + *(s16 *)(entity + 0x22) * 2 + 0x19)) >> 8;
    {
        u8 phase = *(u8 *)(entity + *(s16 *)(entity + 0x22) * 2 + 0x19);
        if (phase <= 0x11)
            *(u8 *)(state + 0xEE) = 0;
        else if (phase <= 0x1D)
            *(u8 *)(state + 0xEE) = 1;
        else
            *(u8 *)(state + 0xEE) = 2;
    }
    sub_080A8940(targetObj, ctrl);
    sub_080A845C(entity, ctrl);
    if (*(u8 *)(entity + *(s16 *)(entity + 0x22) * 2 + 0x19) == 0x5A) {
        u8 *ctrlFlag = ctrl + 0xA7;
        u32 zero = 0;
        *ctrlFlag = 1;
        *(u8 *)(entity + *(s16 *)(entity + 0x22) * 2 + 0x19) = (u8)zero;
        {
            void **effectTable = &gMainObjTimerCallback;
            u8 *msgArgs = entity + 0x18;
            sub_080C31E4(msgArgs, entity + 0x22, *effectTable);
        }
    }
}
