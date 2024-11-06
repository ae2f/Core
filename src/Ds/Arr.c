#include <ae2f/Ds/Arr.h>
#include <stdlib.h>
#include <stdio.h>

ae2f_SHAREDEXPORT ae2f_errint_t ae2f_ds_Arr_BSearch_imp(
	const struct ae2f_ds_cAlloc* arr,
	const void* wanted,
	const ae2f_ds_Arr_fpElCmp_t fpElCmp,
	size_t* out,
	size_t _elsize
) {
	if (!out) return ae2f_errGlob_PTR_IS_NULL;
	if (!fpElCmp) return ae2f_errGlob_IMP_NOT_FOUND;

	ae2f_errint_t err; 
	size_t arr_r, arr_l = 0, elsize;
	
	if ((err = ae2f_ds_Alloc_cRef_getSize(arr, &arr_r, &elsize))) 
		return err;

	if(_elsize) {
		arr_r = arr_r * elsize / _elsize;
		elsize = _elsize;
	} else if(!elsize) {
		return ae2f_errGlob_WRONG_OPERATION;
	}

	arr_r--;


	void* el = calloc(elsize, 1);
	if (!el) {
		return ae2f_errGlob_ALLOC_FAILED;
	}

/// it ends the entire function
#define memdump(code) { free(el); return (code); }

	while (arr_l <= arr_r) {
#define idx (arr_l + ((arr_r - arr_l) >> 1))
		if ((err = ae2f_ds_Alloc_cRef_Read(arr, idx * elsize, el, elsize))) {
			memdump(err);
		}

		ae2f_ds_Arr_CmpRet_t got = fpElCmp(el, wanted);

		if (got == ae2f_ds_Arr_EQUAL) {
			out[0] = idx;
			memdump(ae2f_errGlob_OK);
		}
		else if (got > ae2f_ds_Arr_EQUAL) {
			arr_r = idx - 1;
		}
		else {
			arr_l = idx + 1;
		}
	}

	memdump(ae2f_ds_Arr_NOT_FOUND);

#undef idx
#undef memdump
}

#pragma region qsort
#define __Read(i, buff) ae2f_ds_Alloc_cRef_Read(arr, (i) * elsize, buff, elsize)
#define __Write(i, buff) ae2f_ds_Alloc_cRef_Write(arr, (i) * elsize, buff, elsize)

static ae2f_errint_t imp_ae2f_swap(
	struct ae2f_ds_cAlloc* arr,
	size_t elsize,
	void* tmpA,
	void* tmpB,
	size_t iA,
	size_t iB
) {
	ae2f_errint_t err;

	if ((err = __Read(iA, tmpA)))
		return err;

	if ((err = __Read(iB, tmpB)))
		return err;

	if ((err = __Write(iA, tmpB)))
		return err;

	if ((err = __Write(iB, tmpA)))
		return err;

	return ae2f_errGlob_OK;
}

static ae2f_errint_t imp_ae2f_partition(
	struct ae2f_ds_cAlloc* arr,
	size_t elsize,
	const ae2f_ds_Arr_fpElCmp_t fpElCmp,
	void* tempel,
	void* pivot,
	size_t* idx_buff,
	size_t idx_low,
	size_t idx_high
) {

	ae2f_errint_t err;
	if ((err = __Read(idx_high, pivot)))
		return err;

	size_t i = idx_low - 1;
	printf("i %d\n", i);

	for (size_t j = idx_low; j < idx_high; j++) {
		printf("j %d\n", j);

		if ((err = __Read(j, tempel)))
			return err;

		if (fpElCmp(tempel, pivot) <= ae2f_ds_Arr_EQUAL) {
			i++; // i, j
			if ((err = imp_ae2f_swap(arr, elsize, pivot, tempel, i, j)))
				return err;
			
			if ((err = __Read(idx_high, pivot)))
				return err;
		}
	}

	if ((err = imp_ae2f_swap(arr, elsize, pivot, tempel, i + 1, idx_high))) 
		return err;

	idx_buff[0] = i + 1;
	return ae2f_errGlob_OK;
}

#define inv_idx ((size_t)-1)

struct __ {
	struct ae2f_ds_cAlloc* arr;
	size_t elsize;
	const ae2f_ds_Arr_fpElCmp_t fpElCmp;
	void* tempel;
	void* pivot;
	size_t idx_low;
	size_t idx_high;
};

static ae2f_errint_t imp_ae2f_Qsort(
	struct __* prm
) {
	ae2f_errint_t err;

	printf("idx: %d %d\n", prm->idx_low, prm->idx_high);

	if (prm->idx_low >= prm->idx_high) {
		return ae2f_errGlob_OK;
	}

	size_t pvtIdx;
	if ((err = imp_ae2f_partition(prm->arr, prm->elsize, prm->fpElCmp, prm->tempel, prm->pivot, &pvtIdx, prm->idx_low, prm->idx_high)))
		return err;

	if(pvtIdx != 0) {
		prm->idx_high = pvtIdx - 1;
		return ae2f_errGlob_DONE_HOWEV;
	}	
	
	prm->idx_low = pvtIdx + 1;
	return ae2f_errGlob_DONE_HOWEV;

#undef inv_idx
}

ae2f_SHAREDEXPORT ae2f_errint_t ae2f_ds_Arr_QSort_imp(
	struct ae2f_ds_cAlloc* arr,
	const ae2f_ds_Arr_fpElCmp_t fpElCmp,
	size_t _elsize
) {
	if (!fpElCmp) return ae2f_errGlob_IMP_NOT_FOUND;

	size_t len, elsize;
	ae2f_errint_t rtn;
	if (rtn = ae2f_ds_Alloc_cRef_getSize(arr, &len, &elsize))
		return rtn;
	struct __ prm = {
		.arr = arr,
		.elsize = elsize,
		.fpElCmp = fpElCmp,
		.tempel = 0,
		.pivot = 0,
		.idx_low = 0,
		.idx_high = len - 1
	};

	if(_elsize) {
		prm.elsize = _elsize;
		prm.idx_high = (len * elsize / _elsize) - 1;
	} else if(!elsize) {
		return ae2f_errGlob_WRONG_OPERATION;
	}

	void* tmpel = calloc(1, elsize);
	if (!tmpel) return ae2f_errGlob_ALLOC_FAILED;

	void* pvt = calloc(1, elsize);
	if (!pvt) { free(tmpel); return ae2f_errGlob_ALLOC_FAILED; }

	prm.tempel = tmpel;
	prm.pivot = pvt;

	int _rtn;
	while(((_rtn = imp_ae2f_Qsort(&prm))) & ae2f_errGlob_DONE_HOWEV) {
		rtn |= _rtn;
	}
	

	free(tmpel);
	free(pvt);

	return rtn;
}

#undef __Read
#undef __Write
#pragma endregion