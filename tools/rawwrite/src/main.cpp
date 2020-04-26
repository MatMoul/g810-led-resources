/*
  This file is part of g810-led.

  g810-led is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, version 3 of the License.

  g810-led is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with g810-led.  If not, see <https://www.gnu.org/licenses/>.
*/

#include <iostream>

#include "classes/Device.h"

bool parseUInt16(std::string val, uint16_t &uint16) {
	if (val.length() == 1) val = "0" + val;
	if (val.length() == 2) val = "0" + val;
	if (val.length() == 3) val = "0" + val;
	if (val.length() != 4) return false;
	uint16 = std::stoul("0x" + val, nullptr, 16);
	return true;
}


int sendRAW(char *arg1, char *arg2, char *arg3) {
	uint16_t vendorID = 0;
	uint16_t productID = 0;
	if (! parseUInt16(arg1, vendorID)) return 1;
	if (! parseUInt16(arg2, productID)) return 1;
	
	std::string line = arg3;
	Device::byte_buffer_t data = {};
	while (line.size() > 1) {
		std::string lpart = line.substr(0, 2);
		line = line.substr(2);
		unsigned char x = std::stoul(lpart, nullptr, 16);
		data.push_back(x);
	}
	
	Device dev;
	if (dev.open(vendorID, productID)) {
		if (dev.sendData(data)) return 0;
	}
	return 1;
}


int main(int argc, char **argv) {
	if (argc < 2) {
		std::cout << "rawwrite" << std::endl;
		std::cout << "--------" << std::endl;
		std::cout << "rawwrite vendorID productID rawdata" << std::endl;
		return 1;
	}
	
	return sendRAW(argv[1], argv[2], argv[3]);
/*
	if (argc < 2) {
		help::usage(argv[0]);
		return 1;
	}
		
	LedKeyboard kbd;
	std::string serial;
	uint16_t vendorID = 0x0;
	uint16_t productID = 0x0;

	int argIndex = 1;
	while (argIndex < argc)
	{
		std::string arg = argv[argIndex];

		// Non-Command arguments
		if (argc > (argIndex + 1) && arg == "-ds") {
			serial = argv[argIndex + 1];
			argIndex += 2;
			continue;
		} else if (argc > (argIndex + 1) && arg == "-dv"){
			if (! utils::parseUInt16(argv[argIndex + 1], vendorID)) return 1;
			argIndex += 2;
			continue;
		} else if (argc > (argIndex + 1) && arg == "-dp"){
			if (! utils::parseUInt16(argv[argIndex + 1], productID)) return 1;
			argIndex += 2;
			continue;
		} else if (argc > (argIndex + 1) && arg == "-tuk"){
			uint8_t kbdProtocol = 0;
			if (! utils::parseUInt8(argv[argIndex + 1], kbdProtocol)) return 1;
			switch(kbdProtocol) {
				case 1:
					kbd.SupportedKeyboards = { { vendorID, productID, (uint16_t)LedKeyboard::KeyboardModel::g810 } };
					break;
				case 2:
					kbd.SupportedKeyboards = { { vendorID, productID, (uint16_t)LedKeyboard::KeyboardModel::g910 } };
					break;
				case 3:
					kbd.SupportedKeyboards = { { vendorID, productID, (uint16_t)LedKeyboard::KeyboardModel::g213 } };
					break;
				default:
					break;
			}
			argIndex += 2;
			continue;
		}
		

		//Commands that do not need to initialize a specific device
		if (arg == "--help" || arg == "-h") {help::usage(argv[0]); return 0;}

		//Initialize the device for use
		if (!kbd.open(vendorID, productID, serial)) {
			std::cout << "Matching or compatible device not found !" << std::endl;
			return 2;
		}
		
		// Command arguments, these will cause parsing to ignore anything beyond the command and its arguments
		return sendRAW(kbd, argv[argIndex + 1]);
	}
*/
	return 0;
}
