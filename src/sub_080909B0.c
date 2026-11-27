extern s32 isGameStatusFlagSet(u16);
extern void sub_080C31E4(void *, void *, s32);
struct Work { u8 pad[0x14]; s32 velocity; };
struct MoveState { u8 pad[0x10]; s16 active; };

/* When the movement-state flag test reports clear, give the work block a
 * +0x8000 X velocity, mark it active, clear the current script step byte and
 * dispatch the next script command. */
void sub_080909B0(void *entity) {
    struct Work *work = *(struct Work **)((u8 *)entity + 0x3C);
    struct MoveState *moveState = (struct MoveState *)((u8 *)work + 0x48);
    u8 zero = 0;
    if (isGameStatusFlagSet(*(u16 *)((u8 *)*(void **)((u8 *)moveState + 0x14) + 4)) == 0) {
        work->velocity = 0x8000;
        moveState->active = 1;
        ((u8 *)((u8 *)entity + (*(s16 *)((u8 *)entity + 0x22)) * 2))[0x19] = zero;
        {
            s32 *advanceCb;
            advanceCb = (s32 *)0x08671BB0;
            sub_080C31E4(entity + 0x18, entity + 0x22, *advanceCb);
        }
    }
}
