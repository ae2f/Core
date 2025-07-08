/**
 * @file errGlob.hpp
 * @author ae2f
 * @brief
 * @date 2025-02-01
 *
 * @copyright Copyright (c) 2025
 *
 */
#ifndef ae2f_errGlob_hpp
#define ae2f_errGlob_hpp


#include "BitVec.hpp"
#include "errGlob.h"
#include <exception>
#include <string>

#include "Pack/Beg.h"

namespace ae2f {

/// @brief
/// Gets the code
struct errGlobState {
  ae2f_err_t code;
  constexprmethod errGlobState(ae2f_err_t a) noexcept;

  /// @brief
  /// It is a constructor, which will throw it is a state critical.
  /// @param a
  /// Raw status code
  /// @return
  /// error parser for a.
  /// @see ae2f_errGlobNormalised
  static inline errGlobState errGlobStateWithThrow(ae2f_err_t a);

  /// @brief
  /// Gets one
  /// @return
  /// A single error message for this code.
  constexprmethod const char *peek() const noexcept {
    return (code & ae2f_errGlob_IMP_NOT_FOUND)
               ? "Failed to find the function on preprocessor which is "
                 "callable "
                 "for some reason No operation has beed done."
           : (code & ae2f_errGlob_PTR_IS_NULL)
               ? "Failed to refer the pointer either l-value inside the "
                 "function."
           : (code & ae2f_errGlob_FLUSH_FAILED) ? "Failed freeing the memory."
           : (code & ae2f_errGlob_ALLOC_FAILED)
               ? "stdlib allocating functions (malloc, calloc, realloc) has "
                 "been "
                 "failed."
           : (code & ae2f_errGlob_WRONG_OPERATION)
               ? "Found that parameter sent by programmer is invalid. The "
                 "operation may have been ceased while the middle."
           : (code & ae2f_errGlob_NFOUND)
               ? "Found some errors, but not by parameters. The operation has "
                 "failed."
           : (code & ae2f_errGlob_DONE_HOWEV)
               ? "The operation went done. Note that operation may not be "
                 "valid."
           : (code) ? "Unexpected flag."
                    : "The operation went done.";
  }

  /// @brief
  /// Pops an error with an error type.
  /// @return
  /// Error message
  constexprmethod errGlobState pop() const noexcept {
    return errGlobState(code & ~rBitVec<ae2f_err_t>(code).FndOne().obj);
  }

  /// @brief
  /// Generates the error message.
  /// @return
  /// A whole list of error messages.
  inline std::string msgall() const noexcept;
};

constexprmethod errGlobState::errGlobState(ae2f_err_t a) noexcept : code(a) {}
inline std::string errGlobState::msgall() const noexcept {
  std::string rtn = "Following shows the error flag enabled.";
  errGlobState err(this->code);

  while (err.code) {
    rtn += '\t';
    rtn += err.peek();
    err = err.pop();
    rtn += '\n';
  }

  return rtn;
}

/// @brief
/// Thrown error type.
class errGlobThrown : public std::exception {
  friend class errGlobState;

  errGlobState code;
  /// @brief
  /// Error message buffer;
  const std::string msg;

  inline errGlobThrown(const ae2f_err_t c) noexcept
      : code(c), msg(code.msgall()) {}

  inline virtual const char *what() const noexcept override {
    return msg.c_str();
  }
};

inline errGlobState errGlobState::errGlobStateWithThrow(ae2f_err_t a) {
  if (ae2f_errGlobNormalised(a))
    throw errGlobThrown(a);
  return a;
}

} // namespace ae2f
#include "Pack/End.h"

#endif
