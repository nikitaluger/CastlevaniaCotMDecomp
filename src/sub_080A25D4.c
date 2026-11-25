extern void sub_080161F0(void);
extern void sub_080C31E0(void *, s32);

/* Walk the child-pointer array at work+0x48, releasing any non-null entry,
 * then chain to the entity's script callback. */
void sub_080A25D4(void *arg0)
{
    s32 *slot;
    s32 i;
    void *work;

    work = *(void **)((u8 *)arg0 + 0x3C);
    i = 0;
    slot = (s32 *)((u8 *)work + 0x48);
    do {
        if (*slot != 0) {
            sub_080161F0();
        }
        slot++;
        i++;
    } while (i == 0);
    sub_080C31E0(arg0, *(s32 *)((u8 *)work + 0x24));
}
