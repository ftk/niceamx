#ifndef API_VOTE_HPP
#define API_VOTE_HPP

#include "config.h"

#include <cassert>
#include <istream>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <map>

namespace api {
//

class vote
{
private:
  //util::strings candidates;
  typedef std::map<std::string, int> votes_map;
  votes_map candidates; // name - votes
public:
  void import_stream(std::istream& s)
  {
    std::string buf;
    while(std::getline(s, buf) && !buf.empty())
    {
      //candidates.push_back(buf);
      candidates[buf] = 0;
    }
  }
  inline std::size_t count()
  {
    return candidates.size();
  }

private:
  inline votes_map::iterator get_by_index(int idx)
  {
    //return candidates.at(idx).first;
    assert(idx < (int)count());
    auto it = candidates.begin();
    std::advance(it, idx);
    return it;
  }
public:
  inline const std::string& get(int idx)
  {
    return(get_by_index(idx)->first);
  }

  inline const std::string& get_random()
  {
    return get_by_index(rand() % count())->first;
  }
public:
  const std::string& get_highest()
  {
    assert(count() > 0);
    votes_map::const_iterator highest = candidates.cbegin();
    for(auto it = candidates.cbegin(), en = candidates.cend(); it != en; ++it)
    {
      if(it->second > highest->second)
        highest = it;
    }
    if(!highest->second)
      return get_random();
    return highest->first;
  }

  void vote_up(int idx)
  {
    auto it = get_by_index(idx);
    it->second++;
  }
  void vote_up(const std::string& name)
  {
    candidates[name] += 1;
  }
  void clear()
  {
    for(auto it = candidates.begin(), en = candidates.end(); it != en; ++it)
    {
      it->second = 0;
    }
  }

  void join(std::string& result, char lim)
  {
    for(auto it = candidates.begin(), en = candidates.end(); it != en; ++it)
    {
      if(it != candidates.cbegin())
	result += static_cast<char>(lim);
      result += it->first;
    }
  }
  std::string join(char lim)
  {
   std::string result = "";
    for(auto it = candidates.cbegin(), en = candidates.cend(); it != en; ++it)
    {
      if(it != candidates.cbegin())
        result += static_cast<char>(lim);
      result += it->first;
    }
    return result;
  }
};


} // namespace

#endif
