void *sub_08000C84(void **arg0)
{
    void *r2 = *arg0;
    void *ret;
    if (r2 == 0) {
        ret = 0;
    } else {
        ret = *(void **)((u8 *)r2 + 4);
        *(void **)((u8 *)r2 + 4) = 0;
        *arg0 = *(void **)r2;
    }
    return ret;
}

void *sub_08000CA0(void **arg0)
{
    void *r1 = *arg0;
    void *r3;
    void *r2;
    if (r1 == 0) {
        return 0;
    }
    r3 = arg0;
    r2 = r1;
    if (*(void **)r2 != 0) {
        do {
            r3 = *(void **)r2;
            r2 = r3;
        } while (*(void **)r3 != 0);
    }
    {
        void *ret = *(void **)((u8 *)r2 + 4);
        *(void **)((u8 *)r2 + 4) = 0;
        *(void **)r3 = 0;
        return ret;
    }
}

void *sub_08000C0C(void *);

/* Allocates a node holding `payload` and appends it to the tail of the list
 * headed by *listHead; nodes link through +0 and carry their value at +4. */
void sub_08000C54(void **listHead, void *payload)
{
    void *node = sub_08000C0C(payload);
    if (node != 0) {
        void *head = *listHead;
        if (head != 0) {
            void *last = head;
            while (*(void **)last != 0) {
                last = *(void **)last;
            }
            *(void **)last = node;
        } else {
            *listHead = node;
        }
    }
}

s32 sub_08000CC8(void **arg0, void *arg1)
{
    void *r2 = *arg0;
    if (r2 != 0) {
        do {
            if (*(void **)((u8 *)r2 + 4) == arg1) {
                return 1;
            }
            r2 = *(void **)r2;
        } while (r2 != 0);
    }
    return 0;
}
