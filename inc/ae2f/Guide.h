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
#define	ae2f_LP(...) ae2f_NONE

/** @def ae2f_opt @brief Optional. */
#define ae2f_opt ae2f_NONE
