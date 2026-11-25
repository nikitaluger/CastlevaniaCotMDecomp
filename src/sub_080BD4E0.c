extern void sub_08011650(s32);
extern void sub_08015974(void);
extern void sub_080161F0(void);
extern void sub_08016678(void *);
extern void sub_080C31E0(void *, s32);

/* Destructor for a multi-part scripted object: releases each registered render
 * part, frees the model, releases the linked secondary, detaches the object and
 * finally destroys it. */
void sub_080BD4E0(void *entity)
{
    s32 sprite = *(s32 *)((u8 *)entity + 0x38);
    void *work = *(void **)((u8 *)entity + 0x3C);
    void *part = (u8 *)work + 0x48;

    if (*(s32 *)((u8 *)work + 0x28) != 0)
        sub_080161F0();
    if (*(s32 *)((u8 *)work + 0x48) != 0)
        sub_080161F0();
    if (*(s32 *)((u8 *)part + 4) != 0)
        sub_080161F0();

    sub_08011650(sprite);
    if (*(s32 *)((u8 *)work + 0x2C) != 0)
        sub_08015974();
    sub_08016678(entity);
    sub_080C31E0(entity, *(s32 *)((u8 *)work + 0x24));
}
