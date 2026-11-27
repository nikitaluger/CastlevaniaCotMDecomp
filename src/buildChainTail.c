void *spawnBudgetedEffect(void *, s32);   /* spawn an effect object */
void refreshMotionTrail(void *, void *);
s32 sub_080C31E0(s32, s32);        /* call the sine table entry */
s32 sub_080C3824(s32, s32);        /* unsigned divide */

/* Build an 8-segment chain/tail attached to the head object arg0: spawn the
 * segment objects (type 0x19B) for slots 0..6 and use the head itself for slot
 * 7, lay them out along an arc, store their per-segment phase, position and
 * sine-derived diagonal drift, then set the head's attack box at 0xA8..0xBC and
 * refresh it. */
/* Builds an 8-segment chain/tail on the head object: spawns 7 segment objects (type 0x19B) and uses the head for slot 7, lays them along an arc with per-segment phase/position/sine-drift, then sets the head's attack box at +0xA8..+0xBC and refreshes its motion trail. */ void buildChainTail(void *headObj, u8 *tailData) {
    s32 headX, angle, segX;
    u32 i;
    s32 segOff, headOff;
    u8 *alivePtr;
    void *segment;
    s32 sine;
    u8 *ptrBase, *headPtrBase, *xBase;
    s32 *angleTable, *angleTable2;
    u8 *vxBase, *vyBase;

    i = 0;
    segOff = 0;
    headOff = 0;
    headX = 0xFFF60000;
    alivePtr = tailData;
    angle = 0;
    segX = 0;
    do {
        if (i <= 6) {
            segment = spawnBudgetedEffect(headObj, 0x19B);
            ptrBase = tailData + 0x10;
            *(void **)(ptrBase + segOff) = segment;
            *alivePtr = 1;
            *((u8 *)(*(void **)(ptrBase + segOff)) + 0x4C) = i;
            xBase = tailData + 0xC;
            *(s32 *)(xBase + segOff) = segX;
            angleTable = (s32 *)((u8 *)tailData + 0x118);
            angleTable = (s32 *)((u8 *)angleTable + headOff);
            *angleTable = sub_080C3824(angle, 0x740000);
        } else {
            headPtrBase = tailData + 0x10;
            *(void **)(headPtrBase + segOff) = headObj;
            *alivePtr = 0;
            xBase = tailData + 0xC;
            *(s32 *)(xBase + segOff) = headX;
            angleTable2 = (s32 *)((u8 *)tailData + 0x118);
            angleTable2 = (s32 *)((u8 *)angleTable2 + headOff);
            *angleTable2 = 0x100;
        }
        sine = sub_080C31E0(0xE000, *(s32 *)0x08671BFC);
        vxBase = tailData + 4;
        *(s32 *)(vxBase + segOff) = i * (sine << 4);
        sine = sub_080C31E0(0xA000, *(s32 *)0x08671BFC);
        vyBase = tailData + 8;
        *(s32 *)(vyBase + segOff) = i * (sine << 4);
        segOff += 0x14;
        headOff += 4;
        headX += 0x120000;
        alivePtr += 0x14;
        angle += 0x12000000;
        segX += 0x120000;
        i++;
    } while (i <= 7);

    if (*(u8 *)((u8 *)headObj + 0x4C) == 0)
        *(s32 *)(tailData + 0xA8) = 0x4000;
    else
        *(s32 *)(tailData + 0xA8) = 0xFFFFC000;
    *(s32 *)(tailData + 0xAC) = 0xFFFF8000;
    *(s32 *)(tailData + 0xB0) = 0xC000;
    *(s32 *)(tailData + 0xB4) = 0;
    *(s32 *)(tailData + 0xB8) = 0;
    *(s32 *)(tailData + 0xBC) = 0;
    refreshMotionTrail(headObj, tailData);
}
