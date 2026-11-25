extern u8 D_080C98C0[];
extern u8 D_0200A268[];
extern u32 D_08106DCC[];
extern u8 D_00000009[];
extern void sub_080C0368(u32);

/* Releases loaded resource slots: for each entry whose ROM-side use flag and
 * runtime active flag are both set, free the resource and clear the active flag. */
void sub_0800617C(void)
{
    u32 slot;
    u32 *desc;
    u32 countLimit;
    u16 count;

    slot = 0;
    count = (u32)D_00000009;
    if (slot < count)
    {
        countLimit = count;
        desc = D_08106DCC;
        do
        {
            if (D_080C98C0[slot] != 0)
            {
                if (D_0200A268[slot] != 0)
                {
                    sub_080C0368(*desc);
                    D_0200A268[slot] = 0;
                }
            }
            desc += 3;
            slot++;
        }
        while (slot < countLimit);
    }
}
