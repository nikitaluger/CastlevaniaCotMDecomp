extern void *sub_08001480(u32, u32);
extern void sub_080C31E4(void *, void *, u32);
extern u32 gMainObjTimerCallback;

extern u8 gMainWorkspace[];

/* Workspace slots used here: +0x14B4 = current area/stage value,
 * +0x1844 = mask of effect-object kinds already loaded,
 * +0x184C..+0x1888 = one object slot per kind. */

/* Load this entity's shared effect-object set: if the area value is zero,
 * allocate the six base kinds first; always allocate the second batch, mark
 * the loaded kinds in the +0x1844 mask, clear the effect-state words, then
 * begin the entity's command script at step 0. */
void sub_080069A8(void *entity) {
    void *self = entity;
    {
        u8 *ws = gMainWorkspace;
        u32 stage = *(u32 *)(ws + 0x14B4);
        if (stage == 0) {
            *(u32 *)(ws + 0x184C) = (u32)sub_08001480(0, 7);
            *(u32 *)(ws + 0x1850) = (u32)sub_08001480(0, 8);
            *(u32 *)(ws + 0x1854) = (u32)sub_08001480(0, 9);
            *(u32 *)(ws + 0x185C) = (u32)sub_08001480(0, 0x0B);
            *(u32 *)(ws + 0x1860) = (u32)sub_08001480(0, 0x0C);
            *(u32 *)(ws + 0x1864) = (u32)sub_08001480(0, 0x0D);
            *(u32 *)(ws + 0x188C) = stage;
            *(u32 *)(ws + 0x1894) = stage;
        } else {
            /* Mark the base kinds as loaded without reallocating them. */
            u32 t1, t2, t3, t4;
            u32 *maskp;
            u32 mask;
            maskp = (u32 *)(ws + 0x1844);
            mask = *maskp;
            t1 = 0x80; t1 = t1 << 0x17; mask |= t1;
            t2 = 0x80; t2 = t2 << 0x11; mask |= t2;
            t3 = 0x80; t3 = t3 << 0x16; mask |= t3;
            t4 = 0x80; t4 = t4 << 0x15; mask |= t4;
            *maskp = mask;
        }
    }
    {
        u8 *ws;
        void *slotA;
        slotA = sub_08001480(0, 0x0A);
        ws = gMainWorkspace;
        *(u32 *)(ws + 0x1858) = (u32)slotA;
        *(u32 *)(ws + 0x1868) = (u32)sub_08001480(0, 2);
        *(u32 *)(ws + 0x186C) = (u32)sub_08001480(0, 0x0E);
        *(u32 *)(ws + 0x1870) = (u32)sub_08001480(0, 2);
        *(u32 *)(ws + 0x1874) = (u32)sub_08001480(0, 2);
        *(u32 *)(ws + 0x1878) = (u32)sub_08001480(0, 0x0F);
        *(u32 *)(ws + 0x187C) = (u32)sub_08001480(0, 2);
        *(u32 *)(ws + 0x1880) = (u32)sub_08001480(0, 2);
        *(u32 *)(ws + 0x1888) = (u32)sub_08001480(0, 0x11);
        {
            /* Mark the second batch's kinds as loaded. */
            u32 t1, t2, t3;
            u32 *maskp;
            u32 mask;
            maskp = (u32 *)(ws + 0x1844);
            mask = *maskp;
            t1 = 0x80; t1 = t1 << 0x0D; mask |= t1;
            t2 = 0x80; t2 = t2 << 0x0C; mask |= t2;
            t3 = 0x80; t3 = t3 << 0x0B; mask |= t3;
            *maskp = mask;
        }
        *(u32 *)(ws + 0x1890) = 0;
        *(u32 *)(ws + 0x189C) = 0;
        *(u32 *)(ws + 0x1898) = 0;
        ws = ws + (0xC5 << 5);
        *(u32 *)ws = 0;
    }
    {
        s16 step = *(s16 *)((u8 *)self + 0x22);
        *((u8 *)self + step * 2 + 0x19) = 0;
    }
    {
        u32 *scriptTable = &gMainObjTimerCallback;
        sub_080C31E4((u8 *)self + 0x18, (u8 *)self + 0x22, *scriptTable);
    }
}
