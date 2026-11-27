/* Spawn a type-0x187 child object linked to `source`, copy its position and
 * direction fields, recompute the direction toward (targetX, targetY), then
 * clear the child's final flag byte. */
extern void *spawnBudgetedEffect(s32, s32);
extern void sub_080A0638(void *, s32, s32);

void sub_080A0668(s32 parent, void *source, s32 targetX, s32 targetY)
{
    void *child;

    child = spawnBudgetedEffect(parent, 0x187);
    *(void **)((u8 *)child + 0x4C) = source;
    *(s32 *)((u8 *)child + 0x5C) = (s32) *(s32 *)((u8 *)source + 0x4C);
    *(s32 *)((u8 *)child + 0x6C) = (s32) *(s32 *)((u8 *)source + 0x5C);
    sub_080A0638(source, targetX, targetY);
    *(s32 *)((u8 *)child + 0x7C) = (s32) *(s32 *)((u8 *)source + 0x7C);
    *(s32 *)((u8 *)child + 0x8C) = (s32) *(s32 *)((u8 *)source + 0x8C);
    *(s8 *)((u8 *)child + 0x9C) = 0;
}
