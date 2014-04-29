#ifndef FACTER_UTIL_FILE_HPP_
#define FACTER_UTIL_FILE_HPP_

#include <string>

namespace facter { namespace util {

    /**
     * Utility type for interacting with files.
     */
    struct file
    {
        /**
         * Reads the entire contents of the given file into a string.
         * @param path The path of the file to read.
         * @return Returns the file contents as a string or empty string if the file cannot be read.
         */
        static std::string read(std::string const& path);

        /**
         * Reads the first line of the given file into a string.
         * @param path The path of the file to read.
         * @return Returns the first line of the file or an empty string if the file cannot be read.
         */
        static std::string read_first_line(std::string const& path);
    };

}}  // namespace facter::util

#endif  // FACTER_UTIL_FILE_HPP_
