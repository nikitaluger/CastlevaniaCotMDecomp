extern void sub_080C31E0(void *, s32);
extern void sub_080144D8(void *, void *);
extern void sub_080144FC(void *, void *);

/* Script command: swap in the main step-handler table, run the next step once
 * (temporarily advancing the step index), then restore the index and refresh
 * the actor's sprite view. */
void sub_08041B88(void *actor) {
    void *view = *(void **)((u8 *)actor + 0x38);
    sub_080144D8(actor, view);
    *(void **)((u8 *)actor + 0x14) = (void *)0x0866E184;
    *(u16 *)((u8 *)actor + 0x22) = (u16)(*(u16 *)((u8 *)actor + 0x22) + 1);
    {
        u8 *step = (u8 *)((u32)(*(s16 *)((u8 *)actor + 0x22)) * 2 + (u32)actor);
        step[0x19] = (u8)(step[0x19] + 1);
        {
            s32 stepOff = (*(s16 *)((u8 *)actor + 0x22)) * 2;
            u8 *steps = (u8 *)actor + 0x18;
            u8 stepId = *(steps + stepOff);
            u8 **handlerTable = *(u8 **)((u8 *)actor + 0x14);
            void *handler = handlerTable[stepId];
            sub_080C31E0(actor, handler);
        }
    }
    *(u16 *)((u8 *)actor + 0x22) = (u16)(*(u16 *)((u8 *)actor + 0x22) - 1);
    sub_080144FC(actor, view);
}
