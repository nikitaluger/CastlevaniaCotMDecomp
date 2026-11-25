extern void *D_08671BD8;
extern void sub_0806AB04(void *, void *, void *, void *);
extern s32 sub_08003740(void *, void *);
extern u16 sub_08065CC8(void *, void *, void *, void *);
extern void sub_0806A884(void *, void *);
extern s32 sub_0806C4B4(void *, void *);
extern void sub_0806C5EC(void *, void *, void *, void *);
extern void sub_0806C6B0(void *, void *, void *, void *);
extern void *sub_0806D2A0(void *, s32, s32, s32);
extern void sub_0806D7B4(void *, s32);
extern void sub_08084CBC(void *, void *);
extern void sub_080C31E8(void *, void *, u16, s32);

/* Per-frame actor update: refresh camera/mode state and tick the actor's timer;
 * when the timer expires, spawn the cooldown effect and fire the type's
 * callback, then run the main object update. */
void sub_08065FCC(u8 *actor) {
    u8 *state = *(u8 **)(actor + 0x6C);
    u8 *objTail = state + 4;
    u8 *position = *(u8 **)(actor + 0x38);
    u8 *obj = objTail;
    s32 timerStatus;
    u8 *cooldown;
    s32 cooldownValue;
    void **callback;
    u8 *cbArgA;
    u8 *cbArgB;
    u16 callbackValue;
    if (sub_0806C4B4(obj, obj) == 0) {
        sub_0806C5EC(actor, position, obj, obj);
        sub_0806AB04(actor, position, obj, obj);
        sub_0806A884(position, obj);
        timerStatus = sub_08003740(state + 0x2C, position);
        if (timerStatus == 0) {
            void *spawned;
            sub_08084CBC(actor, obj);
            cooldown = state + 0xC4;
            cooldownValue = *(s32 *)cooldown;
            if (cooldownValue != 0) {
                sub_0806D7B4(obj, cooldownValue << 16);
                spawned = sub_0806D2A0(actor, 0x3C, 0xA, 0x12);
                if (spawned != 0) *(u16 *)((u8 *)spawned + 0x7C) = 1;
                *(s32 *)cooldown = timerStatus;
            }
            (actor + *(s16 *)(actor + 0x22) * 2)[0x17] = 0;
            callback = &D_08671BD8;
            cbArgA = actor + 0x18;
            cbArgB = actor + 0x22;
            callbackValue = sub_08065CC8(actor, position, objTail, obj);
            sub_080C31E8(cbArgA, cbArgB, callbackValue, *callback);
        }
        sub_0806C6B0(actor, position, objTail, obj);
    }
}
