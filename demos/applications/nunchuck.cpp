// Copyright 2024 Khalil Estell
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <libhal-nunchuck/nunchuck.hpp>
#include <libhal-util/serial.hpp>
#include <libhal-util/steady_clock.hpp>
#include <libhal/i2c.hpp>

#include "../hardware_map.hpp"

void application(hardware_map_t& p_map)
{
  using namespace std::chrono_literals;
  using namespace hal::literals;

  auto& i2c = *p_map.i2c;
  auto& clock = *p_map.clock;
  auto& console = *p_map.console;

  hal::nunchuck::nunchuck nunchuck(i2c);
  hal::print(console, "Demo Application Starting...\n\n");

  while (true) {
    hal::delay(clock, 20ms);

    auto data = nunchuck.read();
    // joystick data
    hal::print<32>(console, "JS-X:%d ", data.joystick_x());
    hal::print<32>(console, "JS-Y:%d ", data.joystick_y());
    // accelerometer data
    hal::print<32>(console, "ACL-X:%li ", data.accelerometer_x());
    hal::print<32>(console, "ACL-Y:%li ", data.accelerometer_y());
    hal::print<32>(console, "ACL-Z:%li ", data.accelerometer_z());
    // button data
    hal::print<32>(console, "Z-BTN:%d ", data.z_button());
    hal::print<32>(console, "C-BTN:%d\n", data.c_button());
  }
}
