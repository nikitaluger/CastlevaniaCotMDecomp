extern void sub_08002D7C(void *entity);

/* Return the entity's pool slot to the free counter at 0x020279E0, then
 * destroy the entity and its children. */
void sub_0805FBCC(void *entity)
{
    *(vu16 *)0x020279E0 += 1;
    sub_08002D7C(entity);
}
