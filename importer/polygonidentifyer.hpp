/**
 * In OpenStreetMap a closed way (a way with the same start- and end-node)
 * can be either a polygon or linestring. If it's the one or the other
 * needs to be decided by looking at the tags. This class provides a list
 * of tags that indicate a way looks like a polygon. This decision is only
 * made based on the tags, the geometry of way (is it closed) needs to
 * be checked by the caller separately.
 */

#ifndef IMPORTER_POLYGONIDENTIFYER_HPP
#define IMPORTER_POLYGONIDENTIFYER_HPP

/**
 * list of tags that let a closed way look like a polygon
 */
const char* const polygon_keys[] =
{
    "aeroway",
    "amenity",
    "area",
    "building",
    "harbour",
    "historic",
    "landuse",
    "leisure",
    "man_made",
    "military",
    "natural",
    "power",
    "place",
    "shop",
    "sport",
    "tourism",
    "water",
    "waterway",
    "wetland"
};

/**
 * Checks Tags against a list to decide if they look like the way
 * could potentially be a polygon.
 */
class PolygonIdentifyer {
public:

    /**
     * checks the TagList against a list to decide if they look like the
     * way could potentially be a polygon.
     */
    static bool looksLikePolygon(const osmium::TagList& tags) noexcept {
        for (const auto& tag : tags) {
            for (const char* const key : polygon_keys) {
                if (0 == std::strcmp(key, tag.key())) {
                    return true;
                }
            }
        }

        return false;
    }
};

#endif // IMPORTER_POLYGONIDENTIFYER_HPP
