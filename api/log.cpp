/*
#include "log.hpp"

#include <sstream>
#include <ctime>

namespace api {
//

log_t * log_t::instance = NULL;
log_t * log_t::get_instance()
{
  if(!instance)
    instance = new log_t;
  return instance;
}

void log_t::rm_instance()
{
  if(instance)
  {
    delete instance;
    instance = NULL;
  }
}

static inline time_t get_timestamp()
{
  return time(NULL);
}


void log_t::write_common(const std::string& cat, const std::string& subcat, const std::string& subsubcat, const std::string& message)
{
  format_text("common", cat, subcat, subsubcat, message);
}
void log_t::write_player(const std::string& cat, const std::string& subcat, const std::string& subsubcat, int playerid, const std::string& message)
{
  //std::ostringstring msg;
  
}
void log_t::format_text(const std::string& group, const std::string& cat, const std::string& subcat, const std::string& subsubcat, const std::string& message)
{
  const char separator = ':';
  
  std::ostringstream line;

  time_t timestamp = get_timestamp();
  std::string date;
  format_time(timestamp, date);

  line <<
    date << separator << // readable time
    timestamp << separator << // unreadable time
    group << separator <<
    cat << separator <<
    subcat << separator <<
    subsubcat << separator <<
    message << std::endl;

  write_line(line.str());
}
void log_t::format_time(long timestamp, std::string& buf)
{
  using namespace std;
  //time_t timestamp = get_timestamp();
  struct tm * timedate;
  timedate = localtime(&timestamp);
  char str[80];
  strftime(str, sizeof(str) / sizeof(*str), "%H-%M-%S", timedate);
  buf = str;
}


}
*/