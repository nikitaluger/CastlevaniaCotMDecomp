extern void unlinkAndFreeObject(void);
extern void sub_080C31E0(void *, s32);

/* Release every non-null child object referenced by the 50 pointer slots at
 * work+0x4C, then chain to the entity's script callback. */
void sub_0809ACAC(void *arg0)
{
    s32 *slot;
    u32 i;
    void *work;

    work = *(void **)((u8 *)arg0 + 0x3C);
    i = 0;
    slot = (s32 *)((u8 *)work + 0x4C);
    do {
        if (*slot != 0) {
            unlinkAndFreeObject();
        }
        slot++;
        i++;
    } while (i <= 0x31);
    sub_080C31E0(arg0, *(s32 *)((u8 *)work + 0x24));
}
