extern void sub_080C31E4(void *, void *, void *);
extern void sub_080C31E0(void *, void *);
extern void *D_08671BB0;

/* Returns zero; kept as a helper so the compiler materialises the constant at
 * the point the original code did. */
static inline u8 zeroByte(void) { u8 v = 0; return v; }

/* Wait step: counts the shared delay slot D_03000830[4] down and, when it hits
 * zero, clears the step byte, runs the script interpreter, advances the step
 * and dispatches the next handler. */
void sub_0800223C(void *entity)
{
    u16 *timer;
    u32 left;
    s16 stepIndex;
    u8 *stepPtr;
    u8 *stepBase;
    void **interpreter;

    timer = (u16 *)0x03000830;
    left = timer[4] - 1;
    timer[4] = left;
    if (((u32)left << 16) != 0)
        return;

    stepIndex = *(s16 *)((u8 *)entity + 0x22);
    stepPtr = (u8 *)((stepIndex * 2) + (u32)entity) + 0x19;
    *stepPtr = zeroByte();
    interpreter = &D_08671BB0;
    stepBase = (u8 *)entity + 0x18;
    sub_080C31E4(stepBase, (u8 *)entity + 0x22, *interpreter);
    stepIndex = *(s16 *)((u8 *)entity + 0x22);
    *(u8 *)((u8 *)entity + stepIndex * 2 + 0x19) += 1;
    stepIndex = *(s16 *)((u8 *)entity + 0x22);
    stepBase += stepIndex * 2;
    {
        u8 step = *stepBase;
        void **handlers = *(void ***)((u8 *)entity + 0x14);
        sub_080C31E0(entity, handlers[step]);
    }
}
