extern s32 sub_08097EF4(s32, s32, s32, s32);
extern void sub_080C31E4(void *, void *, s32);

/* Uploads the direction-specific palette fragment for the entity's current
 * animation slot: the slot byte's low bits pick one of the four tables at
 * 0x083D59xx. If the entity's 0x4C flag is clear, upload the default table,
 * reset the slot byte and re-register its animation callback instead. */
void sub_080A20B4(u8 *entity) {
    u32 zero = 0;
    s32 paletteSrc = 0;
    s8 customPalette = *(s8 *)((s8 *)entity + 0x4C);

    if (customPalette != 0) {
        switch (*(u8 *)(entity + *(s16 *)(entity + 0x22) * 2 + 0x19) & 7) {
        case 0: paletteSrc = 0x083D5998; break;
        case 2: paletteSrc = 0x083D59D8; break;
        case 4: paletteSrc = 0x083D59F8; break;
        case 6: paletteSrc = 0x083D5A18; break;
        }
        if (!(*(u8 *)(entity + *(s16 *)(entity + 0x22) * 2 + 0x19) & 1)) {
            sub_08097EF4(1, paletteSrc, zero, 1);
        }
    } else {
        sub_08097EF4(1, 0x083D5998, zero, 1);
        *(s8 *)(entity + *(s16 *)(entity + 0x22) * 2 + 0x19) = 0;
        {
            const u32 *animTable = (const u32 *)0x08671BC0;
            void *animSlot = entity + 0x18;
            sub_080C31E4(animSlot, entity + 0x22, *animTable);
        }
    }
}
