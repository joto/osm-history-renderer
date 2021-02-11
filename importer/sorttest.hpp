#ifndef IMPORTER_SORTTEST_HPP
#define IMPORTER_SORTTEST_HPP

class SortTest {
private:
    osmium::item_type last_type = osmium::item_type::undefined;
    osmium::object_id_type last_id = 0;
    osmium::object_version_type last_version = 0;

    const char* typeToText(osmium::item_type type) {
        switch(type) {
            case osmium::item_type::node: return "Node";
            case osmium::item_type::way: return "Way";
            case osmium::item_type::relation: return "Relation";
            case osmium::item_type::area: return "Area";
            default: return "Unknown";
        }

    }

public:
    void test(const osmium::OSMObject* obj) {
        if(
            (last_type > obj->type()) ||
            (last_type == obj->type() && last_id > obj->id()) ||
            (last_type == obj->type() && last_id == obj->id() && last_version > obj->version())
        ) {
            std::cerr
                << "your file is not sorted correctly (by type, id and version):" << std::endl
                << " " << typeToText(last_type) << " " << last_id << "v" << last_version << " comes before"
                << " " << typeToText(obj->type()) << " " << obj->id() << "v" << obj->version() << std::endl << std::endl
                << "The history importer is not able to work with unsorted files." << std::endl
                << "You can use osmosis to sort the file. (see: http://wiki.openstreetmap.org/wiki/Osmosis/Detailed_Usage#--sort_.28--s.29)" << std::endl;

            throw new std::runtime_error("file incorrectly sorted");
        }

        last_type = obj->type();
        last_id = obj->id();
        last_version = obj->version();
    }
};

#endif // IMPORTER_SORTTEST_HPP
