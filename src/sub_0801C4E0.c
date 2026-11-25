/*
 * Follow placement: when this actor's follow flag is off and its carrier
 * still targets it, set the work position to an offset from the carrier's
 * position (left or right depending on facing) plus a move-record offset.
 */
s32 sub_08014990(s32);

void sub_0801C4E0(void *actor) {
    u8 *carrier;
    u8 *carrierWork;
    u8 *carrierMove;
    u8 *work;
    s32 facingRef;
    s32 flag;

    work = *(u8 **)((u8 *)actor + 0x3C);
    flag = 1 & *(u16 *)((u8 *)actor + 0x5C);
    if (flag == 0) {
        carrier = *(u8 **)((u8 *)actor + 0x8C);
        facingRef = *(s32 *)(carrier + 0x38);
        carrierWork = *(u8 **)(carrier + 0x3C);
        carrierMove = carrierWork + 0x48;
        if (*(s32 *)(carrierMove + 0x30) == (s32)actor) {
            if (sub_08014990(facingRef) < 0) {
                *(s32 *)(work + 8) = *(s32 *)(carrierWork + 8) + (s32)0xFFDC0000;
            } else {
                *(s32 *)(work + 8) = *(s32 *)(carrierWork + 8) + 0x240000;
            }
            *(s32 *)(work + 0x0C) = *(s32 *)(carrierWork + 0x0C) + *(s32 *)(carrierMove + 0x20) + (s32)0xFFD80000;
        }
    }
}
