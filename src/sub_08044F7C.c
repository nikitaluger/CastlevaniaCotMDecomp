void advanceMotion(s32 obj, s32 delta);
void stepAnimationTrack(s32 parent, s32 objSub);

/* Advance the physics sub-object at +0x3C by one step (zero extra delta), then
 * dispatch the parent's (+0x38) script slot callback using the sub-object's
 * slot table at +0x34. */
void sub_08044F7C(void *self) {
    s32 parent;
    s32 obj;
    s32 objSub;
    parent = *((s32 *) ((s8 *) self + 0x38));
    obj = *((s32 *) ((s8 *) self + 0x3C));
    objSub = obj + 0x34;
    advanceMotion(obj, 0);
    stepAnimationTrack(parent, objSub);
}
