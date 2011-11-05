#ifndef API_PARSERS_HPP
#define API_PARSERS_HPP

#include "util/point.hpp"
#include "util/rotation.hpp"

#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>

#include <string>
#include <istream>


#include "object.hpp"

namespace api {

class basic_parser
{
public:
  struct node
  {};
  
protected:
  //typedef bool (*func_t)(node);
public:
  //virtual static bool load(std::istream& s, func_t fn) = 0;
  
  virtual ~basic_parser() {}
};


class basic_object_parser : public basic_parser
{
public:
  struct node
  {
    virtual object to_object() = 0;
  };
  
  virtual ~basic_object_parser() {}
};


#define PARSE_PHRASE(l) boost::spirit::qi::phrase_parse(first, last, (l), boost::spirit::ascii::space)
// IPL parser

class ipl_parser : public basic_object_parser
{
  
  // example:
  // 5472, od_walkway3, 0, 2680.37, -2751.8, 1.55, 0, 0, 0.104528375299, 0.994521904614, -1
  
public:
  
    struct node
    {
      int modelid;
      //std::string modelname; // unused
      int interior;
      util::point3d pos;
      util::quaternion rot;
      //int lod; // unused
      
      node() : modelid(0), //modelname(),
	  interior(0), pos(), rot()/*, lod(-1)*/ {}

	  object to_object()
      {
		util::euler ang = rot.to_euler();
		return object(modelid, pos, ang, interior);
      }
      
    };

    template <typename Iterator>
    static bool parse(Iterator first, Iterator last, node& obj)
    {
	namespace qi = boost::spirit::qi;

        using qi::float_;
        using qi::int_;
        using boost::spirit::ascii::char_;
        using qi::_1;
	
        using boost::phoenix::ref;
	
	
        bool r = PARSE_PHRASE
            //  Begin grammar
            (
	      int_[ref(obj.modelid) = _1] >> ',' >>
	      qi::lexeme[+(char_ - ',')] >> ',' >> // unused
	      int_[ref(obj.interior) = _1] >> ',' >>
	      float_[ref(obj.pos.x) = _1] >> ',' >>
	      float_[ref(obj.pos.y) = _1] >> ',' >>
	      float_[ref(obj.pos.z) = _1] >> ',' >>
	      float_[ref(obj.rot->x) = _1] >> ',' >>
	      float_[ref(obj.rot->y) = _1] >> ',' >>
	      float_[ref(obj.rot->z) = _1] >> ',' >>
	      float_[ref(obj.rot->w) = _1] >> ','
	      //>> double_[ref(lod) = _1] // wtf
            );
            //  End grammar
	
        return r;
    }
    
private:
    typedef bool (*func_t)(node &);
    
public:
    static bool load(std::istream& s, func_t fn)
    {
      std::string buf;
      bool inst = false;
      while(getline(s, buf))
      {
	// !!!: works only with UNIX line ends ( \n )
	if(buf == "inst")
	{
	  inst = true;
	  continue;
	}
	else if(buf == "end")
	{
	  inst = false;
	  continue;
	}
	if(inst)
	{
	  node item;
	  if(parse(buf.begin(), buf.end(), item))
	  {
	    if(!fn(item))
	      return false;
	  }
	}
      }
      return true;
    }
    

};

// RAW objects parser

class raw_obj_parser : public basic_object_parser
{

  // example:
  // 1459,2237.226318,-2280.630859,5.0,0,0,345.726257;
public:
  
    struct node
    {
      int modelid;
      util::point3d pos;
      util::euler rot;
      
      node() : modelid(0),
	  pos(), rot() {}

      object to_object()
      {
		return object(modelid, pos, rot);
      }
    };

    template <typename Iterator>
    static bool parse(Iterator first, Iterator last, node& obj)
    {
	namespace qi = boost::spirit::qi;

        using qi::float_;
        using qi::int_;
        using boost::spirit::ascii::char_;
        using qi::_1;
        using boost::phoenix::ref;
	
        bool r = PARSE_PHRASE

            //  Begin grammar
            (
	      int_[ref(obj.modelid) = _1] >> ',' >>
	      float_[ref(obj.pos.x) = _1] >> ',' >>
	      float_[ref(obj.pos.y) = _1] >> ',' >>
	      float_[ref(obj.pos.z) = _1] >> ',' >>
	      float_[ref(obj.rot->x) = _1] >> ',' >>
	      float_[ref(obj.rot->y) = _1] >> ',' >>
	      float_[ref(obj.rot->z) = _1] >> ';'
	      //double_[ref(lod) = _1]
            );
            //  End grammar

	
        return r;
    }

private:
    typedef bool (*func_t)(node &);
    
public:
    static bool load(std::istream& s, func_t fn)
    {
      std::string buf;
      while(getline(s, buf))
      {
	node item;
	if(parse(buf.begin(), buf.end(), item))
	{
	  if(!fn(item))
	    return false;
	}
      }
      
      return true;
    }

  
};



#undef PARSE_PHRASE
}

#endif
