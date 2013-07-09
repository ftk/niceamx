#ifndef GVOTE_HPP
#define GVOTE_HPP

#include <string>
#include <vector>
#include <list>
#include <cstdlib>
#include <stdexcept>

struct vote_option
{
    std::string name;
    std::string cmd;
    int index;
    int voted;

    vote_option() : index(-1) {}
    vote_option(const std::string& name, const std::string cmd) : name(name), cmd(cmd),
        index(-1)
    {}

    const std::string& to_string()
    {
        return name;
    }

    bool execute_command(int pipe, unsigned flags);
};

class vote_container
{
    int max_votes;
public:
    std::vector<vote_option> options;

    vote_container() : max_votes(0) {}

    const vote_option& at(int idx) const
    {
        return options.at(idx);
    }
    vote_option& at(int idx)
    {
        return options.at(idx);
    }

    int add(const vote_option& opt)
    {
        int idx = options.size();
        options.push_back(opt);

        options[idx].index = idx;
        options[idx].voted = 0;
        return idx;
    }

    void vote(int idx)
    {
        at(idx).voted++;
        max_votes = std::max(at(idx).voted, max_votes);
    }
    void reset()
    {
        for(auto& it : options)
        {
            it.voted = 0;
        }
        max_votes = 0;
    }
    void clear()
    {
        options.clear();
        max_votes = 0;
    }



    std::vector<vote_option*> get_top_options()
    {
        std::vector<vote_option*> result;
        for(auto& it : options)
        {
            if(it.voted == max_votes)
                result.push_back(&it);
        }
        return result;

    }

    vote_option& get_top_option()
    {
        auto top = get_top_options();
        if(top.empty())
            throw std::runtime_error("GVote: No top options");
        return *top[rand() % top.size()];
    }

    inline std::string join(char delim = '\n')
    {
        std::string result;
        for(std::size_t i = 0; i < options.size(); i++)
        {
            if(i)
                result += delim;
            result += options[i].to_string();
        }
        return result;
    }

};


extern vote_container * gvotes;

//void show_gvote_dialog(int playerid);

#endif // GVOTE_HPP
