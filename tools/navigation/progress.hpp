#ifndef PROGRESS_HPP
#define PROGRESS_HPP
// fixed version of boost/progress.hpp


#include <boost/timer.hpp>
#include <boost/utility.hpp>  // for noncopyable
//#include <boost/cstdint.hpp>// for uintmax_t
#include <iostream>           // for ostream, cout, etc
#include <string>             // for string

namespace progress {

using namespace boost;
//  progress_timer  ----------------------------------------------------------//

//  A progress_timer behaves like a timer except that the destructor displays
//  an elapsed time message at an appropriate place in an appropriate form.

class progress_timer : public timer, private noncopyable
{
  
 public:
  explicit progress_timer( std::ostream & os = std::cout, unsigned short precise = 2 )
     // os is hint; implementation may ignore, particularly in embedded systems
     : m_os(os), m_prec(precise) {}
  ~progress_timer()
  {
  //  A) Throwing an exception from a destructor is a Bad Thing.
  //  B) The progress_timer destructor does output which may throw.
  //  C) A progress_timer is usually not critical to the application.
  //  Therefore, wrap the I/O in a try block, catch and ignore all exceptions.
    try
    {
      // use istream instead of ios_base to workaround GNU problem (Greg Chicares)
      std::istream::fmtflags old_flags = m_os.setf( std::istream::fixed,
                                                   std::istream::floatfield );
      std::streamsize old_prec = m_os.precision( m_prec );
      m_os << elapsed() << " s\n" // "s" is System International d'Unites std
                        << std::endl;
      m_os.flags( old_flags );
      m_os.precision( old_prec );
    }

    catch (...) {} // eat any exceptions
  } // ~progress_timer

 private:
  std::ostream & m_os;
  unsigned short m_prec;
};


//  progress_display  --------------------------------------------------------//

//  progress_display displays an appropriate indication of 
//  progress at an appropriate place in an appropriate form.

// NOTE: (Jan 12, 2001) Tried to change unsigned long to boost::uintmax_t, but
// found some compilers couldn't handle the required conversion to double.
// Reverted to unsigned long until the compilers catch up. 

class progress_display : private noncopyable
{
 public:
  explicit progress_display( unsigned long expected_count,
                             std::ostream & os = std::cout,
							 char filler = '#',
                             const std::string & s1 = "\n", //leading strings
                             //const std::string & s2 = "",
                             const std::string & s2 = "" )
   // os is hint; implementation may ignore, particularly in embedded systems
   : m_os(os), m_filler(filler), m_s1(s1), m_s3(s2) { restart(expected_count); }

  void           restart( unsigned long expected_count )
  //  Effects: display appropriate scale
  //  Postconditions: count()==0, expected_count()==expected_count
  {
    _count = _next_tic_count = _tic = 0;
    _expected_count = expected_count;

    m_os << m_s1 << "0%   10%  20%  30%  40%  50%  60%  70%  80%  90%  100%\n"
         << std::endl  // endl implies flush, which ensures display
         << m_s3;
    if ( !_expected_count ) _expected_count = 1;  // prevent divide by zero
  } // restart

  unsigned long  operator+=( unsigned long increment )
  //  Effects: Display appropriate progress tic if needed.
  //  Postconditions: count()== original count() + increment
  //  Returns: count().
  {
    if ( (_count += increment) >= _next_tic_count ) { display_tic(); }
    return _count;
  }

  unsigned long  operator++()           { return operator+=( 1 ); }
  unsigned long  operator++(int)         { return operator+=( 1 ); }
  unsigned long  count() const          { return _count; }
  unsigned long  expected_count() const { return _expected_count; }

  private:
  std::ostream &     m_os;  // may not be present in all imps
  const char		 m_filler;
  const std::string  m_s1;  // string is more general, safer than 
//const std::string  m_s2;  //  const char *, and efficiency or size are
  const std::string  m_s3;  //  not issues

  unsigned long _count, _expected_count, _next_tic_count;
  unsigned int  _tic;
  void display_tic()
  {
    // use of floating point ensures that both large and small counts
    // work correctly.  static_cast<>() is also used several places
    // to suppress spurious compiler warnings. 
    unsigned int tics_needed =
      static_cast<unsigned int>(
        (static_cast<double>(_count)/_expected_count)*50.0 );
    do { m_os << m_filler << std::flush; } while ( ++_tic < tics_needed );
    _next_tic_count = 
      static_cast<unsigned long>((_tic/50.0)*_expected_count);
    if ( _count == _expected_count ) {
      if ( _tic < 51 ) m_os << m_filler;
      m_os << std::endl;
      }
  } // display_tic
};

} // namespace progress

#endif  // PROGRESS_HPP
