extern void stepAnimationTrack(void *, void *);
extern void setObjectAnimationFrame(void *, void *, s32, s32);
extern void sub_080C31E4(void *, void *, s32);
extern s32 gMainObjTimerCallbacks;

/* Global list head held in the shared work area at offset 0x1870. */
struct WorkAreaList { u8 pad[0x1870]; void *head; };
extern struct WorkAreaList gMainWorkspace;

/* When the enemy's animation-control flags signal a spawn, set its fixed-point
 * motion values from script flags, advance the animation, link this object into
 * the global list and dispatch the spawn callback. */
void sub_0803AD60(u8 *self) {
    void *actor = *(void **)(self + 0x38);
    u8 *enemy = *(u8 **)(self + 0x3C);
    u8 *enemyData = enemy + 0x34;
    u8 *animData;
    void *listHead, *oldFirst;

    stepAnimationTrack(actor, enemyData);
    if (*(u8 *)enemyData & 2) {
        s32 zero;
        if (*(u8 *)(self + 0x80) != 0) {
            *(s32 *)(enemy + 0x10) = 0x80000;
        } else {
            *(s32 *)(enemy + 0x10) = 0xFFF80000;
        }
        if (*(u8 *)(self + 0x7C) == 2) {
            *(s32 *)(enemy + 0x14) = 0xFFFD0000;
        }
        setObjectAnimationFrame(actor, enemyData, 0x23, 1);
        animData = *(u8 **)(enemy + 0x28);
        zero = 0;
        *(u8 *)(animData + 1) = 1;
        {
            u8 *head = *(u8 **)(self + 0x28);
            u8 *first = *(u8 **)(head + 0x30);
            *(u32 *)(first + 0x2C) = zero;
        }
        listHead = gMainWorkspace.head;
        oldFirst = *(void **)((u8 *)listHead + 0x30);
        *(void **)(self + 0x2C) = oldFirst;
        *(void **)((u8 *)listHead + 0x30) = self;
        *(void **)(self + 0x28) = gMainWorkspace.head;
        *(u32 *)(self + 0x30) = zero;
        *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = zero;
        {
            s32 *pTable = &gMainObjTimerCallbacks;
            sub_080C31E4(self + 0x18, self + 0x22, *pTable);
        }
    }
}
