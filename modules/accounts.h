#ifndef ACCOUNTS_H
#define ACCOUNTS_H

#include "config.h"

#include <string>


#include <boost/cstdint.hpp>
#include <cstring>

#include "util/utils.h"


enum
{
    ACCOUNT_VERSION = 1
};

template <unsigned Version>
struct player_account_v
{
    virtual void dont_instantiate() = 0;
};

template<>
struct player_account_v<1>
{
    boost::uint32_t create_time;
    boost::uint32_t last_write_time;
    char password[33];

    // methods

    void set_password(const char * pw)
    {
        strncpy(password, pw, util::arrayof(password));
    }

    static const unsigned Version = 1;
};



//using player_account = player_account_v<ACCOUNT_VERSION>;
typedef player_account_v<ACCOUNT_VERSION> player_account;


bool account_registered(const std::string& name);

void account_create(const std::string& name, player_account& acc);

player_account account_get(const std::string& name);
void account_set(const std::string& name, player_account& acc);

void account_remove(const std::string& name);



#endif // API_GACCOUNTS_H
