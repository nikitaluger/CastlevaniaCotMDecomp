extern void sub_08001738(void *objectList);
extern void sub_0808C18C(void);
extern void sub_080C31E4(void *, void *, s32);
extern u32 D_02025FF0[];
extern s32 D_08671BB0;

/* Finishes a stage/room: frees the two child-object lists, bumps the room
 * counter, and once the actor has no children left runs the palette/screen
 * transition, clears the script action byte and advances the script. */
void sub_08006F18(void *arg0)
{
    u8 *self = (u8 *)arg0;
    u32 offListA = 0x1854;
    u32 offListB = 0x1860;
    u32 offCounter = 0x1894;
    void *child;

    sub_08001738(*(void **)((u8 *)D_02025FF0 + offListA));
    sub_08001738(*(void **)((u8 *)D_02025FF0 + offListB));
    *(u32 *)((u8 *)D_02025FF0 + offCounter) += 1;

    child = *(void **)(self + 0x30);
    if (child == 0) {
        s32 zero = 0;
        s32 *advanceTable;
        sub_0808C18C();
        *(u8 *)(self + (*(s16 *)(self + 0x22) * 2) + 0x19) = zero;
        advanceTable = &D_08671BB0;
        sub_080C31E4(self + 0x18, self + 0x22, *advanceTable);
    }
}
