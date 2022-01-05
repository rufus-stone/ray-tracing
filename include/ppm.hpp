#pragma once

#include <string>
#include <filesystem>

namespace ppm
{

void write_file(std::filesystem::path const &path, char const *data, std::size_t const data_len);

} // namespace ppm
