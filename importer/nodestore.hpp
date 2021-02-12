/**
 * During the import and update process, nodes are read from the input
 * file. The coordinates from those nodes are stored in-memory for very
 * fast access.
 *
 * There are several implementations of the Nodestore, as during import
 * it's the main memory consumer and during the import the memory
 * consumption is quite high.
 *
 * Therefor Nodestore is an abstract class, with its main methods being
 * pure virtual.
 */

#ifndef IMPORTER_NODESTORE_HPP
#define IMPORTER_NODESTORE_HPP

#include <osmium/osm/types.hpp>

#include <map>
#include <memory>
#include <utility>

/**
 * Abstract baseclass for all nodestores
 */
class Nodestore {
public:
    /**
     * the information stored for each node
     */
    struct Nodeinfo {
        double lat;
        double lon;
        osmium::user_id_type uid;
    };

    /**
     * map representing data stored for one node-version
     */
    using timemap = std::map<time_t, Nodeinfo>;

    /**
     * a pair of a time and a nodeinfo stored in a timemap
     */
    using timepair = std::pair<time_t, Nodeinfo>;

    /**
     * iterator over a timemap
     */
    using timemap_it = timemap::iterator;

    /**
     * constant iterator over a timemap
     */
    using timemap_cit = timemap::const_iterator;

    /**
     * shared ptr to a timemap
     */
    using timemap_ptr = std::shared_ptr<timemap>;

protected:
    /**
     * a Nodeinfo that equals null, returned in case of an error
     */
    const Nodeinfo nullinfo{};

private:
    /**
     * should messages because of store-misses be printed?
     * in a usual import of a softcutted file there are a lot of misses,
     * because the ways may reference nodes that are not part of the
     * extract. Therefore this option may be switched on seperately
     */
    bool m_debug = false;
    bool m_storeerrors = false;

public:

    virtual ~Nodestore() {}

    /**
     * is this nodestore printing debug messages
     */
    bool isPrintingDebugMessages() {
        return m_debug;
    }

    /**
     * should this nodestore print debug messages
     */
    void printDebugMessages(bool shouldPrintDebugMessages) {
        m_debug = shouldPrintDebugMessages;
    }

    /**
     * is this nodestore printing errors originating from store-misses
     */
    bool isPrintingStoreErrors() {
        return m_storeerrors;
    }

    /**
     * should this nodestore be printing errors originating from store-misses?
     */
    void printStoreErrors(bool shouldPrintStoreErrors) {
        m_storeerrors = shouldPrintStoreErrors;
    }

    /**
     * record information about a node
     */
    virtual void record(osmium::object_id_type id, osmium::user_id_type uid, time_t t, double lon, double lat) = 0;

    /**
     * retrieve all information about a node, indexed by time
     */
    virtual timemap_ptr lookup(osmium::object_id_type id, bool &found) = 0;

    /**
     * lookup the version of a node that was valid at time_t t
     *
     * found is set to true if the node was found, and to false otherwise
     * if found != true, the returned value is identical to nullinfo and
     * should not be used.
     */
    virtual Nodeinfo lookup(osmium::object_id_type id, time_t t, bool &found) = 0;
};

#endif // IMPORTER_NODESTORE_HPP
