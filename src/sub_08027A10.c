/* Follow the owner: unless this object is flagged as settled (bit 0 of +0x64),
 * copy the position and attachment values of the object at +0x8C (and of its
 * sub-block at +0x48) into this object's own work block. */
void sub_08027A10(void *arg0) {
    void *work;
    void *pos;
    void *owner;
    void *ownerPos;

    work = *(void **)((u8 *)arg0 + 0x3C);
    pos = (u8 *)work + 0x48;
    if (!(1 & *(u16 *)((u8 *)arg0 + 0x64))) {
        owner = *(void **)(*(void **)((u8 *)arg0 + 0x8C) + 0x3C);
        ownerPos = (u8 *)owner + 0x48;
        *(s32 *)((u8 *)work + 0x48) = *(s32 *)((u8 *)owner + 8);
        *(s32 *)((u8 *)pos + 4) = *(s32 *)((u8 *)owner + 0xC);
        *(s32 *)((u8 *)pos + 8) = *(s32 *)((u8 *)ownerPos + 0x18);
        *(s32 *)((u8 *)pos + 0x5C) = *(s32 *)((u8 *)ownerPos + 0x68);
        *(s32 *)((u8 *)pos + 0x60) = *(s32 *)((u8 *)ownerPos + 0x6C);
    }
}
