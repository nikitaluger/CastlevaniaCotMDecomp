extern void *sub_0805FAEC(s32 parent, s32 type);

/* Spawn a type-0x1C1 object under the entity and clear its state byte. */
void *sub_080B7174(s32 parent)
{
    void *obj = sub_0805FAEC(parent, 0x1C1);
    if (obj == 0) {
        return 0;
    }
    *(u8 *)((u8 *)obj + 0x4C) = 0;
    return obj;
}

/* Spawn a type-0x1C0 object under the entity, store arg1 at +0x5C and clear its
 * state byte. */
void *sub_080B7144(s32 parent, s32 arg1)
{
    void *obj = sub_0805FAEC(parent, 0x1C0);
    if (obj == 0) {
        return 0;
    }
    *(s32 *)((u8 *)obj + 0x5C) = arg1;
    *(u8 *)((u8 *)obj + 0x4C) = 0;
    return obj;
}

/* Set bit 0 of the flag word on every type-0x1C2 child object. */
void sub_080B722C(void *parent)
{
    void *child = *(void **)((u8 *)parent + 0x30);
    if (child != 0) {
        do {
            if (*(s16 *)child == 0x1C2) {
                u16 *flags = *(u16 **)((u8 *)child + 0x3C);
                *flags |= 1;
            }
            child = *(void **)((u8 *)child + 0x2C);
        } while (child != 0);
    }
}

extern void sub_08011898(void *, s32);
extern void sub_080113A8(s32, void *);
extern void sub_080B72CC(void *);
extern void sub_080C31E0(void *, s32);

/* Move the effect through world collision and play its animation; once it has
 * landed (flag bit 1) hand control to the next handler. */
void sub_080B6DD4(void *entity)
{
    s32 sprite = *(s32 *)((u8 *)entity + 0x38);
    u8 *anim = (u8 *)*(void **)((u8 *)entity + 0x3C) + 0x34;
    sub_08011898(*(void **)((u8 *)entity + 0x3C), 0x4000);
    sub_080113A8(sprite, anim);
    sub_080B72CC(entity);
    if (anim[0] & 2) {
        sub_080C31E0(entity, *(s32 *)((u8 *)entity + 0x24));
    }
}
