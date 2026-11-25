extern void sub_080C31E0(void *a, void *b);
extern void sub_080161F0(void *a);

struct S_02025FF0 {
    u8 pad0[0x14EC];
    u8 state;
    u8 pad1[0x1780 - 0x14ED];
    u32 slotState[1];
};
extern struct S_02025FF0 D_02025FF0;

/* Clear the global state byte, unlink the group node this entity owns, zero
 * its per-slot state word (slot at +0xAC) and release the group's +0x18 node. */
void sub_0807199C(void *arg0)
{
    u8 *self = (u8 *)arg0;
    u8 *group = *(u8 **)(self + 0x6C) + 4;

    D_02025FF0.state = 0;
    sub_080161F0(*(void **)(group + 0x3C));
    *(&D_02025FF0.slotState[*(s32 *)(self + 0xAC)]) = 0;
    sub_080C31E0(arg0, *(void **)(group + 0x18));
}
