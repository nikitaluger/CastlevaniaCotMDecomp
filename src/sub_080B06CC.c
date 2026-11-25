void *sub_0805FAEC(u32 parent, u32 type);
extern u32 D_02027860;

/* Fill the entity's three auxiliary slot pointers with freshly spawned
 * type-0x1A9 objects (NULL where the spawn budget is exhausted). */
void sub_080B06CC(void **slots)
{
    u32 i = 0;
    u32 *parentPtr = &D_02027860;
    void **dst = slots;
    do {
        *dst++ = sub_0805FAEC(*parentPtr, 0x1A9);
        i++;
    } while (i <= 2);
}
