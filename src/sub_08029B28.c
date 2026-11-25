s32 sub_0808DBF8(s32, s32, s32);
void sub_080C31E4(void *, void *, s32);

/* Spawn a level-8 effect at the work object's position while the current
 * script step counter is exactly 1; once that counter passes 5, reset it and
 * dispatch the next script step. */
void sub_08029B28(void *arg0)
{
    void *work;
    s32 *handlerTable;

    work = *((void **)((u8 *)arg0 + 0x3C));
    if (*((u8 *)(((*(s16 *)((u8 *)arg0 + 0x22)) * 2) + (u8 *)arg0) + 0x19) == 1)
    {
        sub_0808DBF8(*((s32 *)((u8 *)work + 8)), *((s32 *)((u8 *)work + 0xC)), 8);
    }
    if ((u32)(*((u8 *)(((*(s16 *)((u8 *)arg0 + 0x22)) * 2) + (u8 *)arg0) + 0x19)) > 5U)
    {
        *((u8 *)(((*(s16 *)((u8 *)arg0 + 0x22)) * 2) + (u8 *)arg0) + 0x19) = 0U;
        handlerTable = &(*((s32 *)0x08671BB0));
        sub_080C31E4((u8 *)arg0 + 0x18, (u8 *)arg0 + 0x22, *handlerTable);
    }
}
