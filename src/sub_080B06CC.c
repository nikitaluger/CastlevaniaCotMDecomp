void *spawnBudgetedEffect(u32 parent, u32 type);
extern u32 gActiveObjectId;

/* Fill the entity's three auxiliary slot pointers with freshly spawned
 * type-0x1A9 objects (NULL where the spawn budget is exhausted). */
void sub_080B06CC(void **slots)
{
    u32 i = 0;
    u32 *parentPtr = &gActiveObjectId;
    void **dst = slots;
    do {
        *dst++ = spawnBudgetedEffect(*parentPtr, 0x1A9);
        i++;
    } while (i <= 2);
}
