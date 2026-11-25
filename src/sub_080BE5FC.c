extern void sub_08014460(void *);

/* For an object whose current command slot is inactive, look through its child
 * list for an untouched companion entity (id 0x1D6), flag it active and move it
 * to the front of the global entity list. */
void sub_080BE5FC(void *obj)
{
    s16 commandIndex = *(s16 *)((u8 *)obj + 0x22);
    if ((((u8 *)obj)[commandIndex * 2 + 0x19] & 0x7F) == 0) {
        void *child = *(void **)((u8 *)obj + 0x30);
        while (child != 0) {
            if (*(s16 *)child == 0x1D6 && *(s32 *)((u8 *)child + 0x4C) == 0) {
                *(s32 *)((u8 *)child + 0x9C) = 1;
                sub_08014460(child);
                return;
            }
            child = *(void **)((u8 *)child + 0x2C);
        }
    }
}
