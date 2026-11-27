extern void *createChildObject(u32, u32);
extern void sub_080C31E4(void *, void *, u32);
extern u32 gScriptStepCallbackTable;

extern u8 gMainWorkspace[];

/* Workspace slots used here: +0x14B4 = current area/stage value,
 * +0x1844 = mask of effect-object kinds already loaded,
 * +0x184C..+0x1888 = one object slot per kind. */

/* Load this entity's shared effect-object set: if the area value is zero,
 * allocate the six base kinds first; always allocate the second batch, mark
 * the loaded kinds in the +0x1844 mask, clear the effect-state words, then
 * begin the entity's command script at step 0. */
void loadEntityEffectObjects(void *entity) {
    void *self = entity;
    {
        u8 *ws = gMainWorkspace;
        u32 stage = *(u32 *)(ws + 0x14B4);
        if (stage == 0) {
            *(u32 *)(ws + 0x184C) = (u32)createChildObject(0, 7);
            *(u32 *)(ws + 0x1850) = (u32)createChildObject(0, 8);
            *(u32 *)(ws + 0x1854) = (u32)createChildObject(0, 9);
            *(u32 *)(ws + 0x185C) = (u32)createChildObject(0, 0x0B);
            *(u32 *)(ws + 0x1860) = (u32)createChildObject(0, 0x0C);
            *(u32 *)(ws + 0x1864) = (u32)createChildObject(0, 0x0D);
            *(u32 *)(ws + 0x188C) = stage;
            *(u32 *)(ws + 0x1894) = stage;
        } else {
            /* Mark the base kinds as loaded without reallocating them. */
            u32 kindBitA, kindBitB, kindBitC, kindBitD;
            u32 *loadedMask;
            u32 mask;
            loadedMask = (u32 *)(ws + 0x1844);
            mask = *loadedMask;
            kindBitA = 0x80; kindBitA = kindBitA << 0x17; mask |= kindBitA;
            kindBitB = 0x80; kindBitB = kindBitB << 0x11; mask |= kindBitB;
            kindBitC = 0x80; kindBitC = kindBitC << 0x16; mask |= kindBitC;
            kindBitD = 0x80; kindBitD = kindBitD << 0x15; mask |= kindBitD;
            *loadedMask = mask;
        }
    }
    {
        u8 *ws;
        void *effectSlot;
        effectSlot = createChildObject(0, 0x0A);
        ws = gMainWorkspace;
        *(u32 *)(ws + 0x1858) = (u32)effectSlot;
        *(u32 *)(ws + 0x1868) = (u32)createChildObject(0, 2);
        *(u32 *)(ws + 0x186C) = (u32)createChildObject(0, 0x0E);
        *(u32 *)(ws + 0x1870) = (u32)createChildObject(0, 2);
        *(u32 *)(ws + 0x1874) = (u32)createChildObject(0, 2);
        *(u32 *)(ws + 0x1878) = (u32)createChildObject(0, 0x0F);
        *(u32 *)(ws + 0x187C) = (u32)createChildObject(0, 2);
        *(u32 *)(ws + 0x1880) = (u32)createChildObject(0, 2);
        *(u32 *)(ws + 0x1888) = (u32)createChildObject(0, 0x11);
        {
            /* Mark the second batch's kinds as loaded. */
            u32 kindBitA, kindBitB, kindBitC;
            u32 *loadedMask;
            u32 mask;
            loadedMask = (u32 *)(ws + 0x1844);
            mask = *loadedMask;
            kindBitA = 0x80; kindBitA = kindBitA << 0x0D; mask |= kindBitA;
            kindBitB = 0x80; kindBitB = kindBitB << 0x0C; mask |= kindBitB;
            kindBitC = 0x80; kindBitC = kindBitC << 0x0B; mask |= kindBitC;
            *loadedMask = mask;
        }
        *(u32 *)(ws + 0x1890) = 0;
        *(u32 *)(ws + 0x189C) = 0;
        *(u32 *)(ws + 0x1898) = 0;
        ws = ws + (0xC5 << 5);
        *(u32 *)ws = 0;
    }
    {
        s16 stepIndex = *(s16 *)((u8 *)self + 0x22);
        *((u8 *)self + stepIndex * 2 + 0x19) = 0;
    }
    {
        u32 *scriptCallback = &gScriptStepCallbackTable;
        sub_080C31E4((u8 *)self + 0x18, (u8 *)self + 0x22, *scriptCallback);
    }
}
