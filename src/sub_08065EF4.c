struct MoveParam { s32 increment; s32 maximum; u8 pad[0x50]; };
struct MoveParamTable { struct MoveParam entries[1]; };
extern struct MoveParamTable D_080E03A0;
extern void *gScriptStepCallbackTable;
extern s32 syncViewPosition(void *, void *);
extern void resetActionResultState(void *, void *, void *, void *);
extern void sub_0806AB04(void *, void *, void *, void *);
extern void stepDelayTimer(void *, void *);
extern void startEffectTimer(void *, s32, s32);
extern void sub_0806A884(void *, void *);
extern void sub_0806C6B0(void *, void *, void *, void *);
extern void sub_080C31E4(void *, void *, void *);

/* Per-frame actor update: refresh camera/mode state, tick the actor's timer,
 * accumulate its capped movement value, and on timer expiry reset its fields
 * and fire the actor type's init callback. */
void sub_08065EF4(u8 *actor) {
    u8 *state = *(u8 **)(actor + 0x6C);
    u8 *objTail = state + 4;
    u8 *position = *(u8 **)(actor + 0x38);
    u8 *obj = objTail;
    struct MoveParamTable *params;
    s32 timer, paramIndex, newSpeed, maxSpeed, timerVal;
    if (syncViewPosition(obj, obj) == 0) {
        resetActionResultState(actor, position, obj, obj);
        timer = *(s32 *)(obj + 0x10);
        if (timer != 0) *(s32 *)(obj + 0x10) = timer - 1;
        sub_0806AB04(actor, position, obj, obj);
        if (*(s32 *)(obj + 0x40) == 0) {
            params = &D_080E03A0;
            paramIndex = *(s32 *)(obj + 0x44);
            newSpeed = *(s32 *)(obj + 0x0C) + params->entries[paramIndex].increment;
            *(s32 *)(obj + 0x0C) = newSpeed;
            maxSpeed = params->entries[paramIndex].maximum;
            if (newSpeed > maxSpeed) *(s32 *)(obj + 0x0C) = maxSpeed;
        } else {
            timerVal = *(s32 *)(obj + 0x10);
            if (timerVal == 0) {
                *(s32 *)(obj + 8) = timerVal;
                *(s32 *)(obj + 0x0C) = timerVal;
                startEffectTimer(state + 0x2C, 0, 0x0846FEBC);
                (actor + *(s16 *)(actor + 0x22) * 2)[0x19] = (u8)timerVal;
                { void **callback = &gScriptStepCallbackTable; sub_080C31E4(actor + 0x18, actor + 0x22, *callback); }
            }
        }
        sub_0806A884(position, obj);
        stepDelayTimer(objTail + 0x28, position);
        sub_0806C6B0(actor, position, objTail, obj);
    }
}
