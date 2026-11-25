void sub_080144D8(void *, void *);
void sub_080144FC(void *, void *);
void sub_080C31E0(void *, void *);

/* Script command: prepare the actor's sprite, install a new command-handler
 * table at +0x14, advance one step and dispatch its handler, then restore the
 * step counter and reposition/highlight the sprite on screen. */
void sub_08034AE8(void *actor) {
    void *sprite = *(void **)((u8 *)actor + 0x38);
    sub_080144D8(actor, sprite);
    *(void **)((u8 *)actor + 0x14) = (void *)0x0866DD84;
    *(u16 *)((u8 *)actor + 0x22) = (u16)(*(u16 *)((u8 *)actor + 0x22) + 1);
    {
        u8 *stepSlot = (u8 *)((u32)(*(s16 *)((u8 *)actor + 0x22)) * 2 + (u32)actor);
        stepSlot[0x19] = (u8)(stepSlot[0x19] + 1);
        {
            s32 stepOffset = (*(s16 *)((u8 *)actor + 0x22)) * 2;
            u8 *commandSlot = (u8 *)actor + 0x18;
            u8 commandId = *(commandSlot + stepOffset);
            void **commandTable = *(void ***)((u8 *)actor + 0x14);
            void *handler = commandTable[commandId];
            sub_080C31E0(actor, handler);
        }
    }
    *(u16 *)((u8 *)actor + 0x22) = (u16)(*(u16 *)((u8 *)actor + 0x22) - 1);
    sub_080144FC(actor, sprite);
}
