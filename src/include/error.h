/** Copyright (C) 2023 Muqiu Han <muqiu-han@outlook.com> */

#ifndef MOS_ERROR_H
#define MOS_ERROR_H

#include "log.h"
#include <cerrno>
#include <cstdint>
#include <cstring>
#include <exception>
#include <map>
#include <string>

namespace mos::error
{
  enum class Code
  {
    Undefined,
    MOS,
    System_call,
  };

  inline const std::map<Code, const char *> CODE_TO_STRING = {
    { Code::Undefined, "Unknown" },
    { Code::System_call, "System call" },
    { Code::MOS, "MOS" },
  };

  class Err
  {
   public:
    Err() { std::terminate(); }

    Err(const Code code,
        std::string custom,
        const uint32_t line,
        const char * file,
        const char * function)
    {
      const char * err_type = CODE_TO_STRING.at(code);
      const std::string custom_msg = [&]() {
        if (custom.empty())
          return std::string("");
        else
          return (": " + custom);
      }();

      log_msg("%s Error with ERRNO(%d) -> %s%s in function `%s` at <%s:%d>",
              err_type,
              errno,
              std::strerror(errno),
              custom_msg.c_str(),
              function,
              file,
              line);

      std::terminate();
    }
  };

}

#define ERR(CODE) Err(mos::error::Err(CODE, "", __LINE__, __FILE__, __FUNCTION__))
#define ERR_MSG(CODE, MSG)                                                               \
  Err(mos::error::Err(CODE, MSG, __LINE__, __FILE__, __FUNCTION__))

#endif /* sinbuger_ERROR_H */
