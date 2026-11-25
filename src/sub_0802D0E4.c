struct ScriptActor {
    u8 _0x00[0x14];
    u32 jumpTable;
    u8 _0x18[0x0A];
    s16 stepIndex;
    u32 field_0x24;
    u8 _0x28[0x10];
    u32 source;
    u32 actor;
};
struct MovingActor {
    u8 _0x00[0x08];
    s32 position;
    u8 _0x0C[0x04];
    u32 direction;
    u8 _0x14[0x34];
    s32 target;
};
extern void sub_08011368(void *, void *, s32, s32);
extern void sub_080C31E0(void *, void *);
extern void sub_080C31E8(void *, void *, s32, s32);
extern void *D_08671BD0;

/* Dispatch the current script command, then pick a movement direction from
 * the actor's position relative to its target and end the step. */
void sub_0802D0E4(struct ScriptActor *arg0)
{
    void *source;
    struct MovingActor *actor;
    u8 *status;
    u8 *scriptData;
    s32 stepOffset;
    s32 direction;

    source = (void *)arg0->source;
    actor = (struct MovingActor *)arg0->actor;
    status = (u8 *)actor + 0x34;
    sub_08011368(source, status, 0x5, 0);
    actor->direction = 0;
    arg0->jumpTable = 0x0866DB74;
    arg0->stepIndex += 1;
    ((u8 *)arg0)[arg0->stepIndex * 2 + 0x19]++;
    stepOffset = arg0->stepIndex * 2;
    scriptData = (u8 *)arg0 + 0x18;
    sub_080C31E0(arg0, *(void **)(arg0->jumpTable + *(u8 *)(scriptData + stepOffset) * 4));
    arg0->stepIndex -= 1;
    if (*status & 2) {
        if (actor->position > actor->target)
            direction = 0xFFFF3000;
        else
            direction = 0xD000;
        actor->direction = direction;
        ((u8 *)arg0)[arg0->stepIndex * 2 + 0x19] = 0;
        {
            void **lit = &D_08671BD0;
            sub_080C31E8(scriptData, (u8 *)arg0 + 0x22, 0, *lit);
        }
    }
}
