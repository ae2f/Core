/**
 * @file ae2f/Guide.h
 * @brief
 * Guide markers for conventions.
 * */
#undef ae2f_LP
#undef ae2f_NONE
#undef ae2f_opt

/** @def ae2f_NONE @brief nothing. */
#define ae2f_NONE

/** 
 * @def ae2f_LP
 *
 * @brief 
 * Desired count required. 
 * 
 * @param ...
 * Parameter with this preprocessor means \n
 * the pointer is considered as list, and inside of this is a desired size.
 * */
#define	ae2f_LP(a) ae2f_NONE

/** @def ae2f_opt @brief Optional. */
#define ae2f_opt		ae2f_NONE

/** 
 * @def ae2f_FREE 
 * @brief Use this marker to show the desired functions
 * 	to effectively free the resources.
 * */
#define ae2f_FREE(a)		ae2f_NONE


/**
 * @def	ae2f_BITFIELD
 * @brief	Use this to notify the user that
 * 		it expects `a` type.
 *
 * @details	Useful when standard typedef is not possible.
 * */
#define ae2f_TYPEDEF(a)	ae2f_NONE

/** @brief l_value. */
#define ae2f_v ae2f_NONE
