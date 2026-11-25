extern u8 D_080CB2B8[];

/* One entry of the parameter table: two 16-bit values. */
struct TblEntry { u16 first; u8 pad[2]; u16 second; u8 rest[0xE]; };

/* Copy the two parameter words of the table entry selected by the index at
 * component+0x1C into the +4 and +0xE fields of each of five objects. */
void sub_080BB900(void *component, void **objects)
{
    u32 i = 0;
    struct TblEntry *tbl = (struct TblEntry *)D_080CB2B8;
    void **p = objects;
    do {
        void *obj;
        obj = *p;
        *(u16 *)((u8 *)obj + 4) = tbl[*(s16 *)((u8 *)component + 0x1C)].first;
        obj = *p++;
        *(u16 *)((u8 *)obj + 0xE) = tbl[*(s16 *)((u8 *)component + 0x1C)].second;
        i++;
    } while (i <= 4);
}
