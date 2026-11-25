extern void sub_080C31E0(void *, s32);
extern void sub_08005E80(s32);
extern void sub_0808DC40(s32, s32, s32);

/* Command step: spawn a variant-2 effect at the actor's work position, nudging
 * y by 0x100000 when the direction flag at work+0x52 is set; play sound 0x88
 * and re-dispatch the script. */
void sub_0804A070(void *arg0)
{
    u8 *work;
    u8 *sub;
    u8 flag;
    s32 yOffset;

    work = *(u8 **)((u8 *)arg0 + 0x3C);
    sub = work + 0x48;
    flag = *(u8 *)(sub + 0x0A);
    yOffset = (-(s32)flag | flag) >> 31;
    yOffset &= 0x100000;
    sub_0808DC40(*(s32 *)(work + 8), *(s32 *)(work + 0x0C) + yOffset, 8);
    sub_08005E80(0x88);
    sub_080C31E0(arg0, *(s32 *)((u8 *)arg0 + 0x24));
}
