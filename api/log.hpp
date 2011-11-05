/*
#ifndef API_LOG_HPP
#define API_LOG_HPP

#include "config.h"

#include <string>
#include <fstream>

namespace api {
//
class log_t
{
  // singleton
private:
  log_t() {}

  static log_t * instance;
public:
  static log_t * get_instance();
  static void rm_instance();

private:
  std::ofstream log_file;
  //long timestamp;
public:
  void write_common(const std::string& cat, const std::string& subcat, const std::string& subsubcat, const std::string& message);
  void write_player(const std::string& cat, const std::string& subcat, const std::string& subsubcat, int playerid, const std::string& message);
private:
  void write_line(const std::string& message);
  void format_text(const std::string& group, const std::string& cat, const std::string& subcat, const std::string& subsubcat, const std::string& message);
  static void format_time(long timestamp, std::string& buf);
};

}

#endif // API_LOG_HPP
*/
