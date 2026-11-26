s32 sub_080141AC(void *, void *);
void sub_08013C5C(void *, void *);
s32 sub_08013558(void *, void *, void *);
void sub_08013978(void *, void *);
void sub_080142C0(void *, void *);
void sub_08013AC4(void *);
void sub_08005E80(s32);
void sub_080C31E8(void *, void *, s32, u32);
s32 sub_08013B5C(void *, void *);
void sub_080C31E0(u8 *, s32);
void sub_080113A8(void *, void *);
void sub_0801165C(void *, s32);
void sub_08013C8C(void *, void *);
extern u8 gCameraState[];
extern u8 gMainWorkspace[];
extern u8 D_0866E498[];
extern u32 D_08671BDC[];

/* One update tick of a weapon entity: run the hit/damage responses, handle the
 * attack-end flag (clear hit state, halve the X offset, issue callback 4), dispatch the
 * current state handler from D_0866E498, then write the owner's camera-corrected Y
 * position back through the coordinate table. */
void sub_0804BF28(u8 *self)
{
    u8 *parent;
    u8 *obj;
    u8 *objSub;
    u8 *objState;
    u8 *coordTable;
    u8 *basePtr;
    u32 slotIndex;
    u32 camOffset;
    u32 mode;
    u8 stateByte;
    u8 *slotArea;
    s32 stateIdx;
    s32 modeOff;
    s32 zero;
    s32 dummy;
    s32 xPos;

    parent = *((u8 **) (self + 0x38));
    obj = *((u8 **) (self + 0x3C));
    objSub = obj + 0x34;
    objState = obj + 0x48;

    if (sub_080141AC(parent, obj) == 1)
    {
        *((u16 *) objState) = 0;
    }
    else
    {
        *((u16 *) objState) = 1;
    }

    zero = 0;
    *((u32 *) (objState + 0x18)) = zero;

    dummy = 0;
    mode = *((s16 *) (objState + dummy));
    if (mode == 1)
    {
        sub_08013C5C(self, parent);
        if (sub_08013558(parent, obj, *((void **) (obj + 0x28))) != 0)
        {
            sub_08013978(self, *((void **) (obj + 0x28)));
        }
        sub_080142C0(self, *((void **) (obj + 0x28)));
        mode = mode & (*((u16 *) obj));
        if (mode && ((*((u8 *) (((((u32) (*((s16 *) (self + 0x22)))) * 2) + ((u32) self)) + 0x1A))) != 4))
        {
            u32 *callbackTable;
            sub_08013AC4(self);
            *((u32 *) (objState + 0x08)) = 0xB60;
            *((u32 *) (obj + 0x14)) = zero;
            xPos = *((s32 *) (obj + 0x10));
            if (xPos < 0) xPos += 3;
            *((s32 *) (obj + 0x10)) = xPos >> 2;
            sub_08005E80(0x8A);
            *((u8 *) (((((u32) (*((s16 *) (self + 0x22)))) * 2) + ((u32) self)) + 0x1B)) = zero;
            callbackTable = D_08671BDC;
            sub_080C31E8(self + 0x18, self + 0x22, 4, *callbackTable);
        }
    }

    if (sub_08013B5C(parent, obj) == 0)
    {
        u8 *slot;
        *((u32 *) (self + 0x14)) = (u32) D_0866E498;
        *((u16 *) (self + 0x22)) = (*((u16 *) (self + 0x22))) + 1;
        slot = (u8 *) ((((u32) (*((s16 *) (self + 0x22)))) * 2) + ((u32) self));
        *((u8 *) (slot + 0x19)) = (*((u8 *) (slot + 0x19))) + 1;
        stateIdx = (*((s16 *) (self + 0x22))) * 2;
        slotArea = self;
        slotArea += 0x18;
        stateByte = *((u8 *) (((u32) slotArea) + ((u32) stateIdx)));
        sub_080C31E0(self, *((s32 *) ((*((u32 *) (self + 0x14))) + (stateByte * 4))));
        *((u16 *) (self + 0x22)) = (*((u16 *) (self + 0x22))) - 1;
        if (((*((u16 *) (self + 2))) & 0x8000) == 0)
        {
            sub_080113A8(parent, objSub);
            sub_0801165C(obj, *((s32 *) (objState + 0x08)));
        }
        else
        {
            return;
        }
    }

    sub_08013C8C(self, parent);
    {
        s32 worldY = (*((s32 *) (obj + 0x0C))) + (*((s32 *) (objState + 0x18)));
        coordTable = gCameraState;
        basePtr = gMainWorkspace;
        basePtr += 0x18A8;
        slotIndex = (((u32) (*basePtr)) + 1) * 0x40;
        coordTable += 0x127C;
        camOffset = *((u32 *) (coordTable + slotIndex));
        *((u32 *) (parent + 0x18)) = worldY - ((camOffset + 0xFFFF8000) & 0xFFFF0000);
    }
}
