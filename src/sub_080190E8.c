void setAnimationFrame(s32, void *, s32, s32);
void sub_080C31E4(void *, void *, s32);

/* Set the actor's model animation to frame 0x24; if the animator's finish
 * flag (bit 2 of the state at work+0x34) is set, clear this script step's flag
 * and advance the script through the handler at 0x08671BB0. */
void sub_080190E8(void *actor)
{
    void *sprite = *(void **)((u8 *)actor + 0x38);
    u8 *work = *(u8 **)((u8 *)actor + 0x3C);
    setAnimationFrame((s32)sprite, work + 0x34, 0x24, 0);
    if (2 & work[0x34]) {
        void **handlerTable;
        ((u8 *)((u8 *)actor + (*(s16 *)((u8 *)actor + 0x22)) * 2))[0x19] = 0;
        handlerTable = (void **)0x08671BB0;
        sub_080C31E4((u8 *)actor + 0x18, (u8 *)actor + 0x22, (s32)*handlerTable);
    }
}
