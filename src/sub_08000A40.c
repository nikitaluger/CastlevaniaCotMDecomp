void sub_080009DC(s32 slot, void *region, s32 size);
extern u8 D_02000000[];
extern u8 D_02004000[];

/* One descriptor of the heap block table at 0x02004000. */
struct MemBlock { u16 flags; u16 reserved; u32 size; u32 base; };

/* Reset the heap: clear the used flag of descriptor slots 1 to 7, then register
 * the 16 KB region at 0x02000000 as slot 0. */
void sub_08000A40(void)
{
    s32 i = 7;
    void *region = D_02000000;
    struct MemBlock *block = (struct MemBlock *)D_02004000;
    s32 z = 0;

    block += 7;
    while (i > 0) {
        block->flags = z;
        block -= 1;
        i--;
    }
    sub_080009DC(0, region, 0x4000);
}
