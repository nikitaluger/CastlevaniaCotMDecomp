extern void sub_080C31E0(void *, void *);
extern void sub_080C31E4(void *, void *, s32);

struct SpriteFx {
    u16 a;
    u16 b;
    u8 pad[0x24];
    u16 c;
    u8 flags;
};

/* When the task's +0x7C flag is set, set the attached object's two halfword
 * parameters to 0x300 and set its 0x40 flag bit, then clear the step's
 * substate, run the script interpreter, advance it and dispatch the handler
 * for the new step. */
void sub_0809FDE4(void *arg0) {
    u8 *task = (u8 *)arg0;
    u8 *sprite = *(u8 **)(task + 0x38);

    if (*(u8 *)(task + 0x7C) != 0) {
        u8 *stepBase;
        s32 *scriptHandlers;
        u32 zero = 0;
        u16 val = 0x300;
        struct SpriteFx *fx = (struct SpriteFx *)sprite;

        *(u16 *)(sprite + 0x04) = val;
        *(u16 *)(sprite + 0x06) = val;
        fx->flags |= 0x40;

        *(u8 *)(task + *(s16 *)(task + 0x22) * 2 + 0x19) = zero;
        scriptHandlers = (s32 *)0x08671BB0;
        stepBase = task + 0x18;
        sub_080C31E4(stepBase, task + 0x22, *scriptHandlers);

        *(u8 *)(task + *(s16 *)(task + 0x22) * 2 + 0x19) += 1;
        stepBase = stepBase + *(s16 *)(task + 0x22) * 2;
        sub_080C31E0(arg0, *(void **)(*(u32 *)(task + 0x14) + *(u8 *)stepBase * 4));
    }
}
