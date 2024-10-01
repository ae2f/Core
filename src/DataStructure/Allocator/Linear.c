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
static ae2f_errint_t Write(ae2f_struct ae2f_ds_Alloc_Refer* This, size_t idx, const void* buff, size_t bufflen) {
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

ae2f_SHAREDEXPORT const struct ae2f_ds_Alloc_vRefer ae2f_ds_Alloc_vRefer_cLinear = { .getSize = Len, .Read = Read, .Write = Write };
ae2f_SHAREDEXPORT const struct ae2f_ds_Alloc_vOwner ae2f_ds_Alloc_vOwner_cLinear = { .Del = Del, .reSize = Make };