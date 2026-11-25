/*
 * Script step waiting for input: while graphic 0x15B is not ready, do nothing;
 * once it is ready and A or B is pressed, clear the actor's work flag, release
 * graphic 0x159, clear the step's companion flag byte and jump the script to
 * step 0x10.
 */
extern s32 sub_08005F1C(s32 resource);  /* 1 when the resource is loaded */
extern s32 sub_08005E80(s32 resource);  /* release a resource */
extern void _call_via_r3(void *, void *, s32, s32);
extern u8 D_02021E90[];

void sub_0800B1D0(void *arg0) {
    u8 *self = (u8 *)arg0;
    u8 *work = *(u8 **)(self + 0x3C);
    s32 loadResult;
    u32 inputOffset = 0x146C;  /* pressed-key bits in the pad state: 1 = A, 2 = B */
    u16 input;
    s32 *stepCallback;
    u32 bMask;

    loadResult = sub_08005F1C(0x15B);
    if (loadResult == 0) {
        input = *(u16 *)(D_02021E90 + inputOffset);
        if ((1 & input) || (bMask = 2, bMask &= input, bMask)) {
            *(s8 *)(work + 0x635) = loadResult;
            sub_08005E80(0x159);
            *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x17) = loadResult;
            stepCallback = (s32 *)0x08671BD8;
            _call_via_r3(self + 0x18, self + 0x22, 0x10, *stepCallback);
        }
    }
}
