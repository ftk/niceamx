#include "samp.h"

//#include "api/cmd.hpp"
//#include "api/streamer.hpp"
//#include "api/playerpool.hpp"
//#include "api/dialogs.hpp"
//#include "api/race.hpp"
//#include "api/counter.hpp"
//#include "api/race_details.hpp"
//#include "api/vote.hpp"
//#include "api/streams.hpp"

//#include <boost/bind.hpp>
#include <iostream>
#include <fstream>

//#include "util/thread.hpp"
#include "util/utils.h"
#include "util/thread.hpp"

/*
void func(int p, bool succ)
{
  std::cout << "h" << std::endl;
  //return true;
}

void f(util::point3d p)
{
  std::cout << p.z << std::endl;
}

void onfinish(int id, int place)
{
  std::cout << id << ' ' << place << std::endl;
}*/

THREAD_FUNC_PREFIX mythread(void * arg)
{
  /*
  api::race_details r;
  std::ifstream str("race.txt");
  r.import_stream(str);
  api::vehicle v(5);
  r.setup_vehicle(v, 1);
  r.setup_vehicle(v, 2);
  r.setup_vehicle(v, 3);
  r.setup_vehicle(v, 4);
  r.setup_vehicle(v, 5);
  r.setup_vehicle(v, 6);
  */
  while(true)
  {
    std::cout << "hoho" << std::endl;
    util::sleep(500);
  }
  THREAD_FUNC_END;
}

//api::vote v;

INIT
{
/*  std::ifstream file("race.txt");
  assert(!!file);
  v.import_stream(file);

  REGISTER_CALLBACK(on_player_spawn, ([&v](int)
  {
    std::string s("");
    //s += int(v.count());
    //api::message<0xffffffff, 0> mesg;
    //v.join(s, '\n');
    //mesg << s << ' ' << v.count() << std::endl;
    
    SHOW_DIALOG(api::dialog_list, ([&v](int id, bool succ, int item)
    {
      v.vote_up(item);
      api::message mesg;
      mesg << v.get_highest() << std::endl;
    }), 0, "vote", v.join('\n'), "ok", "no");
  }));*/

  
  //api::counter x(5, 0, [](api::counter *) { std::cout << "A"; });
  //REGISTER_TIMER(1000, [&x]() {return x.count();} );
  //REGISTER_TIMER(1000, boost::bind<bool>(&api::counter::count, x));
  //REGISTER_TIMER(1000, x);
  //bool (*fptr)() = &(x.count);
  //REGISTER_TIMER(1000, &func);

  util::thread_t thrd;
  util::start_thread(&thrd, &mythread);
  /*
  api::detail::race_loader r;
  std::ifstream racefile("race.txt");
  assert(racefile);
  r.import_stream(racefile);
  api::race def(r);
  def.set_finish_fn(&onfinish);

  def.join(2);
  def.join(1);
  def.start();
  def.proccess_cp(1);
  def.proccess_cp(1);
  def.proccess_cp(1);
  def.proccess_cp(1);
  def.proccess_cp(2);
  def.proccess_cp(2);
  def.proccess_cp(2);
  def.proccess_cp(2);

  std::ofstream racefile2("race2.txt");
  r.export_stream(racefile2);
*/
  //api::detail::delete_checkpoints(r);
  
  //SHOW_DIALOG(api::dialog_msgbox, &func, 10, "aa", "dd", "ok", "no");
  //SHOW_DIALOG(api::dialog_msgbox, &func, 10, "aa", "dd", "ok", "no");
  //SHOW_DIALOG(api::dialog_msgbox, &func, 10, "aa", "dd", "ok", "no");
  /*

  util::strings s = { "1", "2", "3", "5" };
  std::cout << util::convert_from_strings<int, 3>(s) << std::endl;
  
  signals::signal<int> sig;
  signals::signal<util::point3d> sig2;
  
  sig.connect(&func);
  sig2.connect(&f);
    
  
  sig2({1.f, 2.f, 3.f});

*
  REGISTER_TIMER(2000,
		 []() -> bool 
		 {
		   ACTIVEPLAYERBOX->for_each
		   (
		     [](int id)
		     {
		       STREAMER->stream(api::player(id));
		     }
		   );
		   return true;
		 }
  );*/

  
}

