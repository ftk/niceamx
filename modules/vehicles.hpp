#ifndef VEHICLES_HPP
#define VEHICLES_HPP


#include <vector>
#include <string>
#include "util/singleton.hpp"

#include <boost/noncopyable.hpp>

#include "api/location.hpp"


struct vehicle_color
{
    int col1, col2;
};


class vehicle_model_t
{
public:
    int model_id = -1;
    std::string name;

    std::vector<vehicle_color> colors;

    vehicle_color get_random_color();

};



class vehicle_models : public util::singleton<vehicle_models>
{
    const int modelid_offset = 400;
    std::vector<vehicle_model_t> models;

public:

    const vehicle_model_t& get_model(int modelid) const
    {
        return models.at(modelid - modelid_offset);
    }

    vehicle_model_t& get_model(int modelid)
    {
        return models.at(modelid - modelid_offset);
    }

    void resize(int max_modelid)
    {
        models.resize(max_modelid - modelid_offset);
    }
};

// synced colors
int vehicle_create(int model, util::point3d pos, float angle, int col1 = -1, int col2 = -1, int respawn = 120);

static inline int vehicle_create(int model, api::location loc, int col1 = -1, int col2 = -1, int respawn = 120)
{
    return vehicle_create(model, loc.to_point(), loc.angle, col1, col2, respawn);
}


#endif // VEHICLES_HPP
