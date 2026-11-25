struct SyncObj {
    u16 x;
    u16 y;
    u8 pad[0x24];
    u16 spriteIndex;
    u8 attr;
};

/* Copy the source object's position into the target child object and, if the
 * source is in one of the attack states, select the matching sprite frame and
 * mirror the target. */
void sub_0803974C(void *arg0) {
    u8 *self = (u8 *)arg0;
    struct SyncObj *target = *(struct SyncObj **)(self + 0x38);
    u8 *attached = *(u8 **)(self + 0x3C);
    u8 *source;

    (*(u8 **)(attached + 0x28))[1] = 0;
    (*(u8 **)(attached + 0x48))[1] = 0;

    source = *(u8 **)(*(u8 **)(self + 0x28) + 0x38);
    target->x = *(u16 *)(source + 0);
    source = *(u8 * volatile *)(self + 0x28);
    source = *(u8 * volatile *)(source + 0x38);
    target->y = *(u16 *)(source + 2);

    target->attr &= 0xBF;

    switch (*(u16 *)(*(u8 **)(*(u8 **)(self + 0x28) + 0x38) + 0x28)) {
    case 0x1A:
        target->spriteIndex = 0x26;
        break;
    case 0x1E:
        target->spriteIndex = 0x27;
        break;
    case 0x22:
        target->spriteIndex = 0x28;
        break;
    default:
        return;
    }

    target->attr |= 0x40;
}
