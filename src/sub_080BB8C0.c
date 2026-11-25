/* One 40-byte record of the actor body-part table at 0x080CBDD0; the u16 pair
 * at +0x14/+0x16 is one body part's entry. */
struct PartDef { u8 pad[0x14]; u16 f14; u16 f16; u8 rest[0x10]; };

/* Give the five sprites of a component the body-part record selected by the
 * actor's body kind (s16 at +0x1C), storing its pair at +4 and +0xE of each. */
void sub_080BB8C0(void *arg0, void **arg1) {
    u32 i = 0;
    struct PartDef *partTable = (struct PartDef *)0x080CBDD0;
    void **slot = arg1;
    do {
        void *sprite;
        *(u16 *)((u8 *)*(vu32 *)slot + 4) = partTable[*(s16 *)((u8 *)arg0 + 0x1C)].f14;
        sprite = *slot++;
        *(u16 *)((u8 *)sprite + 0xE) = partTable[*(s16 *)((u8 *)arg0 + 0x1C)].f16;
        i++;
    } while (i <= 4);
}
