#ifndef IMPORTER_MINORTIMESCALCULATOR_HPP
#define IMPORTER_MINORTIMESCALCULATOR_HPP

#include <osmium/osm/node_ref_list.hpp>

class MinorTimesCalculator {

    const Nodestore* m_nodestore;

public:
    MinorTimesCalculator(const Nodestore* nodestore): m_nodestore(nodestore) {}

    struct MinorTimesInfo {
        time_t t;
        osmium::user_id_type uid;

        MinorTimesInfo(time_t time, osmium::user_id_type user_id) : t(time), uid(user_id) {
        }

        friend bool operator<(const MinorTimesInfo& a, const MinorTimesInfo& b) noexcept {
            return a.t < b.t;
        }

        friend bool operator==(const MinorTimesInfo& a, const MinorTimesInfo& b) noexcept {
            return a.t == b.t;
        }
    };

    std::vector<MinorTimesInfo> *forWay(const osmium::NodeRefList &nodes, time_t from, time_t to = 0) {
        std::vector<MinorTimesInfo> *minor_times = new std::vector<MinorTimesInfo>();

        for (const auto& nr : nodes) {
            bool found = false;
            const auto tmap = m_nodestore->lookup(nr.ref(), found);
            if (!found) {
                continue;
            }

            auto it = tmap->lower_bound(from);
            const auto upper = to == 0 ? tmap->end() : tmap->upper_bound(to);
            for (; it != upper; ++it) {
                /*
                 * lower_bound returns elements *not lower then* from, so it can return times == from
                 * this results in minor with timestamps and information equal to the original way
                 */
                if (it->first == from) {
                    continue;
                }
                minor_times->emplace_back(it->first, it->second.uid);
            }
        }

        std::sort(minor_times->begin(), minor_times->end());
        minor_times->erase(std::unique(minor_times->begin(), minor_times->end()), minor_times->end());

        return minor_times;
    }

};

#endif // IMPORTER_MINORTIMESCALCULATOR_HPP
