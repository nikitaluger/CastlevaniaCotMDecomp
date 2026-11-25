void sub_08098598(s32, void *, s32, void *);
void sub_080C31E0(void *, void *);

/* Restart the enemy's repeating sound effect, install action-script table
 * 0x0866FE38 on the object, bump the current sub-state's step counter and
 * dispatch that sub-state's handler, then restore the script pointer. */
void sub_080A0EB4(void *arg0)
{
    u8 *self = (u8 *)arg0;
    u8 *enemy = *(u8 **)(self + 0x3C);
    sub_08098598(0x170, enemy + 0x60, 0x0A, enemy + 0x64);
    *(u32 *)(self + 0x14) = 0x0866FE38;
    *(s16 *)(self + 0x22) = *(s16 *)(self + 0x22) + 1;
    *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) += 1;
    {
        s16 step = *(s16 *)(self + 0x22);
        struct S_18 { u8 pad[0x18]; u8 subState[0x200]; };
        u8 subState = ((struct S_18 *)self)->subState[step * 2];
        sub_080C31E0(self, *(void **)(*(u32 *)(self + 0x14) + subState * 4));
    }
    *(s16 *)(self + 0x22) = *(s16 *)(self + 0x22) - 1;
}
