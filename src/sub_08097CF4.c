extern void sub_08002D7C(void *);

/* Kind-1 spawn budget at 0x020279E0 (refunded when one of these despawns). */
#define gSpawnBudget (*(vu16 *)0x020279E0)
/* Number of live objects tracked by this actor pool. */
#define gObjCount (*(vu16 *)0x020213DC)

/* Recycle a kind-1 object: refund its spawn-budget slot, drop the live-object
 * count, then run the object's destructor (unlink and release its resources). */
void sub_08097CF4(void *obj) {
    gSpawnBudget += 1;
    gObjCount -= 1;
    sub_08002D7C(obj);
}
