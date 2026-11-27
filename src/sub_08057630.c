extern s32 sub_08014620(s32, s32, u16);
extern void sub_08005E80(u16);
extern void *spawnBudgetedEffect(s32, s32);
extern void sub_080C31E0(void *, s32);

/* Plays a sound, works out the aim direction from the camera target, then
 * spawns four projectiles at the entity's position, tagging each with that
 * direction and its slot index before advancing the script state. */
void sub_08057630(u8 *entity) {
    u8 *work = *(u8 **)(entity + 0x3C);
    u32 *p;
    u32 i;
    s32 direction;
    direction = sub_08014620(*(s32 *)(work + 8), *(s32 *)(work + 0xC), 8);
    sub_08005E80(0x83);
    i = 0;
    p = (u32 *)0x02027860;
    while ((s32)i <= 3) {
        void *obj = spawnBudgetedEffect(*p, 0x15F);
        if (obj != 0) {
            u8 owner = *(entity + 0x4C);
            *(u8 *)((u8 *)obj + 0x4C) = owner;
            *(s32 *)((u8 *)obj + 0x5C) = *(s32 *)(work + 8);
            *(s32 *)((u8 *)obj + 0x6C) = *(s32 *)(work + 0xC);
            {
                u8 *field = (u8 *)obj + 0x80;
                *field = (u8)direction;
                field -= 4;
                *field = (u8)i;
            }
        }
        i++;
    }
    sub_080C31E0(entity, *(s32 *)(entity + 0x24));
}
