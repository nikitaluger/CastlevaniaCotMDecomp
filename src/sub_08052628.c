extern void sub_080C31E0(void *, void *);
extern void sub_080144D8(void *, void *);
extern void sub_080144FC(void *, void *);

/* Run one step of an actor's script: prepare its sprite, switch to the
 * 0x0866E65C command table, advance the script index (and that step's
 * repeat byte), dispatch the step's handler through the command table,
 * restore the index, then finish the sprite update. */
void sub_08052628(void *actor) {
    void *sprite = *(void **)((u8 *)actor + 0x38);
    sub_080144D8(actor, sprite);
    *(void **)((u8 *)actor + 0x14) = (void *)0x0866E65C;
    *(u16 *)((u8 *)actor + 0x22) = (u16)(*(u16 *)((u8 *)actor + 0x22) + 1);
    {
        u8 *step = (u8 *)((u32)(*(s16 *)((u8 *)actor + 0x22)) * 2 + (u32)actor);
        step[0x19] = (u8)(step[0x19] + 1);
        {
            s32 stepOffset = (*(s16 *)((u8 *)actor + 0x22)) * 2;
            u8 *script = (u8 *)actor + 0x18;
            u8 command = *(script + stepOffset);
            void **handlers = *(void **)((u8 *)actor + 0x14);
            void *handler = handlers[command];
            sub_080C31E0(actor, handler);
        }
    }
    *(u16 *)((u8 *)actor + 0x22) = (u16)(*(u16 *)((u8 *)actor + 0x22) - 1);
    sub_080144FC(actor, sprite);
}
