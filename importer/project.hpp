#ifndef IMPORTER_PROJECT_HPP
#define IMPORTER_PROJECT_HPP

#include <osmium/geom/mercator_projection.hpp>

class Project {
public:
    static bool toMercator(double *lon, double *lat) noexcept {
        if (*lon < -180.0 ||
            *lon > 180.0 ||
            *lat < -osmium::geom::MERCATOR_MAX_LAT ||
            *lat > osmium::geom::MERCATOR_MAX_LAT) {
            return false;
        }

        const osmium::geom::Coordinates c{*lon, *lat};
        const auto projected = osmium::geom::lonlat_to_mercator(c);
        *lon = projected.x;
        *lat = projected.y;

        return true;
    }
};

#endif // IMPORTER_PROJECT_HPP
