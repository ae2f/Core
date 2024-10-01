#include <ae2f/DataStructure/Array.h>
#include <stdlib.h>
#include <stdio.h>

ae2f_SHAREDEXPORT ae2f_errint_t ae2f_ds_Arr_BSearch_imp(
	const struct ae2f_ds_Alloc_Refer* arr,
	const void* wanted,
	size_t elsize,
	const ae2f_ds_Arr_fpElCmp_t fpElCmp,
	size_t* out
) {
	if (!out) return ae2f_errGlobal_PTR_IS_NULL;
	if (!fpElCmp) return ae2f_errGlobal_IMP_NOT_FOUND;

	ae2f_errint_t err; size_t arr_r, arr_l = 0;
	if ((err = ae2f_ds_Alloc_vRefer_getSize(arr, &arr_r)) != ae2f_errGlobal_OK) 
		return err;
	arr_r /= elsize;
	arr_r--;

	void* el = calloc(elsize, 1);
	if (!el) {
		return ae2f_errGlobal_ALLOC_FAILED;
	}

/// it ends the entire function
#define memdump(code) { free(el); return (code); }

	while (arr_l <= arr_r) {
#define idx (arr_l + ((arr_r - arr_l) >> 1))
		if ((err = ae2f_ds_Alloc_vRefer_Read(arr, idx * elsize, el, elsize)) != ae2f_errGlobal_OK) {
			memdump(err);
		}

		ae2f_ds_Arr_Compared_t got = fpElCmp(el, wanted);

		if (got == ae2f_ds_Arr_EQUAL) {
			out[0] = idx;
			memdump(ae2f_errGlobal_OK);
		}
		else if (got > ae2f_ds_Arr_EQUAL) {
			arr_r = idx - 1;
		}
		else {
			arr_l = idx + 1;
		}
	}

	memdump(ae2f_ds_Arr_BSearch_NOT_FOUND);

#undef idx
#undef memdump
}

#pragma region qsort
#define __Read(i, buff) ae2f_ds_Alloc_vRefer_Read(arr, (i) * elsize, buff, elsize)
#define __Write(i, buff) ae2f_ds_Alloc_vRefer_Write(arr, (i) * elsize, buff, elsize)

static ae2f_errint_t imp_ae2f_swap(
	struct ae2f_ds_Alloc_Refer* arr,
	size_t elsize,
	void* tmpA,
	void* tmpB,
	size_t iA,
	size_t iB
) {
	ae2f_errint_t err;

	if ((err = __Read(iA, tmpA)) != ae2f_errGlobal_OK)
		return err;

	if ((err = __Read(iB, tmpB)) != ae2f_errGlobal_OK)
		return err;

	if ((err = __Write(iA, tmpB)) != ae2f_errGlobal_OK)
		return err;

	if ((err = __Write(iB, tmpA)) != ae2f_errGlobal_OK)
		return err;

	return ae2f_errGlobal_OK;
}

static ae2f_errint_t imp_ae2f_partition(
	struct ae2f_ds_Alloc_Refer* arr,
	size_t elsize,
	const ae2f_ds_Arr_fpElCmp_t fpElCmp,
	void* tempel,
	void* pivot,
	size_t* idx_buff,
	size_t idx_low,
	size_t idx_high
) {

	ae2f_errint_t err;
	if ((err = __Read(idx_high, pivot)) != ae2f_errGlobal_OK)
		return err;

	size_t i = idx_low - 1;

	for (size_t j = idx_low; j < idx_high; j++) {
		if ((err = __Read(j, tempel)) != ae2f_errGlobal_OK)
			return err;

		if (fpElCmp(tempel, pivot) <= ae2f_ds_Arr_EQUAL) {

			i++; // i, j
			if ((err = imp_ae2f_swap(arr, elsize, pivot, tempel, i, j)) != ae2f_errGlobal_OK)
				return err;
			
			if ((err = __Read(idx_high, pivot)) != ae2f_errGlobal_OK)
				return err;
		}
	}

	if ((err = imp_ae2f_swap(arr, elsize, pivot, tempel, i + 1, idx_high)) != ae2f_errGlobal_OK) 
		return err;

	idx_buff[0] = i + 1;
	return ae2f_errGlobal_OK;
}

#define inv_idx ((size_t)-1)

static ae2f_errint_t imp_ae2f_Qsort(
	struct ae2f_ds_Alloc_Refer* arr,
	size_t elsize,
	const ae2f_ds_Arr_fpElCmp_t fpElCmp,
	void* tempel,
	void* pivot,
	size_t idx_low,
	size_t idx_high
) {
	ae2f_errint_t err;
	if (idx_low >= idx_high)
		return ae2f_errGlobal_OK;

	size_t pvtIdx;
	if ((err = imp_ae2f_partition(arr, elsize, fpElCmp, tempel, pivot, &pvtIdx, idx_low, idx_high)) != ae2f_errGlobal_OK)
		return err;

	if(pvtIdx != 0)
	if ((err = imp_ae2f_Qsort(arr, elsize, fpElCmp, tempel, pivot, idx_low, pvtIdx - 1)) != ae2f_errGlobal_OK)
		return err;

	

	err = imp_ae2f_Qsort(arr, elsize, fpElCmp, tempel, pivot, pvtIdx + 1, idx_high);
	return err;

#undef inv_idx
}

ae2f_SHAREDEXPORT ae2f_errint_t ae2f_ds_Arr_QSort_imp(
	struct ae2f_ds_Alloc_Refer* arr,
	size_t elsize,
	const ae2f_ds_Arr_fpElCmp_t fpElCmp
) {
	if (!fpElCmp) return ae2f_errGlobal_IMP_NOT_FOUND;

	size_t len;
	ae2f_errint_t rtn;
	if (rtn = ae2f_ds_Alloc_vRefer_getSize(arr, &len) != ae2f_errGlobal_OK)
		return rtn;

	void* tmpel = calloc(1, elsize);
	if (!tmpel) return ae2f_errGlobal_ALLOC_FAILED;

	void* pvt = calloc(1, elsize);
	if (!pvt) { free(tmpel); return ae2f_errGlobal_ALLOC_FAILED; }

	rtn = imp_ae2f_Qsort(arr, elsize, fpElCmp, tmpel, pvt, 0, (len / elsize) - 1);

	free(tmpel);
	free(pvt);

	return rtn;
}

#undef __Read
#undef __Write
#pragma endregion