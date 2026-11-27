extern void spawnSceneObjectTableEntries(void *obj);

/* Thunk: forward the object pointer passed in r0 to the state-propagation
 * routine. */
void sub_08098748(void *obj) {
    spawnSceneObjectTableEntries(obj);
}
