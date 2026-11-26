/*
 * Load character `arg0`'s object tiles and palette, or blank the object tile
 * area when the character's graphic slot is empty.
 */
extern s32 sub_0800F414(s8 charId);  /* non-zero when the character has a graphic */
extern void postDisplaySprite(s32, const void *, void *, s32, s32);
extern void sub_08000E54(s32, s32, void *, s32, s32);
extern const void *D_0866CF4C[];  /* object tile graphics per character */
extern const void *D_0866CF6C[];  /* palette per character */

void sub_0800F464(u8 arg0)
{
    u32 idx;
    if (sub_0800F414((s8)arg0) != 0) {
        idx = arg0;
        postDisplaySprite(1, D_0866CF4C[idx], (void *)0x06001000, 0x600, 0x10);
        postDisplaySprite(1, D_0866CF6C[idx], (void *)0x05000080, 0x20, 0x10);
    } else {
        sub_08000E54(1, 0, (void *)0x06001000, 0x600, 0x10);
    }
}
