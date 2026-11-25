s32 sub_08007E24(u16);
s32 sub_080C31E4(void *, void *, s32);

/* Advance an actor's animation-driven state: bump a work value on the
 * animation's final frame, and when its flag 2 is set mark a resource bit and
 * dispatch the next bytecode script command. */
void sub_080922D8(void *arg0)
{
    void *anim;
    void *work;

    work = *(void **)((u8 *)arg0 + 0x3C);
    anim = work + 0x24;
    if ((*(u8 *)((u8 *)anim + 1) == 1) && (*(s32 *)((u8 *)anim + 4) == (*(u16 *)((u8 *)anim + 2) - 1))) {
        *(s32 *)((u8 *)work + 0x10) = *(s32 *)((u8 *)work + 0x10) + 0x20000;
    }
    if ((*(u8 *)((u8 *)anim + 1) == 2) && (*(s32 *)((u8 *)anim + 4) == (*(u16 *)((u8 *)anim + 2) - 1))) {
        *(s32 *)((u8 *)work + 0x10) = *(s32 *)((u8 *)work + 0x10) + 0x20000;
    }
    if (2 & *(u8 *)((u8 *)anim + 0)) {
        sub_08007E24(**(u16 **)((u8 *)work + 0x20));
        *(s8 *)((u8 *)((u8 *)arg0 + (*(s16 *)((u8 *)arg0 + 0x22)) * 2) + 0x19) = 0;
        {
            s32 *commandIdPtr = (s32 *)0x08671BB0;
            sub_080C31E4((u8 *)arg0 + 0x18, (u8 *)arg0 + 0x22, *commandIdPtr);
        }
    }
}
