void sub_080C31E0(void *, void *);
void sub_080C31E8(void *, void *, s32, u32);

/* Count the control timer down; when it expires, play the owner's animation,
 * clear the current script byte and advance the command stream. */
void sub_0801AD84(void *arg0) {
    u8 *control;
    s32 timer;
    s32 commandIndex;
    s32 *handlerTable;
    void *owner;

    control = (u8 *)*(void **)((u8 *)arg0 + 0x3C) + 0x48;
    timer = *(u16 *)(control + 0x16) - 1;
    *(u16 *)(control + 0x16) = timer;
    if ((timer << 16) < 0) {
        owner = *(void **)((u8 *)arg0 + 0x30);
        if (owner != NULL) {
            sub_080C31E0(owner, *(void **)((u8 *)owner + 0x24));
        }
        commandIndex = *(s16 *)((u8 *)arg0 + 0x22);
        *(u8 *)((u8 *)arg0 + commandIndex * 2 + 0x17) = 0;
        handlerTable = (s32 *)0x08671BD8;
        sub_080C31E8((u8 *)arg0 + 0x18, (u8 *)arg0 + 0x22, 4, *handlerTable);
    }
}
