void sub_080C0430(void);

/* Stop the sound engine's timer 1, then dispatch to the IWRAM-resident
 * routine at 0x030041D0. */
void sub_0800050C(void) {
    *(s32 *)0x04000104 = 0;
    sub_080C0430();
}
