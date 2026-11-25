extern void sub_080BE58C(void *, s32);

/* If this owner's flag slot is clear, top its child list up to eight
 * objects of type 0x1D6. */
void sub_080BE5A4(void *arg0)
{
    s32 count = 0;
    s16 slot = *(s16 *)((u8 *)arg0 + 0x22);
    if ((((u8 *)arg0)[slot * 2 + 0x19] & 7) == 0) {
        void *child = *(void **)((u8 *)arg0 + 0x30);
        if (child != 0) {
            while (1) {
                if (*(s16 *)child == 0x1D6) {
                    count++;
                    if (count == 8) goto end;
                }
                child = *(void **)((u8 *)child + 0x2C);
                if (child == 0) break;
            }
        }
        {
            u32 spawned = 0;
            u32 needed = (u32)(8 - count);
            if (spawned < needed) {
                u32 limit = needed;
                do {
                    sub_080BE58C(arg0, 1);
                    spawned++;
                } while (spawned < limit);
            }
        }
    }
end:;
}
