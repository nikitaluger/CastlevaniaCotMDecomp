struct S_02025FF0 { u8 _0x000[0x1870]; u32 v; };
extern struct S_02025FF0 gMainWorkspace;
extern void *spawnBudgetedEffect(s32, s32);

/* Allocate a result object, store its fixed-point position and parameters,
 * register it in the owner's result array at the given slot, and return it. */
void *sub_080199B0(void *owner, s32 x, s32 y, u16 slot, u16 variant)
{
    void *result = spawnBudgetedEffect(gMainWorkspace.v, 0x8A);
    s32 hi, yHi, slotOffset;
    u8 *field, *ownerArray;

    if (result == NULL) return NULL;

    hi = x;
    if (hi < 0) hi += 0xFFFF;
    hi >>= 16;
    *(s16 *)((u8 *)result + 0x4C) = hi;

    yHi = y;
    if (yHi < 0) yHi += 0xFFFF;
    hi = yHi >> 16;
    field = (u8 *)result + 0x54;
    *(s16 *)field = hi;
    field += 8;
    *(u16 *)field = slot;
    field += 8;
    *(u16 *)field = variant;
    field += 0x28;
    *(void **)field = owner;

    ownerArray = *(u8 **)((u8 *)owner + 0x3C);
    slotOffset = (s16)slot * 4;
    ownerArray += 0x80;
    ownerArray += slotOffset;
    *(void **)ownerArray = result;
    return result;
}
