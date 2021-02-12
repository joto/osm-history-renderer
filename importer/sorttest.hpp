#ifndef IMPORTER_SORTTEST_HPP
#define IMPORTER_SORTTEST_HPP

#include <osmium/osm/item_type.hpp>
#include <osmium/osm/types.hpp>

#include <iostream>
#include <stdexcept>

class SortTest {
    osmium::item_type last_type = osmium::item_type::undefined;
    osmium::object_id_type last_id = 0;
    osmium::object_version_type last_version = 0;

public:
    void test(const osmium::OSMObject& obj) {
        if ((last_type > obj.type()) ||
            (last_type == obj.type() && last_id > obj.id()) ||
            (last_type == obj.type() && last_id == obj.id() && last_version > obj.version())) {
            std::cerr
                << "your file is not sorted correctly (by type, id and version):\n"
                << " " << osmium::item_type_to_name(last_type) << " " << last_id << "v" << last_version << " comes before"
                << " " << osmium::item_type_to_name(obj.type()) << " " << obj.id() << "v" << obj.version()
                << "\n\nThe history importer is not able to work with unsorted files.\n";

            throw new std::runtime_error{"file incorrectly sorted"};
        }

        last_type = obj.type();
        last_id = obj.id();
        last_version = obj.version();
    }
};

#endif // IMPORTER_SORTTEST_HPP
