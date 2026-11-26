extern u8 gGameStatus[];
extern void *D_020278D0[];
void *sub_08001480(void *, s32);
void sub_0800F4D4(s32, u8, s32);
void sub_0800F584(u8, u8);
void sub_0806D930(void *);
void sub_080C2E68(void *, void *, s32);

/* Create two status objects, copy their base stats from the shared work state,
 * then load their graphics. */
void sub_0800E2A0(void *parent)
{
    u8 *workState = gGameStatus;
    u32 slotIndex = 0;
    u8 *statusObjects = (u8 *)D_020278D0;
    void **slotPtr;
    void *newObject;
    u8 *status;
    u8 *field40;
    u8 index;
    u32 copyOffset;

    slotPtr = (void **)(statusObjects + 0x48);

    do {
        newObject = sub_08001480(parent, 0x1B);
        *slotPtr = newObject;
        *(u8 *)((u8 *)newObject + 0x3C) = 5;
        newObject = *slotPtr++;
        *(u8 *)((u8 *)newObject + 0x44) = (u8)slotIndex;
        slotIndex++;
    } while (slotIndex <= 1);

    status = (u8 *)D_020278D0;
    copyOffset = 0xB1;
    copyOffset <<= 2;
    sub_080C2E68(status, workState + copyOffset, 0x48);
    sub_0806D930(status);
    field40 = status;
    field40 += 0x40;
    if (*field40 == 0) *field40 = 1;
    status += 0x41;
    if (*status == 0) *status = 1;
    index = *status;
    sub_0800F4D4(0, index, 0x82 << 2);
    index = *field40;
    sub_0800F4D4(1, index, 0x80 << 2);
    sub_0800F584(*status, *field40);
}
