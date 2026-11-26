void loadEffectPalette(u32);
void sub_080C31E0(void *, void *);
extern void sub_0809BEE8(void);

/* Addresses of the three palette sheets the screen effects can upload. */
struct PaletteSheets { u32 a, b, c; };
extern struct PaletteSheets D_08101808;

/*
 * Starts the screen fade effect: uploads the palette sheet selected by the
 * entity's effect index (+0x4C), installs the fade handler and runs its first
 * frame immediately.
 */
void sub_0809BEB0(void *entity) {
    struct PaletteSheets sheets;
    sheets = D_08101808;
    loadEffectPalette(*(u32 *)((u8 *)&sheets + *(u32 *)((u8 *)entity + 0x4C) * 4));
    *(void **)((u8 *)entity + 0x14) = (void *)sub_0809BEE8;
    *(u16 *)((u8 *)entity + 0x22) = 1;
    sub_080C31E0(entity, (void *)sub_0809BEE8);
}
