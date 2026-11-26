void sub_08010F5C(s32, void *, s32, s32, s32, s32, s32);

/* Switch an object's animation: when the requested id differs from the
 * current one, store it, look up that animation's frame table and start
 * playback; otherwise just update the low flag byte. */
void setObjectAnimation(s32 scene, void *obj, u16 animId, u8 flags) {
    s16 newAnim;
    u8 flagByte;
    void *animDesc;

    flagByte = flags;
    newAnim = (s16) animId;
    if (*(s16 *) ((u8 *) obj + 0xE) != newAnim) {
        *(s16 *) ((u8 *) obj + 0xE) = (s16) animId;
        animDesc = *(void **) ((u8 *) obj + 8);
        sub_08010F5C(scene, obj, *(s32 *) animDesc + (newAnim * 4), *(s32 *) ((u8 *) animDesc + 4), *(s32 *) ((u8 *) animDesc + 8), *(s32 *) ((u8 *) obj + 0x10), (s32) flagByte);
        return;
    }
    *(u8 *) ((u8 *) obj + 0) = (u8) ((2 & *(u8 *) ((u8 *) obj + 0)) | flagByte);
}
