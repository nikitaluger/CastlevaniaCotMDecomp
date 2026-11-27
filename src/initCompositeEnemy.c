extern void setObjectAnimation(void *, void *, s32, s32);
extern void setSpriteFacingToTarget(void *, void *);
extern void *spawnBudgetedEffect(void *, s32);
extern void sub_080C31E0(void *, s32);
extern void sub_080C31E4(void *, void *, s32);
extern u32 gCompositePartParams[];
extern u32 gMainObjTimerCallbacks[];

/* Initialises a complex/multi-part entity: sets its animation and graphics,
 * spawns the child sub-objects, copies per-part parameters into them, then
 * dispatches the entity's initial state callback. */
void initCompositeEnemy(u8 *self) {
    u8 *sprite;
    u8 *work;
    u8 *gfxInit;
    u8 *parts;
    u8 partType;
    u32 zero;
    u32 *paramEntry;
    u8 *paramTable;
    u32 *dest;
    u8 **source;
    u32 i;
    s32 spriteScale;
    s16 stateIndex;
    u8 *stateSlot;
    u8 stateId;
    u8 *flagsPtr;
    u32 flags;
    u32 callback;
    u8 *stepSlots;
    u32 *timerCallback;
    u8 oldFlags;

    sprite = *(u8 **)(self + 0x38);
    work = *(u8 **)(self + 0x3C);
    gfxInit = work + 0x34;
    parts = work + 0x48;
    {
        u8 *subStateByte = work + 0x244;
        zero = 0;
        partType = 2;
        *subStateByte = partType;
    }
    setObjectAnimation(sprite, gfxInit, 0x35, 0);
    *(u8 *)(work + 0x95) = zero;
    *(u32 *)(work + 0x0C) = 0x700000;
    *(u32 *)(work + 0x14) = zero;
    *(u16 *)(work + 4) = (*(u16 *)(work + 4) & 0xFDFF) | 0x100;
    setSpriteFacingToTarget(sprite, *(u8 **)(work + 8));
    spriteScale = 0x32;
    *(u32 *)(sprite + 0x1C) = spriteScale;
    spriteScale += 0xCE;
    *(u16 *)(sprite + 4) = spriteScale;
    *(u16 *)(sprite + 6) = spriteScale;
    flagsPtr = sprite + 0x2A;
    oldFlags = *flagsPtr;
    flags = 0x40;
    flags |= oldFlags;
    *flagsPtr = flags;
    *(u8 **)(parts + 0x2C) = spawnBudgetedEffect(self, 0x1AD);
    *(u8 **)(parts + 0x30) = spawnBudgetedEffect(self, 0x1B6);
    *(u8 **)(parts + 0x50) = spawnBudgetedEffect(self, 0x1B3);
    *(u8 *)(*(u8 **)(parts + 0x50) + 0x4C) = 0;
    *(u8 **)(parts + 0x54) = spawnBudgetedEffect(self, 0x1B4);
    *(u8 *)(*(u8 **)(parts + 0x54) + 0x4C) = 0;
    *(u8 *)(*(u8 **)(parts + 0x54) + 0x50) = 0;
    *(u8 **)(parts + 0x58) = spawnBudgetedEffect(self, 0x1B4);
    *(u8 *)(*(u8 **)(parts + 0x58) + 0x4C) = 1;
    *(u8 *)(*(u8 **)(parts + 0x58) + 0x50) = 0;
    *(u8 **)(parts + 0x5C) = spawnBudgetedEffect(self, 0x1B5);
    *(u8 *)(*(u8 **)(parts + 0x5C) + 0x4C) = 0;
    *(u8 *)(*(u8 **)(parts + 0x5C) + 0x50) = 0;
    *(u8 *)(*(u8 **)(parts + 0x5C) + 0x54) = 0;
    *(u8 **)(parts + 0x60) = spawnBudgetedEffect(self, 0x1B5);
    *(u8 *)(*(u8 **)(parts + 0x60) + 0x4C) = partType;
    *(u8 *)(*(u8 **)(parts + 0x60) + 0x50) = 0;
    *(u8 *)(*(u8 **)(parts + 0x60) + 0x54) = 0;
    *(u8 **)(parts + 0x64) = spawnBudgetedEffect(self, 0x1B2);
    i = 0;
    paramTable = (u8 *)gCompositePartParams;
    paramEntry = (u32 *)(paramTable + 8);
    dest = (u32 *)(work + 0xB8);
    source = (u8 **)(work + 0xA4);
    for (; i <= 1; i++) {
        *dest++ = paramEntry[1];
        *(u32 *)(*source++ + 0x5C) = paramEntry[0];
        paramEntry += 4;
    }
    *(u32 *)(parts + 0x68) = 0x20;
    *(u32 *)(*(u8 *volatile *)(parts + 0x54) + 0x5C) = 0;
    *(u32 *)(*(u8 *volatile *)(parts + 0x54) + 0x6C) = 0;
    *(u32 *)(*(u8 *volatile *)(parts + 0x54) + 0x7C) = 0;
    *(u32 *)(parts + 0x6C) = -0x20;
    *(u32 *)(*(u8 *volatile *)(parts + 0x58) + 0x5C) = 0;
    *(u32 *)(*(u8 *volatile *)(parts + 0x58) + 0x6C) = 0;
    *(u32 *)(*(u8 *volatile *)(parts + 0x58) + 0x7C) = 0;
    stateIndex = *(s16 *)(self + 0x22);
    *(u8 *)(self + stateIndex * 2 + 0x19) = 0;
    timerCallback = gMainObjTimerCallbacks;
    stepSlots = self + 0x18;
    sub_080C31E4(stepSlots, self + 0x22, *timerCallback);
    stateIndex = *(s16 *)(self + 0x22);
    *(u8 *)(self + stateIndex * 2 + 0x19) += 1;
    stateIndex = *(s16 *)(self + 0x22);
    stateSlot = stepSlots + stateIndex * 2;
    stateId = *stateSlot;
    {
        u8 *callbackTable = *(u8 **)(self + 0x14);
        callback = *(u32 *)(callbackTable + stateId * 4);
        sub_080C31E0(self, callback);
    }
}
