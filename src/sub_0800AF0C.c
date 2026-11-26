extern void sub_08005E80(s32);
extern void sub_0800B824(s32, s32, s32);
extern void sub_0800B888(void *, s32);
extern void sub_0800B9A8(s8, s32, s32);
extern void sub_080103A0(u8, u8);
extern s32 sub_080103F0(u8);
extern void sub_080C31E4(void *, void *, s32);
extern void sub_080C31E8(void *, void *, s32, s32);

/* Global game state; the two key-input words live at +0x146C and +0x1470. */
struct DraculaState {
    u8 pad[0x146C];
    u16 f146C;
    u16 f146E;
    u16 f1470;
};
extern struct DraculaState gCameraState;

/* Save-file menu entity: +0x50 is the source slot (never selectable) and
 * +0x54 the currently highlighted destination slot. */
struct Ent {
    u8 _0[0x50];
    u8 srcSlot;
    u8 _51[3];
    s8 destSlot;
};
extern u32 gMainObjTimerCallback[];
extern u32 D_08671BC0[];
extern u32 D_08671BD0[];

/* Copy-file menu cursor: moves the highlighted destination slot over the eight
 * save slots on d-pad input, skipping the source slot, plays the move sound,
 * and on B cancels (back to the menu script) or on A copies the source save
 * record into the selected empty slot and advances the actor's script. */
void sub_0800AF0C(struct Ent *arg0)
{
    s32 dataPtr = *(s32 *)((u8 *)arg0 + 0x3C);
    s32 oldSlot = arg0->destSlot;
    u32 isCancel;
    s32 itemState;
    s32 t;
    u8 cur;

    if ((0x30 & gCameraState.f1470) != 0x30)
    {
        if ((0x20 & gCameraState.f1470) != 0)
        {
            t = (u8)arg0->destSlot - 1;
            arg0->destSlot = t;
            if ((s32)((s8)t << 24) < 0)
                arg0->destSlot = 7;
            cur = (u8)arg0->destSlot;
            if (arg0->destSlot == (s8)arg0->srcSlot)
            {
                t = cur - 1;
                arg0->destSlot = t;
                if ((s32)((s8)t << 24) < 0)
                    arg0->destSlot = 7;
            }
        }
        if ((0x10 & gCameraState.f1470) != 0)
        {
            u8 zero;
            t = (u8)arg0->destSlot + 1;
            zero = 0;
            arg0->destSlot = t;
            if ((s8)t == 8)
                arg0->destSlot = zero;
            cur = (u8)arg0->destSlot;
            if (arg0->destSlot == (s8)arg0->srcSlot)
            {
                t = cur + 1;
                arg0->destSlot = t;
                if ((s8)t == 8)
                    arg0->destSlot = zero;
            }
        }
        if ((0x30 & gCameraState.f1470) != 0)
            sub_08005E80(0x154);
    }

    isCancel = (u16)(gCameraState.f146C & 2);
    if (isCancel != 0)
    {
        sub_08005E80(0x159);
        arg0->destSlot = -1;
        sub_0800B9A8(arg0->destSlot, 2, dataPtr);
        sub_0800B824(0x81D6, 0x270, 0x600);
        *((u8 *)((u8 *)arg0 + *(s16 *)((u8 *)arg0 + 0x22) * 2 + 0x19)) = 0;
        {
            u32 *tbl = &D_08671BC0;
            sub_080C31E4((u8 *)arg0 + 0x18, (u8 *)arg0 + 0x22, *tbl);
        }
        return;
    }
    if (oldSlot != arg0->destSlot)
        sub_0800B9A8(arg0->destSlot, 2, dataPtr);
    if ((1 & gCameraState.f146C) != 0)
    {
        itemState = sub_080103F0((u8)arg0->destSlot);
        if (itemState != 0)
        {
            sub_08005E80(0x157);
            sub_0800B824(0x81D8, 0x270, 0x600);
            *((u8 *)((u8 *)arg0 + *(s16 *)((u8 *)arg0 + 0x22) * 2 + 0x19)) = isCancel;
            {
                u32 *tbl = &gMainObjTimerCallback;
                sub_080C31E4((u8 *)arg0 + 0x18, (u8 *)arg0 + 0x22, *tbl);
            }
            return;
        }
        sub_08005E80(0x15B);
        sub_080103A0(*(u8 *)((u8 *)arg0 + 0x50), (u8)arg0->destSlot);
        sub_0800B9A8(arg0->destSlot, 2, dataPtr);
        sub_0800B888(arg0, dataPtr);
        sub_0800B824(0x81D9, 0x270, 0x600);
        *((u8 *)((u8 *)arg0 + *(s16 *)((u8 *)arg0 + 0x22) * 2 + 0x19)) = itemState;
        {
            u32 *tbl = &D_08671BD0;
            sub_080C31E8((u8 *)arg0 + 0x18, (u8 *)arg0 + 0x22, 3, *tbl);
        }
    }
}
