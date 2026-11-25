extern u8 D_080CAB88[];
extern u8 D_0863E7DC[];
/* Pick an entity's contact/hitbox data from its facing index and the actor's
 * contact flags, and set or clear the actor's contact-enable bit. */
void sub_0800C1EC(u8 *entity) {
    u8 *sprite = *(u8 **)(entity + 0x38);
    u8 *actor = *(u8 **)(entity + 0x28);
    u32 dirMask = 1U << *(s8 *)(entity + 0x44);
    u32 contactBits = *(u32 *)(actor + 0x6C) & dirMask;
    s32 contactFlag = (s32)(((-contactBits) | contactBits) >> 31);
    s32 tmp;
    s8 pose;
    if (((s8)*(u8 *)(actor + 0x50) == *(s8 *)(entity + 0x44)) || ((s8)*(u8 *)(actor + 0x54) == *(s8 *)(entity + 0x44))) contactFlag |= 2;
    *(u32 *)(sprite + 0x18) = 0;
    pose = (s8)*(u8 *)(*(u8 **)(entity + 0x28) + 0x4C);
    switch (pose) {
    case 1: case 3: case 5: case 6:
        if (contactFlag != 0) { tmp = 0x40 | *(u8 *)(sprite + 0x2A); *(u8 *)(sprite + 0x2A) = (u8)tmp; }
        else { *(u8 *)(sprite + 0x2A) &= 0xBF; }
        {
            u32 base = (u32)D_080CAB88;
            s32 dirOffset = *(s8 *)(entity + 0x44) * 2;
            u16 recordOffset = *(u16 *)(dirOffset + (contactFlag << 4) + base);
            *(u32 *)(sprite + 0x24) = (u32)D_0863E7DC + recordOffset * 8;
            *(u32 *)(sprite + 0x14) = (contactFlag == 2) ? *(s8 *)(entity + 0x44) * 0xD0000 : 0;
        }
        break;
    default:
        *(u8 *)(sprite + 0x2A) &= 0xBF;
        break;
    }
}
