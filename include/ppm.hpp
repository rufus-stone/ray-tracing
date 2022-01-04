#pragma once

#include <string>
#include <filesystem>

namespace ppm
{

auto example() -> std::string;
auto example_two() -> std::string;

void write_file(std::filesystem::path const &path, char const *data, std::size_t const data_len);

} // namespace ppm
