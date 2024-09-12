#include <ae2f/DataStructure/Allocator.h>
#include <string.h>
#include <stdlib.h>

#define LEN_GETTER (*((size_t*)This->data))

static ae2f_errint_t Len(const ae2f_struct ae2f_ds_Alloc_Refer* This, size_t* buff) {
	if (!(This && This->data))
		return ae2f_errGlobal_PTR_IS_NULL;

	*buff = *((size_t*)This->data);

	return ae2f_errGlobal_OK;
}
static ae2f_errint_t Read(const ae2f_struct ae2f_ds_Alloc_Refer* This, size_t idx, void* buff, size_t bufflen) {
	if (!(This && This->data))
		return ae2f_errGlobal_PTR_IS_NULL;

	if (idx + bufflen > LEN_GETTER)
		return ae2f_errGlobal_WRONG_OPERATION;

	memcpy(buff, This->data + sizeof(size_t) + idx, bufflen);


	return ae2f_errGlobal_OK;
}
static ae2f_errint_t Write(const ae2f_struct ae2f_ds_Alloc_Refer* This, size_t idx, const void* buff, size_t bufflen) {
	if (!(This && This->data))
		return ae2f_errGlobal_PTR_IS_NULL;

	if (idx + bufflen > LEN_GETTER)
		return ae2f_errGlobal_WRONG_OPERATION;

	memcpy(This->data + sizeof(size_t) + idx, buff, bufflen);

	return ae2f_errGlobal_OK;
}
static ae2f_errint_t Make(ae2f_struct ae2f_ds_Alloc_Owner* This, size_t l) {
	if (!This)
		return ae2f_errGlobal_PTR_IS_NULL;

	void* _Try = This->data ? realloc(This->data, l + sizeof(size_t)) : calloc(l + sizeof(size_t), 1);

#define i ((size_t*)_Try)[0]
	if (_Try) {
		if (This->data) for (; i < l; i++)
			This->data[i] = 0;
	} else return ae2f_errGlobal_ALLOC_FAILED;

	This->data = _Try;
	i = l;
#undef i
	return ae2f_errGlobal_OK;
}
static ae2f_errint_t Del(ae2f_struct ae2f_ds_Alloc_Owner* This) {
	if (!This)
		return ae2f_errGlobal_PTR_IS_NULL;

	if (This->data) {
		free(This->data);
		This->data = 0;
	}

	return ae2f_errGlobal_OK;
}

const struct ae2f_ds_Alloc_vRefer ae2f_ds_Alloc_vRefer_cLinear = ae2f_ds_Alloc_vRefer_mPrm(Len, Read, Write);
const struct ae2f_ds_Alloc_vOwner ae2f_ds_Alloc_vOwner_cLinear = ae2f_ds_Alloc_vOwner_mPrm(Make, Del, Make);

ae2f_errint_t ae2f_ds_Alloc_vOwner_Init(
	ae2f_struct ae2f_ds_Alloc_Owner* This, 
	const ae2f_struct ae2f_ds_Alloc_vRefer* vRef, 
	const ae2f_struct ae2f_ds_Alloc_vOwner* vOwn
) {
	if (!This) return ae2f_errGlobal_PTR_IS_NULL;

	This->data = 0;
	This->vRefer = vRef ? vRef : &ae2f_ds_Alloc_vRefer_cLinear;
	This->vOwner = vOwn ? vOwn : &ae2f_ds_Alloc_vOwner_cLinear;

	return ae2f_errGlobal_OK;
}
ae2f_errint_t ae2f_ds_Alloc_vOwner_Copy(ae2f_struct ae2f_ds_Alloc_Owner* This, const ae2f_struct ae2f_ds_Alloc_Refer* Another) {
	size_t size; ae2f_errint_t err = ae2f_errGlobal_OK;
	if ((err = ae2f_ds_Alloc_vRefer_getSize(Another, &size)) != ae2f_errGlobal_OK) return err;
	if ((err = ae2f_ds_Alloc_vOwner_Make(This, size)) != ae2f_errGlobal_OK) return err;

	void* buff = malloc(size);
	if (!buff) return ae2f_errGlobal_ALLOC_FAILED;

	if ((err = ae2f_ds_Alloc_vRefer_Read(Another, 0, buff, size))) return err;
	if ((err = ae2f_ds_Alloc_vOwner_Write(This, 0, buff, size))) return err;

	free(buff);

	return err;
}