void sub_0800617C(void);

/* Free loaded resource slots, then mirror two runtime state halfwords into the
 * shared game state at +0x14DC and +0x14DE. */
void sub_08006234(void)
{
    sub_0800617C();
    {
        u8 *state = (u8 *)0x02025FF0;
        u16 *src1 = (u16 *)0x0200A278;
        u16 val1 = *src1;
        u32 off1 = 0x14DC;
        *(u16 *)(state + off1) = val1;
        {
            u16 *src2 = (u16 *)0x0200A27A;
            u16 val2 = *src2;
            u32 off2 = 0x14DE;
            *(u16 *)(state + off2) = val2;
        }
    }
}
