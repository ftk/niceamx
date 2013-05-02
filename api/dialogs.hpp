#ifndef API_DIALOGS_HPP
#define API_DIALOGS_HPP

#include "config.h"
#include "pawn/natives.h"

#include <string>
#include <boost/ptr_container/ptr_list.hpp>
#include <cassert>
#include <functional>

#include <boost/lexical_cast.hpp>

#include "util/singleton.hpp"

namespace api {
//

class basic_dialog
{
public:
  //int playerid;
  unsigned dialogid;
  
protected:
  static void show_impl(int playerid, int dialogid, native::dialog_style style, const std::string& cap, const std::string& text, const std::string& b1, const std::string& b2 = "")
  {
    native::show_player_dialog(playerid, dialogid, style, cap, text, b1, b2);
  }


  basic_dialog() : dialogid(-1) {}
  basic_dialog(unsigned dialogid_) : dialogid(dialogid_) {}
public:

  virtual ~basic_dialog() {}
  
  virtual void invoke(int playerid, bool success, int listitem, const std::string& inputtext) = 0;
};
// -----------
class dialog_msgbox : public basic_dialog
{
private:
  static const native::dialog_style style = native::DIALOG_STYLE_MSGBOX;
  //typedef void (*handler_t)(int, bool);
  typedef std::function<void (int, bool)> handler_t;
public:
  handler_t handler;

public:
  dialog_msgbox() : basic_dialog() {}
  dialog_msgbox(unsigned dialogid_, handler_t handler_, int playerid, const std::string& cap, const std::string& text, const std::string& b1, const std::string& b2 = "") :
    basic_dialog(dialogid_),
    handler(handler_)
  {
    show_impl(playerid, dialogid, style, cap, text, b1, b2);
  }

  void invoke(int playerid, bool success, int/* listitem*/, const std::string& /*inputtext*/)
  {
    assert(handler != NULL);
    return handler(playerid, success);
  }
  
};
// -----------
class dialog_input : public basic_dialog
{
private:
  static const native::dialog_style style = native::DIALOG_STYLE_INPUT;
  //typedef void (*handler_t)(int, bool, const std::string&);
  typedef std::function<void (int, bool, const std::string&)> handler_t;
public:
  handler_t handler;

public:
  dialog_input() : basic_dialog() {}
  dialog_input(unsigned dialogid_, handler_t handler_, int playerid, const std::string& cap, const std::string& text, const std::string& b1, const std::string& b2 = "") :
    basic_dialog(dialogid_),
    handler(handler_)
  {
    show_impl(playerid, dialogid, style, cap, text, b1, b2);
  }

  void invoke(int playerid, bool success, int /*listitem*/, const std::string& inputtext)
  {
    assert(handler != NULL);
    return handler(playerid, success, inputtext);
  }

};
// -----------
class dialog_password : public basic_dialog
{
private:
  static const native::dialog_style style = native::DIALOG_STYLE_PASSWORD;
  //typedef void (*handler_t)(int, bool, const std::string&);
  typedef std::function<void (int, bool, const std::string&)> handler_t;
public:
  handler_t handler;

public:
  dialog_password() : basic_dialog() {}
  dialog_password(unsigned dialogid_, handler_t handler_, int playerid, const std::string& cap, const std::string& text, const std::string& b1, const std::string& b2 = "") :
    basic_dialog(dialogid_),
    handler(handler_)
  {
    show_impl(playerid, dialogid, style, cap, text, b1, b2);
  }

  void invoke(int playerid, bool success, int /*listitem*/, const std::string& inputtext)
  {
    assert(handler != NULL);
    return handler(playerid, success, inputtext);
  }

};
// -----------
class dialog_list : public basic_dialog
{
private:
  static const native::dialog_style style = native::DIALOG_STYLE_LIST;
  //typedef void (*handler_t)(int, bool, int);
  typedef std::function<void (int, bool, int)> handler_t;
public:
  handler_t handler;

public:
  dialog_list() : basic_dialog() {}
  dialog_list(unsigned dialogid_, handler_t handler_, int playerid, const std::string& cap, const std::string& text, const std::string& b1, const std::string& b2 = "") :
    basic_dialog(dialogid_),
    handler(handler_)
  {
    show_impl(playerid, dialogid, style, cap, text, b1, b2);
  }

  void invoke(int playerid, bool success, int listitem, const std::string&/* inputtext*/)
  {
    assert(handler != NULL);
    return handler(playerid, success, listitem);
  }

};

// ------------------------------

class dialogs : public util::singleton<dialogs>
{
  // singleton
private:
  friend class util::singleton<dialogs>;
  dialogs() : dialognext(1) {}

private:
  typedef boost::ptr_list<basic_dialog> dialogids_t;
  dialogids_t dialogids;

  unsigned int dialognext;
  
public:
  bool handle_response(int playerid, unsigned int dialogid, bool success, int listitem, const std::string& inputtext);

  inline unsigned int get_id()
  {
    return(dialognext++);
  }

  inline void new_dialog(basic_dialog * d)
  {
    dialogids.push_back(d);
  }
  
};

// to string
template <typename Iterator, typename T>
inline std::string join(Iterator first, Iterator last, T ch = '\n')
{
    std::string result;
    if(first != last)
    {
        result += boost::lexical_cast<std::string>(*first);
        while(++first != last)
        {
            result += ch;
            result += boost::lexical_cast<std::string>(*first);
        }
    }
    return result;
}
/*
 * Usage:
 * std::list<int> list;
 * auto str = api::join(list.begin(), list.end(), ' '); // "1 2 3"
 */

}

#define DIALOGBOX (api::dialogs::get_instance())

#define MAKE_DIALOG(class,...) new class(DIALOGBOX->get_id(), __VA_ARGS__)
#define SHOW_DIALOG(class,fn,...) DIALOGBOX->new_dialog(MAKE_DIALOG(class, fn, __VA_ARGS__))
// using:
// SHOW_DIALOG(api::dialog_msgbox, &func, playerid, "caption", "message", "ok", "no");

#endif
