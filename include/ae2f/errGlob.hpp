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

#include "errGlob.h"
#include <exception>
#include <string>

#include "BitVec.hpp"
#include "Pack/Beg.h"

namespace ae2f {
/// @brief
/// Gets the code
struct errGlobState {
  ae2f_err_t code;
  inline errGlobState(ae2f_err_t a) noexcept;

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
    if (code & ae2f_errGlob_IMP_NOT_FOUND) {
      return "Failed to find the function on preprocessor which is callable "
             "for some reason No operation has beed done.";
    }

    if (code & ae2f_errGlob_PTR_IS_NULL) {
      return "Failed to refer the pointer either l-value inside the function.";
    }

    if (code & ae2f_errGlob_FLUSH_FAILED) {
      return "Failed freeing the memory.";
    }

    if (code & ae2f_errGlob_ALLOC_FAILED) {
      return "stdlib allocating functions (malloc, calloc, realloc) has been "
             "failed.";
    }

    if (code & ae2f_errGlob_WRONG_OPERATION) {
      return "Found that parameter sent by programmer is invalid. The "
             "operation may have been ceased while the middle.";
    }

    if (code & ae2f_errGlob_NFOUND) {
      return "Found some errors, but not by parameters. The operation has "
             "failed.";
    }

    if (code & ae2f_errGlob_DONE_HOWEV) {
      return "The operation went done. Note that operation may not be valid.";
    }

    if (code) {
      return "Unexpected flag.";
    }

    return "The operation went done.";
  }

  /// @brief
  /// Pops an error with an error type.
  /// @return
  /// Error message
  constexprmethod void pop() noexcept {
    code &= ~rBitVec<ae2f_err_t>(code).FndOne().obj;
  }

  /// @brief
  /// Generates the error message.
  /// @return
  /// A whole list of error messages.
  inline std::string msgall() const noexcept;
};

inline errGlobState::errGlobState(ae2f_err_t a) noexcept : code(a) {}
inline std::string errGlobState::msgall() const noexcept {
  std::string rtn = "Following shows the error flag enabled.";
  errGlobState err(this->code);

  while (err.code) {
    rtn += '\t';
    rtn += err.peek();
    err.pop();
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
