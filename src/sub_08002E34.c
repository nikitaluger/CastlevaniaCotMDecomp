/*
 * Frame update of the timed object list: age every object, and when an
 * object's timer reaches zero remove it from the list, release the graphics
 * handles of its child links and slide the allocation pointer back.
 */
void sub_08000BE8(s32);
void sub_08000CE4(void *, void *);
void sub_08001384(s32);
void sub_08001448(void);

extern u8 D_02021E90[];
extern u32 D_020223E0;

void sub_08002E34(void) {
    u32 listOffset;
    void **node;

    listOffset = 0xAA;
    listOffset <<= 3;  /* head of the timed object list at D_02021E90 + 0x550 */
    node = *(void ***)(D_02021E90 + listOffset);

    while (node != 0) {
        void **object;
        s32 timer;
        object = (void **)node[1];
        timer = ((s32 *)object)[1];
        timer--;
        ((s32 *)object)[1] = timer;
        if (timer == 0) {
            void **link;
            sub_08000CE4(&D_020223E0, object);
            link = (void **)*object;
            while (link != 0) {
                s32 flags;
                s32 handle;
                flags = ((s32 *)link)[1];
                handle = flags & 0x0FFFFFFF;
                if (flags < 0) {
                    sub_08000BE8(handle);
                } else if (flags & 0x40000000) {
                    sub_08001384(handle);
                }
                ((s32 *)link)[1] = 0;
                link = (void **)*link;
            }
        }
        node = (void **)*node;
    }
    sub_08001448();
}
