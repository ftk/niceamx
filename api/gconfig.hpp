#ifndef API_GCONFIG_HPP
#define API_GCONFIG_HPP

#include "util/singleton.hpp"

//#include <unordered_map>
#include <map>
#include <string>



namespace api {


class config : public util::singleton<config>
{
private:
	
	//std::unordered_map<std::string, std::string> dict;
	std::map<std::string, std::string> dict;
	
public:
	
	inline const std::string& get(const std::string& pname) const
	{
		return dict.at(pname);
	}
	inline void get(const std::string& pname, std::string& dest)
	{
		dest = dict.at(pname);
	}

	inline void set(const std::string& pname, const std::string& value)
	{
		dict[pname] = value;
	}
	
	inline bool exists(const std::string& pname) const
	{
		return !!dict.count(pname);
	}

};



} //

#define CONFIGBOX (api::config::get_instance())
#endif

