void sub_080C31E0(void *, void *);
extern u8 D_020278D0[];

/* Release the seven registered objects and clear their saved slots in the
 * scene state. */
void sub_0800D5B8(void) {
    u32 i = 0;
    void **slot;
    u8 *slots = D_020278D0;
    slot = (void **)((u32)slots + 0x48);
    do {
        void *obj = *slot;
        if (obj != 0) {
            sub_080C31E0(obj, *(void **)((u8 *)obj + 0x24));
        }
        slot++;
        i++;
    } while (i <= 6);
    {
        u8 *state = (u8 *)0x02021E90;
        state[0x1460] = 0;
        state[0x1464] = 0;
        state[0x1462] = 0;
        state[0x1466] = 0;
    }
}
