extern s32 allocWorkSlot(void *, s32, s32, s32);
extern s32 allocSpriteObject(void);
extern void sub_0806D2D0(void *);
extern void sub_080C31E0(void *, s32);
extern void sub_080C31E4(void *, void *, s32);

/* Spawns the entity's sprite: allocates its work slot and the visual object
 * (releasing the slot and aborting the script if that fails), then clears the
 * step byte, runs the script interpreter, advances the step byte and
 * dispatches the handler for the new step. */
void sub_0808B130(void *arg0)
{
    s32 sprite;
    s16 stepIndex;
    u8 *stepBase;
    s32 *scriptHandlers;

    if (allocWorkSlot(arg0, 0, 0x3C, 3) == 0) {
        sub_080C31E0(arg0, *(s32 *)((u8 *)arg0 + 0x24));
        return;
    }

    sprite = allocSpriteObject();
    if (sprite == 0) {
        sub_0806D2D0(arg0);
        return;
    }

    *(s32 *)((u8 *)arg0 + 0x38) = sprite;

    stepIndex = *(s16 *)((u8 *)arg0 + 0x22);
    *(u8 *)((u8 *)arg0 + stepIndex * 2 + 0x19) = 0;

    scriptHandlers = (s32 *)0x08671BB0;
    stepBase = (u8 *)arg0 + 0x18;
    sub_080C31E4(stepBase, (u8 *)arg0 + 0x22, *scriptHandlers);

    stepIndex = *(s16 *)((u8 *)arg0 + 0x22);
    *(u8 *)((u8 *)arg0 + stepIndex * 2 + 0x19) += 1;

    stepIndex = *(s16 *)((u8 *)arg0 + 0x22);
    stepBase += stepIndex * 2;
    {
        u8 step = *stepBase;
        s32 *handlers = *(s32 **)((u8 *)arg0 + 0x14);
        sub_080C31E0(arg0, handlers[step]);
    }
}
