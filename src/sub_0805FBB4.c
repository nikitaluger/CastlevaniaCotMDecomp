extern void sub_08002D7C(void *obj);

/* Destroy `obj` together with its children and release one instance slot of
 * this object type (the per-type slot counter at 0x020279E4 goes back up). */
void sub_0805FBB4(void *obj)
{
    *(vu16 *)0x020279E4 += 1;
    sub_08002D7C(obj);
}
