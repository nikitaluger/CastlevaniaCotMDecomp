extern void sub_0809BEB0(void);
extern u16 D_03000830[];

/* Actor step: while the script step is idle, write 0x3F40 and a packed value
 * ((byte at +0x60 << 8) | the decremented byte at +0x5C) to the global at
 * 0x03000830; when the countdown reaches 4, reset the step and install
 * sub_0809BEB0 as the next callback. */
void sub_0809BE60(void *arg0, u32 u1, u32 u2, u32 u3) {
    u16 step;
    u32 counter;
    D_03000830[2] = 0x3F40;
    step = 3 & *(u16 *)((u8 *)arg0 + 0x22);
    if (step == 0) {
        counter = *(u8 *)((u8 *)arg0 + 0x5C) - 1;
        *(u8 *)((u8 *)arg0 + 0x5C) = counter;
        D_03000830[3] = (*(u8 *)((u8 *)arg0 + 0x60) << 8) | *(u8 *)((u8 *)arg0 + 0x5C);
        if ((u8)counter == 4) {
            *(u16 *)((u8 *)arg0 + 0x22) = step;
            *(u32 *)((u8 *)arg0 + 0x14) = (u32)&sub_0809BEB0;
        }
    }
}
