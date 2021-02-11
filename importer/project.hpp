#ifndef IMPORTER_PROJECT_HPP
#define IMPORTER_PROJECT_HPP

#include <proj_api.h>

class Project {
private:
    projPJ pj_3857, pj_4326;

    Project() {
        if (!(pj_3857 = pj_init_plus("+init=epsg:3857"))) {
            throw std::runtime_error{"can't initialize proj4 with 3857"};
        }
        if (!(pj_4326 = pj_init_plus("+init=epsg:4326"))) {
            throw std::runtime_error{"can't initialize proj4 with 4326"};
        }
    }

    virtual ~Project() {
        pj_free(pj_3857);
        pj_free(pj_4326);
    }

    static Project& instance() {
        static Project the_instance;
        return the_instance;
    }

    bool _toMercator(double *lon, double *lat) {
        double inlon = *lon, inlat = *lat;
        *lon *= DEG_TO_RAD;
        *lat *= DEG_TO_RAD;

        int r = pj_transform(pj_4326, pj_3857, 1, 1, lon, lat, NULL);
        if (r != 0) {
            std::cerr << "error transforming POINT(" << inlon << " " << inlat << ") from 4326 to 3857)" << std::endl;
            *lon = *lat = 0;
            return false;
        }
        return true;
    }

public:
    static bool toMercator(double *lon, double *lat) {
        return Project::instance()._toMercator(lon, lat);
    }
};

#endif // IMPORTER_PROJECT_HPP
