extern void setObjectAnimation(void *, void *, s32, s32);
extern void sub_080148D8(void *, void *);
extern void *sub_0805FAEC(void *, s32);
extern void sub_080C31E0(void *, s32);
extern void sub_080C31E4(void *, void *, s32);
extern u32 D_081021F4[];
extern u32 gMainObjTimerCallback[];

/* Initialises a complex entity: sets up its animation and graphics, spawns a
 * set of child sub-objects, copies table data into them, then dispatches the
 * entity's initial state callback. */
void sub_080ABBBC(u8 *self) {
    u8 *gfxObj;
    u8 *anim;
    u8 *animData;
    u8 *extra;
    u8 typeVal;
    u32 zero;
    u32 *tableEntry;
    u8 *table;
    u32 *dest;
    u8 **source;
    u32 i;
    s32 scale;
    s16 stateIdx;
    u8 *stateSlot;
    u8 stateId;
    u8 *flagsPtr;
    u32 flags;
    u32 fn;
    u8 *slots;
    u32 *animFn;
    u8 oldFlags;

    gfxObj = *(u8 **)(self + 0x38);
    anim = *(u8 **)(self + 0x3C);
    animData = anim + 0x34;
    extra = anim + 0x48;
    {
        u8 *stateByte = anim + 0x244;
        zero = 0;
        typeVal = 2;
        *stateByte = typeVal;
    }
    setObjectAnimation(gfxObj, animData, 0x35, 0);
    *(u8 *)(anim + 0x95) = zero;
    *(u32 *)(anim + 0x0C) = 0x700000;
    *(u32 *)(anim + 0x14) = zero;
    *(u16 *)(anim + 4) = (*(u16 *)(anim + 4) & 0xFDFF) | 0x100;
    sub_080148D8(gfxObj, *(u8 **)(anim + 8));
    scale = 0x32;
    *(u32 *)(gfxObj + 0x1C) = scale;
    scale += 0xCE;
    *(u16 *)(gfxObj + 4) = scale;
    *(u16 *)(gfxObj + 6) = scale;
    flagsPtr = gfxObj + 0x2A;
    oldFlags = *flagsPtr;
    flags = 0x40;
    flags |= oldFlags;
    *flagsPtr = flags;
    *(u8 **)(extra + 0x2C) = sub_0805FAEC(self, 0x1AD);
    *(u8 **)(extra + 0x30) = sub_0805FAEC(self, 0x1B6);
    *(u8 **)(extra + 0x50) = sub_0805FAEC(self, 0x1B3);
    *(u8 *)(*(u8 **)(extra + 0x50) + 0x4C) = 0;
    *(u8 **)(extra + 0x54) = sub_0805FAEC(self, 0x1B4);
    *(u8 *)(*(u8 **)(extra + 0x54) + 0x4C) = 0;
    *(u8 *)(*(u8 **)(extra + 0x54) + 0x50) = 0;
    *(u8 **)(extra + 0x58) = sub_0805FAEC(self, 0x1B4);
    *(u8 *)(*(u8 **)(extra + 0x58) + 0x4C) = 1;
    *(u8 *)(*(u8 **)(extra + 0x58) + 0x50) = 0;
    *(u8 **)(extra + 0x5C) = sub_0805FAEC(self, 0x1B5);
    *(u8 *)(*(u8 **)(extra + 0x5C) + 0x4C) = 0;
    *(u8 *)(*(u8 **)(extra + 0x5C) + 0x50) = 0;
    *(u8 *)(*(u8 **)(extra + 0x5C) + 0x54) = 0;
    *(u8 **)(extra + 0x60) = sub_0805FAEC(self, 0x1B5);
    *(u8 *)(*(u8 **)(extra + 0x60) + 0x4C) = typeVal;
    *(u8 *)(*(u8 **)(extra + 0x60) + 0x50) = 0;
    *(u8 *)(*(u8 **)(extra + 0x60) + 0x54) = 0;
    *(u8 **)(extra + 0x64) = sub_0805FAEC(self, 0x1B2);
    i = 0;
    table = (u8 *)D_081021F4;
    tableEntry = (u32 *)(table + 8);
    dest = (u32 *)(anim + 0xB8);
    source = (u8 **)(anim + 0xA4);
    for (; i <= 1; i++) {
        *dest++ = tableEntry[1];
        *(u32 *)(*source++ + 0x5C) = tableEntry[0];
        tableEntry += 4;
    }
    *(u32 *)(extra + 0x68) = 0x20;
    *(u32 *)(*(u8 *volatile *)(extra + 0x54) + 0x5C) = 0;
    *(u32 *)(*(u8 *volatile *)(extra + 0x54) + 0x6C) = 0;
    *(u32 *)(*(u8 *volatile *)(extra + 0x54) + 0x7C) = 0;
    *(u32 *)(extra + 0x6C) = -0x20;
    *(u32 *)(*(u8 *volatile *)(extra + 0x58) + 0x5C) = 0;
    *(u32 *)(*(u8 *volatile *)(extra + 0x58) + 0x6C) = 0;
    *(u32 *)(*(u8 *volatile *)(extra + 0x58) + 0x7C) = 0;
    stateIdx = *(s16 *)(self + 0x22);
    *(u8 *)(self + stateIdx * 2 + 0x19) = 0;
    animFn = gMainObjTimerCallback;
    slots = self + 0x18;
    sub_080C31E4(slots, self + 0x22, *animFn);
    stateIdx = *(s16 *)(self + 0x22);
    *(u8 *)(self + stateIdx * 2 + 0x19) += 1;
    stateIdx = *(s16 *)(self + 0x22);
    stateSlot = slots + stateIdx * 2;
    stateId = *stateSlot;
    {
        u8 *callbackTable = *(u8 **)(self + 0x14);
        fn = *(u32 *)(callbackTable + stateId * 4);
        sub_080C31E0(self, fn);
    }
}
