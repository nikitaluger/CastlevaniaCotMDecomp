void sub_080C31E0(void *, void *);

/* Enter level 0 of the script table at 0x0866F990: stop the running
 * animation, install the level table, step the script index and its per-step
 * counter, run the level's handler, then restore the index. */
void sub_08090E10(void *arg0)
{
    u8 *self = (u8 *)arg0;
    u8 *stepPtr;
    u8 *cmdPtr;
    u8 cmd;
    u32 cmdOffset;
    u32 stepOffset;
    *(u8 *)(*(void **)(*(void **)(self + 0x3C)) + 1) = 0;
    *(u32 *)(self + 0x14) = 0x0866F990;
    *(u16 *)(self + 0x22) = *(u16 *)(self + 0x22) + 1;
    stepOffset = (u32)*(s16 *)(self + 0x22) * 2;
    stepPtr = (u8 *)(stepOffset + (u32)self);
    *(u8 *)(stepPtr + 0x19) += 1;
    cmdOffset = (u32)*(s16 *)(self + 0x22) * 2;
    cmdPtr = self + 0x18;
    cmdPtr = cmdPtr + cmdOffset;
    cmd = *cmdPtr;
    sub_080C31E0(arg0, *(void **)((u8 *)*(u32 *)(self + 0x14) + (u32)cmd * 4));
    *(u16 *)(self + 0x22) = *(u16 *)(self + 0x22) - 1;
}
