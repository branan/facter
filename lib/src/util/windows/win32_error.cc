#include <facter/util/scoped_resource.hpp>
#include <internal/util/windows/win32_error.hpp>
#include <internal/util/windows/windows.hpp>
#include <boost/format.hpp>
#include <boost/nowide/convert.hpp>

using namespace std;

namespace facter { namespace util { namespace windows {

    string win32_error(DWORD err)
    {
        LPWSTR buffer = nullptr;
        if (FormatMessageW(
            FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_IGNORE_INSERTS,
            nullptr, err, 0, reinterpret_cast<LPWSTR>(&buffer), 0, nullptr) == 0 || !buffer) {
            return (boost::format("unknown error (%1%)") % err).str();
        }

        // boost format could throw, so ensure the buffer is freed.
        scoped_resource<LPWSTR> guard(buffer, [](LPWSTR ptr) { if (ptr) LocalFree(ptr); });
        return (boost::format("%1% (%2%)") % boost::nowide::narrow(buffer) % err).str();
    }

    string win32_error()
    {
        return win32_error(GetLastError());
    }

}}}  // namespace facter::util::windows
