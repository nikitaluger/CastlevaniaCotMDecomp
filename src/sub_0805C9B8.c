extern void sub_08015974(void *);
extern void sub_080161F0(void *);
extern void sub_08016678(void *);
extern void sub_080C31E0(void *, s32);

/* Tear down an object: free its optional sub-objects (+0x28, +0x84..+0x98 and
 * +0x2C), reset its field state, then dispatch the callback at +0x24. */
void sub_0805C9B8(void *obj) {
    u8 *fields = *(u8 **)((u8 *)obj + 0x3C);
    void **slots;
    s32 remaining;

    if (*(void **)(fields + 0x28) != 0)
        sub_080161F0(*(void **)(fields + 0x28));

    slots = (void **)(fields + 0x84);
    remaining = 4;
    do {
        if (*slots != 0)
            sub_080161F0(*slots);
        slots++;
        remaining--;
    } while (remaining >= 0);

    if (*(void **)(fields + 0x2C) != 0)
        sub_08015974(*(void **)(fields + 0x2C));

    sub_08016678(obj);
    sub_080C31E0(obj, *(s32 *)(fields + 0x24));
}
