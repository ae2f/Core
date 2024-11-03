#include <ae2f/Ds/Alloc.h>
#include <stdlib.h>



ae2f_SHAREDEXPORT ae2f_extern ae2f_errint_t ae2f_ds_Alloc_cOwn_Init(
	ae2f_struct ae2f_ds_Alloc_cOwn* This, 
	const ae2f_struct ae2f_ds_vAlloc* imp
) {
	if (!(This)) return ae2f_errGlob_PTR_IS_NULL;
	if (!imp) return ae2f_ds_Alloc_cOwn_Init_FPIMPNULL;

	This->data = 0;
	This->v = imp;

	return ae2f_errGlob_OK;
}

ae2f_SHAREDEXPORT ae2f_errint_t ae2f_ds_Alloc_cOwn_Cpy_imp(
	ae2f_struct ae2f_ds_Alloc_cOwn* This, 
	const ae2f_struct ae2f_ds_cAlloc* Another
) {
	if(!(This && Another)) 
	return ae2f_errGlob_PTR_IS_NULL;

	size_t size, elsize; ae2f_errint_t err = ae2f_errGlob_OK;
	
	if ((err = ae2f_ds_Alloc_cRef_getSize(Another, &size, &elsize)))
	return err;

	void* buff = calloc(size, elsize);
	if (!buff) return ae2f_errGlob_ALLOC_FAILED;
	
	if ((err = ae2f_ds_Alloc_cRef_Read(Another, 0, buff, size)))
		goto __GlobalFree;

	if ((err = ae2f_ds_Alloc_cOwn_ReConfig(This, size, elsize)))
		goto __GlobalFree;

	if ((err = ae2f_ds_Alloc_cOwn_Write(This, 0, buff, size * elsize)))
		goto __This_Architect_Failed;

	goto __GlobalFree;

	/// # Error occurred after `This`  
	__This_Architect_Failed:
	/// # Normal Error, from This not implemented.
	__GlobalFree:
	free(buff);
	return err;
}