void sub_0801604C(void *obj);

/* If the object's flag word at +2 has bit 0 set, also set flag 0x400, then run
 * the object's slot-copy/position update (sub_0801604C). arg0 is the unused
 * owner. */
void sub_08090A5C(void *owner, void *obj) {
    if (1 & *(u16 *)((s8 *)obj + 2)) {
        *(u16 *)((s8 *)obj + 2) = (0x80 << 3) | *(u16 *)((s8 *)obj + 2);
    }
    sub_0801604C(obj);
}
