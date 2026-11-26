extern void sub_080C2E68(void *, void *, u32);
extern u8 gCameraState[];

/* Build the option mask stored at out+0x38: OR the bit values {1,2,4,8} from
 * a table into 0x30 for each of four global flag words whose 0x2000 bit is
 * clear. */
void sub_0808D640(void *out) {
    u8 optionBits[4];
    u8 result = 0x30;
    volatile u16 *flag;
    u8 *state;
    u32 i;
    u32 disableMask;

    sub_080C2E68(optionBits, (void *)0x080F3E2C, 4);
    i = 0;
    state = gCameraState;
    disableMask = 0x80 << 6;
    flag = (u16 *)(state + (0x93 << 5));
    do {
        if (!(disableMask & *flag)) {
            result |= optionBits[i];
        }
        flag = (volatile u16 *)((u8 *)flag + 0x40);
        i++;
    } while (i <= 3);
    *(u8 *)((u8 *)out + 0x38) = result;
}
