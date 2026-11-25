/* When the transfer state sits at the handshake magic, advance it, stop the
 * two sound DMAs and zero-fill part of the transfer buffer via BIOS CpuSet. */
extern void sub_080C2F1C(void *, void *, void *);

void sub_080C09BC(void)
{
    u32 *transfer = *(u32 **)0x03007FF0;
    u32 state = transfer[0];
    if ((u32)(state + 0x978C92AD) <= 1) {
        u32 zero;
        transfer[0] = state + 10;
        *(vu16 *)0x040000C6 = 0;
        *(vu16 *)0x040000D2 = 0;
        zero = 0;
        sub_080C2F1C(&zero, (void *)((u8 *)transfer + 0x350), (void *)0x05000318);
    }
}
