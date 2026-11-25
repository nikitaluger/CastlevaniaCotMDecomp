extern void sub_080C31E4(void *obj, s32 state, void *handler);

/* Initialize a falling-projectile object: start it at its target height, set
 * the fall limit to infinity, mark it active (flag 0x800), install the
 * falling-update handler at +0x14 and enter state 1. */
void sub_0808E6C0(void *obj)
{
    s32 flags;
    s32 state;

    *(u32 *)((u8 *)obj + 0x9C) = *(u32 *)((u8 *)obj + 0x5C);
    *(u32 *)((u8 *)obj + 0xAC) = 0x7FFFFFFF;
    flags = 0x800 | (*(u16 *)((u8 *)obj + 2));
    *(u16 *)((u8 *)obj + 2) = (u16)flags;
    *(void **)((u8 *)obj + 0x14) = (void *)0x0808E6F5;
    state = 1;
    *(u16 *)((u8 *)obj + 0x22) = (u16)state;
    sub_080C31E4(obj, state, (void *)0x0808E6F5);
}
