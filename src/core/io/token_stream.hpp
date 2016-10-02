#pragma once

#include <core/typedefs.hpp>
#include <core/token.hpp>
#include <core/reg.hpp>

/*!
 * @brief Binary token stream reader
 */
class TokenStream {
public:
  TokenStream(const byte* input);

  /*!
   * @brief Read sizeof(T) bytes and return them as T object
   * @tparam T type to be fetched from stream
   */
  template<class T> T read();

  //! @brief Read single uninterpreted byte from stream
  byte read_byte() noexcept;

  //! @brief Read N uninterpreted bytes from stream
  const byte* read_bytes(int count) noexcept;

private:
  //! @brief Current position in input buffer
  const byte* $pos;
};
