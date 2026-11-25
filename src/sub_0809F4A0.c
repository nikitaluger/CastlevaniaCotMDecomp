extern s32 sub_08013B5C(u32, u32);
extern void sub_080A05D0(u32, u32, u16, void *);
extern void sub_080A0638(void *, u32, u32);
extern s32 sub_080C31E0(void *, s32);
extern void sub_080C31E8(void *, void *, s32, s32);

/* Per-frame update for a six-slot formation: clear finished slots, run the entity's script
 * step, cache every slot's world position, arrange the slots on a circle around the entity
 * and aim each slot at its cached target. */
void sub_0809F4A0(u8 *entity)
{
    u32 sprite;
    u32 state;
    u32 slot;
    s32 stepOff;
    u8 *slots;
    u8 *slotPtr;
    u8 *script;
    u8 *flagPtr;
    u8 flag;
    u8 cmd;
    u16 *anglePtr;
    u16 *baseAnglePtr;
    s32 handled;
    u8 *xTargets;
    u8 *yTargets;
    u8 *yWrite;
    u8 *slotRead;
    u8 *xWrite;
    u8 *yRead;
    u8 *xRead;
    u8 *slotRead2;

    sprite = *(u32 *)(entity + 0x38);
    state = *(u32 *)(entity + 0x3C);
    slots = (u8 *)state + 0x48;

    if (*(u8 *)(entity + *(s16 *)(entity + 0x22) * 2 + 0x1A) != 0) {
        slot = 0;
        if (*(u32 *)slots == 0) {
            slotPtr = slots;
            do {
                slotPtr += 4;
                slot++;
                if (slot > 5) break;
            } while (*(u32 *)slotPtr == 0);
        }
        if (slot == 6) {
            u32 addr;
            *(u8 *)(entity + *(s16 *)(entity + 0x22) * 2 + 0x1B) = 0;
            addr = 0x08671BDC;
            sub_080C31E8(entity + 0x18, entity + 0x22, 0, *(u32 *)addr);
        }
    }

    {
        u8 *flagAddr = slots + 0x4F;
        flag = *flagAddr;
        flagPtr = flagAddr;
    }
    if (flag == 0 && *(u8 *)(entity + 0x6C) == 4) {
        u32 addr;
        *(u8 *)(entity + *(s16 *)(entity + 0x22) * 2 + 0x1B) = flag;
        addr = 0x08671BDC;
        sub_080C31E8(entity + 0x18, entity + 0x22, 5, *(u32 *)addr);
    }

    handled = sub_08013B5C(sprite, state);
    baseAnglePtr = (u16 *)(slots + 0x48);
    if (handled == 0) {
        u32 addr;
        *(u32 *)(entity + 0x14) = 0x0866FD90;
        *(s16 *)(entity + 0x22) = *(s16 *)(entity + 0x22) + 1;
        *(u8 *)(entity + (*(s16 *)(entity + 0x22)) * 2 + 0x19) += 1;
        stepOff = (*(s16 *)(entity + 0x22)) * 2;
        script = entity + 0x18;
        cmd = script[stepOff];
        sub_080C31E0(entity, *(u32 *)(*(u32 *)(entity + 0x14) + cmd * 4));
        *(s16 *)(entity + 0x22) = *(s16 *)(entity + 0x22) - 1;
        anglePtr = (u16 *)(slots + 0x4A);
        *anglePtr = *anglePtr + 0xD9;
        addr = 0x08671BFC;
        *baseAnglePtr = (sub_080C31E0((void *)(u32)*anglePtr, *(u32 *)addr) >> 6) + *baseAnglePtr;
    }

    slot = 0;
    xTargets = slots + 0x18;
    yTargets = slots + 0x30;
    yWrite = yTargets;
    slotRead = slots;
    xWrite = xTargets;
    do {
        u8 *child = *(u8 **)slotRead;
        slotRead += 4;
        *(u32 *)xWrite = *(u32 *)(child + 0x4C);
        xWrite += 4;
        *(u32 *)yWrite = *(u32 *)(child + 0x5C);
        yWrite += 4;
        slot++;
    } while (slot <= 5);

    sub_080A05D0(*(u32 *)(entity + 0x4C), *(u32 *)(entity + 0x5C), *(u16 *)(slots + 0x48), slots);

    if (*flagPtr != 0) {
        slot = 0;
        yRead = yTargets;
        xRead = xTargets;
        slotRead2 = slots;
        do {
            u8 *child = *(u8 **)slotRead2;
            slotRead2 += 4;
            {
                u32 targetX = *(u32 *)xRead;
                xRead += 4;
                sub_080A0638(child, targetX, *(u32 *)yRead);
            }
            yRead += 4;
            slot++;
        } while (slot <= 5);
    }
}
