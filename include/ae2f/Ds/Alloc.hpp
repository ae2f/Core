#include "./Alloc.h"

#if !defined(ae2f_ds_Alloc_hpp)
#define ae2f_ds_Alloc_hpp

namespace ae2f { namespace Ds { namespace Alloc {
	struct xrOwner;

	/// @brief 
	/// @tparam __imp 
	/// @see ae2f::Ds::Alloc::iOwner
	template<const ae2f_ds_vAlloc* __imp>
	struct vfDef {
		static constexpr ae2f_ds_vAlloc* ___vRef() noexcept { return __imp; }
	};
}}}

#include "Alloc/Defs.hpp"
#include "Alloc/Ref.hpp"
#include "Alloc/Own.hpp"

namespace ae2f { namespace Ds { namespace Alloc {

	constexpr cRefer::cRefer(const xrOwner& r) noexcept : cRefer(ae2f_ds_Alloc_cRef_Mk(&r)) {}

	/// @brief 
	/// Pre-defined implementations of @ref ae2f::Ds::Alloc::iOwner
	namespace cOwner {
		/// @brief
		/// Each elements will be physically linear.
		/// @see ae2f::Ds::Alloc::iOwner
		/// @see ae2f_ds_vAlloc_cLinear
		using Linear_t = iOwner<&ae2f_ds_vAlloc_cLinear>;
	}
}}}

#endif