extern s32 scaleByRandom(s32);
extern s32 getAngleTurnDirection(s32, s32);
extern void sub_080C31E0(void *, s32);
extern void sub_080C31E4(void *, void *, s32);

/* Pick a renewed facing angle from the actor's angle-range table that differs
 * from its last chosen angle, save it and its turn direction on the actor's
 * tracker, then run the actor's current script step. */
void sub_080A6374(void *arg0)
{
    u8 *entity = (u8 *)arg0;
    s32 matchedAngle;
    u8 *ai;
    u8 *indexPtr;
    s32 *angleTable;
    s32 *desiredAngle;
    u32 actor;
    u8 *tableB;

    actor = *(u32 *)(entity + 0x3C);
    ai = (u8 *)(actor + 0x48);
    angleTable = (s32 *)0x08102074;
    indexPtr = entity;
    indexPtr += 0x4C;
    tableB = (u8 *)angleTable + 4;
    desiredAngle = (s32 *)(actor + 0x108);

    do {
        s32 angleDelta;
        angleDelta = *(s32 *)((u8 *)angleTable + (*indexPtr) * 8) - *(s32 *)(tableB + (*indexPtr) * 8);
        matchedAngle = scaleByRandom(angleDelta) + *(s32 *)(tableB + (*indexPtr) * 8);
    } while (matchedAngle == *(s32 *)(ai + 0xC0));

    {
        s32 turnRate;
        s32 stepOffset;
        u8 *stepBase;
        u8 stepId;
        s32 *scriptCallbacks;

        turnRate = getAngleTurnDirection(*desiredAngle, matchedAngle);
        *(s32 *)(ai + 0xC4) = matchedAngle;
        *(s32 *)(ai + 0xD0) = turnRate * 3;
        *(s32 *)(ai + 0xC8) = 0;
        *(u8 *)(ai + 0xD8) = 0;
        stepOffset = *(s16 *)(entity + 0x22) * 2;
        *(u8 *)((u32)stepOffset + (u32)entity + 0x19) = 0;
        scriptCallbacks = (s32 *)0x08671BB0;
        stepBase = entity;
        stepBase += 0x18;
        sub_080C31E4(stepBase, entity + 0x22, *scriptCallbacks);
        stepOffset = *(s16 *)(entity + 0x22) * 2;
        *(u8 *)((u32)stepOffset + (u32)entity + 0x19) = *(u8 *)((u32)stepOffset + (u32)entity + 0x19) + 1;
        stepOffset = *(s16 *)(entity + 0x22) * 2;
        stepBase += stepOffset;
        stepId = *stepBase;
        sub_080C31E0(entity, *(void **)(stepId * 4 + *(u32 *)(entity + 0x14)));
    }
}
