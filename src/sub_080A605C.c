/* Pick the facing/animation angle that best matches the direction from an
 * actor's tracker to its target, save it on the tracker, then run the current
 * script step. */
void sub_080A605C(void *arg0)
{
    u8 *entity = (u8 *)arg0;
    s32 matchedAngle;
    u8 *ai;
    u8 *indexPtr;
    s32 *angleTable;
    u32 actor;
    s32 angle;
    u8 *tableB;

    actor = *(u32 *)(entity + 0x3C);
    ai = (u8 *)(actor + 0x48);
    angle = sub_08005910(*(s32 *)(ai + 0x1C) - *(s32 *)(ai + 0x08),
                         *(s32 *)(ai + 0x18) - *(s32 *)(ai + 0x04));
    *(s32 *)(actor + 0x108) = angle & 0xFFFF;
    angleTable = (s32 *)0x08102030;
    indexPtr = entity;
    indexPtr += 0x4C;
    tableB = (u8 *)angleTable + 4;

    do {
        s32 angleDelta;
        angleDelta = *(s32 *)((u8 *)angleTable + (*indexPtr) * 8) - *(s32 *)(tableB + (*indexPtr) * 8);
        matchedAngle = sub_08005820(angleDelta) + *(s32 *)(tableB + (*indexPtr) * 8);
    } while (matchedAngle == angle);

    {
        s32 turnRate;
        s32 stepOffset;
        u8 *stepBase;
        u8 stepId;
        s32 *scriptCallbacks;

        turnRate = sub_0801473C(angle, matchedAngle);
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
