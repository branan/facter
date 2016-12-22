#include <internal/facts/aix/disk_resolver.hpp>
#include <internal/util/aix/odm.hpp>
#include <leatherman/logging/logging.hpp>

#include <odmi.h>
#include <sys/cfgodm.h>
#include <sys/ioctl.h>
#include <sys/devinfo.h>

namespace facter { namespace facts { namespace aix {

    disk_resolver::data disk_resolver::collect_data(collection& facts)
    {
        data result;
        vector<string> disk_types;
        auto pd_dv_query = odm_class<PdDv>::open("PdDv").query("class=disk");
        for (auto& pd_dv : pd_dv_query) {
            LOG_DEBUG("got a disk type: {1}", pd_dv.uniquetype);
            disk_types.push_back(pd_dv.uniquetype);
        }

        auto cu_dv = odm_class<CuDv>::open("CuDv");
        for (string& type : disk_types) {
            string query = (boost::format("PdDvLn=%1%") % type).str();
            auto cu_dv_query = cu_dv.query(query);
            for (auto& cu_dv : cu_dv_query) {
                LOG_DEBUG("got a disk: {1}", cu_dv.name);
                disk d;
                d.name = cu_dv.name;
                result.disks.emplace_back(move(d));
            }
        }
        
        return result;
    }
}}}  // namespace facter::facts::aix
