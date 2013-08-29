#ifndef API_ACCOUNTS_HPP
#define API_ACCOUNTS_HPP


#include "config.h"

#include "util/utils.h"
#include "util/log.h"
#include "util/hash.hpp"

#include <cstdio>
#include <stdexcept>
#include <cassert>
#include <string>
#include <map>
#include <bitset>
#include <ctime>

#include <type_traits>

#include <boost/cstdint.hpp>
#include <boost/noncopyable.hpp>



namespace api {

//

enum
{
    ACCOUNT_CHUNK_SIZE = 2048,
    MAX_ACCOUNTS = 2000
};

using offset_t = boost::uint32_t;

class account_loader : boost::noncopyable
{
private:
    FILE * db = NULL;

public:
    offset_t db_offset = 0;

    bool is_open() const
    {
        return db != NULL;
    }

    void create(const char * filename)
    {
        close();

        FILE * newdb = fopen(filename, "wb"); // write zeroes

        if(!newdb)
            throw std::runtime_error(std::string("cannot create file ") + filename);

        char t = 0;
        for(offset_t i = 0; i < ACCOUNT_CHUNK_SIZE * MAX_ACCOUNTS; i += sizeof(char))
            fwrite(&t,sizeof(char),1,newdb);

        fclose(newdb);
    }

    void close()
    {
        if(db)
            fclose(db);
        db = NULL;
    }

    void open(const char * filename)
    {
        close();
        db = fopen(filename, "rb+");
        if(!db)
        {
            util::log_msg("api/accounts/db", "cant open %s, creating...", filename);
            create(filename);
            db = fopen(filename, "rb+");
        }
        //else
        //	fclose(db);

        assert(db);
    }

	template <typename Account>
    Account load(unsigned chunk)
    {
        /* structure of chunk (name, type, size)
         * account  Account      sizeof(Account)
         * zeroes   void         (ACCOUNT_CHUNK_SIZE-sizeof(Account))
         */
        static_assert(std::is_pod<Account>::value, "Account should be POD");
        static_assert(sizeof(Account) <= ACCOUNT_CHUNK_SIZE, "Account size is too big");
        
        if(!is_open())
            throw std::logic_error("account_loader: db is not opened");

        fseek(db, db_offset + chunk * ACCOUNT_CHUNK_SIZE, SEEK_SET);

        return util::fread<Account>(db);
    }
    
	template <typename Account>
    void save(const Account& acc, unsigned chunk)
    {
        static_assert(std::is_pod<Account>::value, "Account should be POD");
        static_assert(sizeof(Account) <= ACCOUNT_CHUNK_SIZE, "Account size is too big");
        
        if(!is_open())
            throw std::logic_error("account_loader: db is not opened");
        fseek(db, db_offset + chunk * ACCOUNT_CHUNK_SIZE, SEEK_SET);
        util::fwrite(db, acc);
        return;
    }

    ~account_loader()
    {
        close();
    }

};



template <class Account>
class accounts_manager
{

private:
    account_loader loader;
    std::string header_path;
    std::string db_path;

    std::map<util::hash_t, offset_t> header;
    
    bool is_opened = false;

private:

    /* structure of header
     * version(2)
     * count(4)
     * { hash(8)
     *   offset(4) }(count * 12)
     */
    void load_header()
    {
        header.clear();
        FILE * hdr = fopen(header_path.c_str(), "rb");

        if(!hdr)
        {
            //throw std::runtime_error("cant read file " + header_path);
            util::log_msg("api/accounts/header", "cant open %s, creating..",
                          header_path.c_str());
            save_header();
            return load_header();
        }

        auto version = util::fread<boost::uint16_t>(hdr);


        if(version != Account::Version)
        {
            util::log_msg("api/accounts/header", "required upgrade to new version %u -> %u",
                          version, Account::Version);
        }


        auto size = util::fread<boost::uint32_t>(hdr);
        for(unsigned i = 0; i < size; i++)
        {
            if(feof(hdr))
                break;
            auto hash = util::fread<util::hash_t>(hdr);
            auto offset = util::fread<offset_t>(hdr);
            header[hash] = offset;
        }

        fclose(hdr);



        if(version != Account::Version)
        {
            upgrade_version(version);
        }

        util::log_debug("api/accounts/header", "loaded %u accounts", size);

    }
    void save_header() const
    {
        FILE * hdr = fopen(header_path.c_str(), "wb");

        if(!hdr)
            throw std::runtime_error("cant write to file " + header_path);

        util::fwrite(hdr, static_cast<boost::uint16_t>(Account::Version));

        util::fwrite(hdr, static_cast<boost::uint32_t>(header.size()));
        for(const auto& pair : header)
        {
            if(feof(hdr))
                break;
            util::fwrite(hdr, pair.first);
            util::fwrite(hdr, pair.second);
        }

        fclose(hdr);
    }

    void cleanup(unsigned free_slots) // remove the oldest n entries
    {
        std::map<boost::uint32_t, util::hash_t> date_asc; // sorted by date
        for(const auto& pair : header)
        {
            auto acc = loader.load<Account>(pair.second);
            date_asc[acc.last_write_time] = pair.first;
        }
        for(const auto& pair : date_asc) // remove the oldest
        {
            if(!free_slots--)
                break;
            header.erase(pair.second);
        }
    }

    void upgrade_version(unsigned version)
    {
        // edit
        if(version != Account::Version)
        {
            throw std::runtime_error("accounts header: wrong version!");
        }
    }

public:
    Account get(util::hash_t hash)
    {
        return loader.load<Account>(header.at(hash));
    }
    Account get(const std::string& name)
    {
        return get(util::hash_rt(name.c_str()));
    }
    
    void set(util::hash_t hash, Account& acc)
    {
        acc.last_write_time = ::time(NULL);
        loader.save(acc, header.at(hash));
    }
    
    void set(const std::string& name, Account& acc)
    {
        set(util::hash_rt(name.c_str()), acc);
    }


    void create(const std::string& name, Account& acc)
    {
        if(header.size() == MAX_ACCOUNTS)
        {
            const unsigned to_clean = MAX_ACCOUNTS / 4; // clean 25%
            cleanup(to_clean);
        }
        auto hash = util::hash_rt(name.c_str());
        if(header.count(hash))
        {
            util::log_msg("api/accounts/header", "dublicate entry %s", name.c_str());
            loader.save(acc, header[hash]);
            return;
        }

        offset_t offset = lower_bound();
        header[hash] = offset;

        acc.create_time = acc.last_write_time = ::time(NULL);

        loader.save(acc, offset);
    }

    void remove(util::hash_t hash)
    {
        auto it = header.find(hash);
        if(it != header.end())
        {
            //
            header.erase(it);
        }
    }

    int count(const std::string& name) const
    {
        return header.count(util::hash_rt(name.c_str()));
    }

private:

    offset_t lower_bound()
    {
        assert(header.size() < MAX_ACCOUNTS);
        std::bitset<MAX_ACCOUNTS> bs;
        for(const auto& pair : header)
        {
            bs.set(pair.second);
        }
        for(offset_t i = 0; i < MAX_ACCOUNTS; i++)
        {
            if(!bs[i])
                return i;
        }
        // never reachs
        return(-1);
    }

public:
    // ctor
    accounts_manager() = default;
    
    accounts_manager(std::string header_path, std::string db_path) :
        header_path(std::move(header_path)), db_path(std::move(db_path))
    {
    	if(!header_path.empty() && !db_path.empty())
    	{
	        load_header();
	        loader.open(db_path.c_str());
	        is_opened = true;
	    }
    }

    // dtor
    ~accounts_manager()
    {
    	if(is_opened)
    	{
	        save_header();
	        loader.close();
	    }
    }

    void reopen(std::string header_path_, std::string db_path_)
    {
    	if(is_opened)
    	{
	        save_header();
	        loader.close();
	    }
        this->header_path = std::move(header_path_);
        this->db_path = std::move(db_path_);
        load_header();
        loader.open(db_path.c_str());
        is_opened = true;
    }

    void flush()
    {
        if(is_opened)
        {
            save_header();
            loader.close();
            loader.open(db_path.c_str());
        }
    }

};


} // api

#endif // ACCOUNTS_HPP
