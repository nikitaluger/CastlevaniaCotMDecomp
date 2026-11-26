extern void sub_080C31E0(void *, s32);
extern void sub_080C31E4(void *, void *, s32);
extern u32 gMainObjTimerCallback[];

/* Fill the work state's four-slot coordinate arrays (+0x48..+0x54 and
 * +0x58..+0x64) with the actor's x/y from +0x4C/+0x5C, then clear this
 * actor's script-action byte and advance the script. */
void sub_080352C0(void *obj) {
    u8 *actor = (u8 *)obj;
    u32 workAddr = *(u32 *)(actor + 0x3C);
    u32 slot = 0;
    const u32 *advance = gMainObjTimerCallback;
    u32 *dest;
    u8 *entry;
    dest = (u32 *)(workAddr + 0x48);
    for (; slot <= 3; slot++) {
        *dest = *(u32 *)(actor + 0x4C);
        *(u32 *)((u8 *)dest + 0x10) = *(u32 *)(actor + 0x5C);
        dest++;
    }
    *(u8 *)(actor + (*(s16 *)(actor + 0x22)) * 2 + 0x19) = 0;
    entry = actor + 0x18;
    sub_080C31E4(entry, actor + 0x22, *advance);
    *(u8 *)(actor + (*(s16 *)(actor + 0x22)) * 2 + 0x19) += 1;
    entry = entry + (*(s16 *)(actor + 0x22)) * 2;
    sub_080C31E0(actor, *(u32 *)((u8 *)*(u32 *)(actor + 0x14) + *(u8 *)entry * 4));
}
