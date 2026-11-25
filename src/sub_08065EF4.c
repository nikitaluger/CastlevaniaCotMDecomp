struct MoveParam { s32 increment; s32 maximum; u8 pad[0x50]; };
struct MoveParamTable { struct MoveParam entries[1]; };
extern struct MoveParamTable D_080E03A0;
extern void *D_08671BB0;
extern s32 sub_0806C4B4(void *, void *);
extern void sub_0806C5EC(void *, void *, void *, void *);
extern void sub_0806AB04(void *, void *, void *, void *);
extern void sub_08003740(void *, void *);
extern void sub_08003A6C(void *, s32, s32);
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
    if (sub_0806C4B4(obj, obj) == 0) {
        sub_0806C5EC(actor, position, obj, obj);
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
                sub_08003A6C(state + 0x2C, 0, 0x0846FEBC);
                (actor + *(s16 *)(actor + 0x22) * 2)[0x19] = (u8)timerVal;
                { void **callback = &D_08671BB0; sub_080C31E4(actor + 0x18, actor + 0x22, *callback); }
            }
        }
        sub_0806A884(position, obj);
        sub_08003740(objTail + 0x28, position);
        sub_0806C6B0(actor, position, objTail, obj);
    }
}
