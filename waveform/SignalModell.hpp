#ifndef SIGNALMODELL_HPP
#define SIGNALMODELL_HPP

#include <memory>
#include <string>
#include <vector>

namespace waveform
{
    struct Signal {
        explicit
        Signal(std::string name, std::size_t const bit_width) :
            name(std::move(name)), bit_width(bit_width),
            data_bytes(bit_width)
        {
        }

        std::string               name;
        std::size_t               bit_width;
        std::size_t               data_bytes;
        std::vector<std::uint8_t> data;
    };

    struct Module {
        explicit
        Module(std::string name) : name(std::move(name))
        {
        }

        std::string                          name;
        std::size_t                          number_of_signals {};
        std::vector<std::shared_ptr<Signal>> signal_list;
    };
} // namespace waveform

#endif // SIGNALMODELL_HPP
