#ifndef API_WEAPONS_HPP
#define API_WEAPONS_HPP

#include <algorithm>

namespace api {



class weapons
{
public:
    enum
    {
        SLOTS = 12
    };
//protected:
    int id[SLOTS];
    int ammo[SLOTS];
public:

    weapons()
    {
        reset();
    }
    weapons(int playerid);

    void setup(int playerid);

    void reset()
    {
        std::fill(id, id + SLOTS, 0);
        std::fill(ammo, ammo + SLOTS, 0);
    }

    static int get_slot(int weaponid);

    void set_weapon(int weaponid, int ammo)
    {
        const int slotid = get_slot(weaponid);
        id[slotid] = weaponid;
        this->ammo[slotid] = ammo;
    }
    void rm_slot(int slotid)
    {
        id[slotid] = ammo[slotid] = 0;
    }

    void rm_weapon(int weaponid)
    {
        rm_slot(get_slot(weaponid));
    }

    static bool rm_player_weapon(int playerid, int slot);

};






} //


#endif // WEAPONS_HPP
