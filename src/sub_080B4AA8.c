extern s32 setObjectAnimation(s32, s32, s32, s32);
extern s32 sub_080148D8(s32, s32);

/* Switch the entity's animation to 0x1C and set which way it faces according
 * to the target X coordinate held in its state block. */
void sub_080B4AA8(void *entity)
{
    s32 sprite = *(s32 *)((u8 *)entity + 0x38);
    void *state = *(void **)((u8 *)entity + 0x3C);

    setObjectAnimation(sprite, state + 0x34, 0x1C, 0);
    sub_080148D8(sprite, *(s32 *)((u8 *)state + 8));
}
