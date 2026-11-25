/* Reset global work state: initialise the block at 0x020279D0, clear the six
 * status words at 0x02020BC0, and zero the two scratch buffers. */
extern void sub_080008A0(void *, s32);
extern vu32 D_02020BC0, D_02020BC4, D_02020BC8, D_02020BCC, D_02020BD0, D_02020BD4;

void sub_08016530(void)
{
    u8 *state = (u8 *)0x020279D0;
    u32 zero = 0;

    state[0] = 1;
    *(u16 *)(state + 2) = (u16)zero;
    state[1] = 0;
    *(u32 *)(state + 4) = zero;
    *(u32 *)(state + 8) = zero;

    D_02020BC0 = 0;
    D_02020BC4 = 0;
    D_02020BC8 = 0;
    D_02020BCC = 0;
    D_02020BD0 = 0;
    D_02020BD4 = 0;

    sub_080008A0((void *)0x020202C0, 0x500);
    sub_080008A0((void *)0x020207C0, 0x400);
}
