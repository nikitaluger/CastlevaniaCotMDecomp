extern void sub_080A02EC(void *);
extern void sub_080C31E4(void *, void *, s32);

/* If the entity's +0x74 flag is set, spawn the type-0x184 effect via
 * sub_080A02EC; then clear its current script slot flag and re-dispatch. */
void sub_0809F21C(void *self)
{
    if (*(u8 *)((u8 *)self + 0x74) != 0) {
        sub_080A02EC(self);
    }
    *(u8 *)((u8 *)self + *(s16 *)((u8 *)self + 0x22) * 2 + 0x19) = 0;
    {
        s32 *scriptArg = (s32 *)0x08671BB0;
        sub_080C31E4((u8 *)self + 0x18, (u8 *)self + 0x22, *scriptArg);
    }
}
