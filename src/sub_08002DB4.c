extern s32 sub_080012F8(s32 id);            /* 1 if id is within [D_02025B7C, D_02025B78) */
extern void *sub_08000C0C(u32 payload);     /* allocate a pool list cell  */
extern void sub_08000C38(void *head, void *payload); /* prepend a cell to *head */
extern void sub_08000C54(void *head, u32 payload);   /* append a cell to *head   */
extern u8 D_02021E90[];                     /* global state, entry list head at +0x550 */
extern u8 D_020223E0[];                     /* list that receives new entries */

/* Register a resource id under a key: find the entry in the global list whose
 * stored key is key+1, tag the id with 0x40000000 (in range) or 0x80000000
 * (out of range), then add the tagged id to that entry's list; if no entry
 * matches, allocate one holding the key and link it into D_020223E0. */
void sub_08002DB4(u32 resourceId, s32 key)
{
    void *entry;
    u32 taggedId = resourceId;
    s32 searchKey = key + 1;
    u8 *state = D_02021E90;
    s32 entryListOff = 0xAA;
    void *node;
    entryListOff <<= 3;
    node = *(void **)(state + entryListOff);

    entry = node;
    if (node != 0) {
        if (*(s32 *)((u8 *)*(void **)((u8 *)node + 4) + 4) != searchKey) {
            do {
                node = *(void **)node;
                if (node == 0)
                    break;
            } while (*(s32 *)((u8 *)*(void **)((u8 *)node + 4) + 4) != searchKey);
            entry = node;
        }
    }

    if (sub_080012F8(taggedId)) {
        taggedId |= 0x40000000;
    } else {
        taggedId |= 0x80000000;
    }

    if (entry != 0) {
        sub_08000C54((u8 *)entry + 4, taggedId);
    } else {
        entry = sub_08000C0C(taggedId);
        sub_08000C38(&entry, (void *)searchKey);
        sub_08000C38(D_020223E0, entry);
    }
}
