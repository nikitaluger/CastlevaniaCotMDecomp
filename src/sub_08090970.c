void sub_080C31E4(void *, void *, s32);

/* Landing step: when the object's y position reaches the height stored at
 * body = work+0x48, snap it to that height, stop its vertical motion, clear
 * the body timer and the script counter, and advance the command script. */
void sub_08090970(void *entity) {
    void *work = *(void **)((u8 *)entity + 0x3C);
    void *body = (u8 *)work + 0x48;
    s32 y = *(s32 *)((u8 *)work + 0xC);
    s32 groundY = *(s32 *)((u8 *)body + 0xC);
    u8 zero;
    if (y <= groundY) {
        *(s32 *)((u8 *)work + 0xC) = groundY;
        *(s32 *)((u8 *)work + 0x14) = 0;
        zero = 0;
        *(s16 *)((u8 *)body + 0x10) = 0;
        ((u8 *)((u8 *)entity + (*(s16 *)((u8 *)entity + 0x22)) * 2))[0x19] = zero;
        {
            s32 *scriptTable;
            scriptTable = (s32 *)0x08671BB0;
            sub_080C31E4(entity + 0x18, entity + 0x22, *scriptTable);
        }
    }
}
