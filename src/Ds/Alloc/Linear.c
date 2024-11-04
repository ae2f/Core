#include <ae2f/Ds/Alloc.h>
#include <string.h>
#include <stdlib.h>

#define LEN_GETTER (*((size_t*)This->data))
#define ELSIZE_GETTER (((size_t*)This->data)[1])
#define BUFF_GETTER ((uint8_t*)(((size_t*)This->data) + 2))
#define BUFFLEN (LEN_GETTER * ELSIZE_GETTER)


static ae2f_errint_t Len(const ae2f_struct ae2f_ds_cAlloc* This, size_t* buff, size_t* one) {
	ae2f_errint_t err = ae2f_errGlob_OK; 

	if (!(This))
		return ae2f_errGlob_PTR_IS_NULL;

	size_t
	p_sz = ((size_t*)This->data) ? LEN_GETTER : 0,
	p_el = ((size_t*)This->data) ? ELSIZE_GETTER : 0;

	if(buff) *buff = p_sz;
	else err |= ae2f_ds_Alloc_Err_NCOPIED;

	if(one) *one = p_el;
	else err |= ae2f_ds_Alloc_Err_NCOPIED;
	return err;
}
static ae2f_errint_t Read(const ae2f_struct ae2f_ds_cAlloc* This, size_t idx, void* buff, size_t bufflen) {
	if (!(This && This->data))
		return ae2f_errGlob_PTR_IS_NULL;

	if (idx + bufflen > BUFFLEN)
		return ae2f_ds_Alloc_Err_IDX_INVALID;

	memcpy(buff, BUFF_GETTER + idx, bufflen);


	return ae2f_errGlob_OK;
}
static ae2f_errint_t Write(ae2f_struct ae2f_ds_cAlloc* This, size_t idx, const void* buff, size_t bufflen) {
	if (!(This && This->data))
		return ae2f_errGlob_PTR_IS_NULL;

	if (idx + bufflen > BUFFLEN)
		return ae2f_ds_Alloc_Err_IDX_INVALID;

	memcpy(BUFF_GETTER + idx, buff, bufflen);

	return ae2f_errGlob_OK;
}
static ae2f_errint_t Make(ae2f_struct ae2f_ds_cAlloc* This, size_t l, size_t ellen) {
	if (!This)
		return ae2f_errGlob_PTR_IS_NULL;

	l *= ellen;

	void* _Try = This->data ? realloc(This->data, l + (sizeof(size_t) << 1)) : calloc(l + (sizeof(size_t) << 1), 1);

#define _i (((size_t*)_Try)[0] * ((size_t*)_Try)[1])

	if (_Try) {
		if (This->data) for (int i = _i; i < l; i++)
			This->data[i] = 0;
	} else return ae2f_errGlob_ALLOC_FAILED;

	This->data = _Try;
	LEN_GETTER = l / ellen;
	ELSIZE_GETTER = ellen;
	
#undef i
	return ae2f_errGlob_OK;
}
static ae2f_errint_t Del(ae2f_struct ae2f_ds_cAlloc* This) {
	if (!This)
		return ae2f_errGlob_PTR_IS_NULL;

	if (This->data) {
		free(This->data);
		This->data = 0;
	}

	return ae2f_errGlob_OK;
}

ae2f_SHAREDEXPORT const struct ae2f_ds_vAlloc ae2f_ds_vAlloc_cLinear = 
{ 
	.GetSize = Len, 
	.Read = Read, 
	.Write = Write,

	.Del = Del,
	.ReConfig = Make
};