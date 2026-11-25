extern s16 D_020279E0;  /* spawn budget of the general object class */
extern s16 D_020279E4;  /* spawn budget of the effect class */
void *sub_080014D0(s32, s32);
extern s32 sub_0805FBB4; /* destructor that refunds D_020279E4 */
extern s32 sub_0805FBCC; /* destructor that refunds D_020279E0 */

/* Allocate an object of `type` under `parent`, spending the effect-class spawn
 * budget first and the general budget as a fallback. Install the matching
 * slot-refund destructor at +0x24 and return the object, or NULL if none free. */
void *sub_0805FA88(s32 parent, s32 type) {
    void *obj;
    s32 *destructor;

    if ((s32)D_020279E4 <= 0) {
        if ((s32)D_020279E0 > 0) {
            obj = sub_080014D0(parent, type);
            if (obj != NULL) {
                D_020279E0 = (u16) D_020279E0 - 1;
                destructor = &sub_0805FBCC;
                goto installDestructor;
            }
        }
        return NULL;
    }
    obj = sub_080014D0(parent, type);
    if (obj != NULL) {
        D_020279E4 = (u16) D_020279E4 - 1;
        destructor = &sub_0805FBB4;
installDestructor:
        *(s32 **)((u8 *)obj + 0x24) = destructor;
        return obj;
    }
    return NULL;
}
