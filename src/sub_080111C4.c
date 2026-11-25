extern void sub_08000BE8(u8 *ptr);

/* Sprite-destruction thunk: free the model object whose pointer is passed in
 * r0 by forwarding it to the block allocator's free routine. */
void sub_080111C4(void *ptr) {
    sub_08000BE8(ptr);
}
