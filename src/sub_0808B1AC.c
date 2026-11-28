extern void startEffectTimer(void *a, s32 b, void *c);
extern void sub_080C31E0(void *a, void *b);
extern void sub_080C31E4(void *a, void *b, void *c);
extern s32 signedRemainder(s32 a, s32 b);
extern u32 gMainObjTimerCallbacks;
extern u8 D_080E6974[];
extern u32 D_080E6940[];
extern u8 D_08453FA0[];

/* Sets up an entity's appearance from a four-entry config table and a color
 * table, then runs the first step of its script/behavior table. */
void sub_0808B1AC(void *entity) {
    u8 *self;
    u8 *stateBlock;
    u8 *state;
    u8 *gfx;
    u8 *idPtr;
    s32 id;
    s32 entryOffset;
    u8 *entry;
    u32 *colorTable;
    s32 colorIdx;
    s16 actionIdx;
    u32 *pAnimStep;
    u8 *stepBase;
    s16 nextIdx;
    u8 stepByte;
    void **handlerTable;

    self = (u8 *)entity;
    stateBlock = *(u8 **)(self + 0x6C);
    state = stateBlock + 4;
    gfx = *(u8 **)(self + 0x38);
    idPtr = self + 0x9C;
    id = *(s32 *)idPtr & 3;
    entryOffset = id;
    entryOffset = (entryOffset << 1) + id;
    entryOffset = entryOffset << 2;
    entry = (u8 *)D_080E6974 + entryOffset;

    *(u32 *)(gfx + 0x24) = (u32)D_08453FA0;
    startEffectTimer(stateBlock + 0x20, 0, *(void **)(entry + 8));

    colorTable = D_080E6940;
    colorIdx = signedRemainder(*(s32 *)idPtr, 0x0D);
    *(u32 *)(gfx + 0x14) = colorTable[colorIdx];
    *(u32 *)(gfx + 0x18) = 0x80 << 12;

    *(u32 *)(state + 0x34) = *(u32 *)(entry + 4);
    *(u32 *)(state + 0x0C) = *(u32 *)(entry + 0);

    actionIdx = *(s16 *)(self + 0x22);
    *(self + actionIdx * 2 + 0x19) = 0;

    pAnimStep = &gMainObjTimerCallbacks;
    stepBase = self + 0x18;
    sub_080C31E4(stepBase, self + 0x22, (void *)*pAnimStep);

    nextIdx = *(s16 *)(self + 0x22);
    (*(u8 *)(nextIdx * 2 + self + 0x19))++;
    nextIdx = *(s16 *)(self + 0x22);
    stepBase = stepBase + nextIdx * 2;
    stepByte = *stepBase;
    handlerTable = *(void ***)(self + 0x14);
    sub_080C31E0(self, handlerTable[stepByte]);
}
