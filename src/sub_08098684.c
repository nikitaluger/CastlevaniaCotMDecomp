extern s8 sub_080988DC(void *p);

/* Start a script sequence: select the entry list for the given script index,
 * store the initial indices and parameter, then run the entry walker and save
 * its result in the object. */
void sub_08098684(void *obj, u8 script, s8 param)
{
    u8 scriptIndex = (u8)((script << 24) >> 24);
    int zero;
    u8 *cursor = (u8 *)obj + 0x24;
    zero = 0;
    *cursor = scriptIndex;
    cursor++;
    *cursor = zero;
    cursor++;
    *cursor = zero;
    cursor++;
    *cursor = (u8)param;
    *((s32 *)((u8 *)obj + 0x20)) = *((s32 *)(*((s32 *)obj) + (scriptIndex * 4)));
    ((u8 *)obj)[0x29] = zero;
    ((u8 *)obj)[0x28] = (u8)sub_080988DC(obj);
}
