extern u8 D_02025368[];
extern u8 D_02025FF0[];
extern u8 D_080E26D0[];

s16 sub_0806D62C(u16, u16);

/* Configure one display-part slot of an effect: copy the 12-byte part
 * definition (width, height, x, y, damage percent, lifetime) selected for the
 * given sprite frame, scale its damage by the global base value, and set the
 * part's flags from bit 0 of the global state byte. */
void sub_08084428(void *arg0, s16 frameId, s16 slotIndex)
{
    u8 *gParams = D_02025368;
    u16 *partDef = (u16 *)(D_080E26D0 + (s32)frameId * 12);
    s32 slotOffset = (s32)slotIndex * 4;
    u8 *slotPtr = (u8 *)arg0;
    u8 **partSlot;
    u8 *gState;
    u8 *part;

    slotPtr += 0x2C;
    slotPtr += slotOffset;
    partSlot = (u8 **)slotPtr;

    *(u16 *)(*((u8 * volatile *)partSlot) + 6) = partDef[0];
    *(u16 *)(*((u8 * volatile *)partSlot) + 8) = partDef[1];
    *(u16 *)(*((u8 * volatile *)partSlot) + 10) = partDef[2];
    *(u16 *)(*((u8 * volatile *)partSlot) + 12) = partDef[3];
    *(u16 *)(*((u8 * volatile *)partSlot) + 14) = sub_0806D62C(*(u16 *)(gParams + 0x2E2), partDef[4]);

    part = *((u8 * volatile *)partSlot);
    gState = D_02025FF0;
    *(u8 *)(part + 1) = *(u8 *)(gState + 0x1510) & 1;
    *(u16 *)(*((u8 * volatile *)partSlot) + 24) = partDef[5];
}
