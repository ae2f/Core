#include <ae2f/DataStructure/Allocator.h>
// #include <string.h>
#include <stdlib.h>

ae2f_SHAREDEXPORT ae2f_errint_t ae2f_ds_Alloc_vOwner_Init(
	struct ae2f_ds_Alloc_Owner* This, 
	const ae2f_struct ae2f_ds_Alloc_vRefer* vRef, 
	const ae2f_struct ae2f_ds_Alloc_vOwner* vOwn
) {
	if (!(This && vRef && vOwn)) return ae2f_errGlobal_PTR_IS_NULL;

	This->data = 0;
	This->vRefer = vRef;
	This->vOwner = vOwn;

	return ae2f_errGlobal_OK;
}

ae2f_SHAREDEXPORT ae2f_errint_t ae2f_ds_Alloc_vOwner_Copy_imp(
	ae2f_struct ae2f_ds_Alloc_Owner* This, 
	const ae2f_struct ae2f_ds_Alloc_Refer* Another
) {
	if(!(This && Another)) 
	return ae2f_errGlobal_PTR_IS_NULL;

	size_t size; ae2f_errint_t err = ae2f_errGlobal_OK;
	if ((err = ae2f_ds_Alloc_vRefer_getSize(Another, &size)) != ae2f_errGlobal_OK) return err;

	void* buff = malloc(size);
	if (!buff) return ae2f_errGlobal_ALLOC_FAILED;
	
	if ((err = ae2f_ds_Alloc_vRefer_Read(Another, 0, buff, size)) != ae2f_errGlobal_OK)
		goto __GlobalFree;

	if ((err = ae2f_ds_Alloc_vOwner_reSize(This, size)) != ae2f_errGlobal_OK)
		goto __GlobalFree;

	if ((err = ae2f_ds_Alloc_vOwner_Write(This, 0, buff, size)) != ae2f_errGlobal_OK)
		goto __This_Architect_Failed;

	goto __GlobalFree;

	/// # Error occurred after `This`  
	__This_Architect_Failed:
	ae2f_ds_Alloc_vOwner_Del(This);

	/// # Normal Error, from This not implemented.
	__GlobalFree:
	free(buff);
	return err;
}