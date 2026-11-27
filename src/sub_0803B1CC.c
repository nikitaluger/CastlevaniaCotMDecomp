extern void unlinkAndFreeObject(void *);

/* Three sub-objects owned by a state block (state+0x54), freed by
 * unlinkAndFreeObject when still allocated. */
struct OwnedObjects {
    void *obj0;
    void *obj1;
    void *obj2;
};

/* Free the three sub-objects owned by this block, skipping empty slots. */
void sub_0803B1CC(struct OwnedObjects *res) {
    if (res->obj0 != 0) {
        unlinkAndFreeObject(res->obj0);
    }
    if (res->obj1 != 0) {
        unlinkAndFreeObject(res->obj1);
    }
    if (res->obj2 != 0) {
        unlinkAndFreeObject(res->obj2);
    }
}
