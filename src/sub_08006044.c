extern u8 D_00000009[];      /* address 9 doubles as the slot count */
extern u32 D_08106E38[];     /* id table immediately after the 9 slots */

/* Walk the nine fixed slots at 0x08106DCC and call the callback on each object
 * whose id differs from D_08106E38[arg1*2]; arg0 selects whether to pass arg3
 * too. (The twin sub_08005FC4 calls back on matching ids.) */
void sub_08006044(volatile s32 arg0, u16 arg1, s32 arg2, s32 arg3, void *arg4)
{
    u32 i;
    u32 *p;
    u32 limit;
    u16 t;
    u32 *idp;
    u32 a1;
    u32 *base;
    void (*f)(void *, s32, s32);

    f = arg4;
    i = 0;
    t = (u32)D_00000009;
    if (i < t) {
        a1 = (u16)arg1;
        base = D_08106E38;
        idp = base + a1 * 2;
        p = (u32 *)0x08106DCC;
        limit = t;
        do {
            void *object = (void *)*p;
            if (object) {
                if (*(u32 *)object != *idp) {
                    if (arg0) {
                        f(object, arg2, arg3);
                    } else {
                        ((void (*)(void *, s32))f)(object, arg2);
                    }
                }
            }
            p += 3;
            i++;
        } while (i < limit);
    }
}
