/* Initialise a trail effect from its owner: set its horizontal drift to +1 or
 * -1 according to the owner's facing flag (bit 4), then place it at the
 * owner's position with one of two vertical offsets chosen by `variant`. */
void sub_080A03C8(void *effect, void *owner, void *work, s32 variant) {
    if (effect == NULL) return;
    *(s32*)((u8*)effect + 0x6C) = (*(u16*)((u8*)owner + 2) & 0x10) ? 1 : -1;
    if (variant != 0) {
        *(s32*)((u8*)effect + 0x4C) = *(s32*)((u8*)work + 8);
        *(s32*)((u8*)effect + 0x5C) = *(s32*)((u8*)work + 0xC) + 0xFFFC0000;
    } else {
        *(s32*)((u8*)effect + 0x4C) = *(s32*)((u8*)work + 8);
        *(s32*)((u8*)effect + 0x5C) = *(s32*)((u8*)work + 0xC) + 0xFFDA0000;
    }
}
