void sub_080C31E4(void *, void *, s32);

/* When the entity's animation reaches frame 0x0A, clear the current script slot
 * and dispatch the next script command through the standard command table. */
void sub_08031740(void *entity) {
    u8 *work = *(void **)((u8 *)entity + 0x3C);
    u8 *anim = work + 0x34;
    if (anim[1] == 0xA) {
        *(u8 *)((u8 *)entity + (*(s16 *)((u8 *)entity + 0x22)) * 2 + 0x19) = 0;
        {
            s32 *commands;
            commands = (s32 *)0x08671BB0;
            sub_080C31E4(entity + 0x18, entity + 0x22, *commands);
        }
    }
}
