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

#ifndef DEVICE_CLASS
#define DEVICE_CLASS

#include <chrono>
#include <vector>

#include "hidapi/hidapi.h"


class Device {
	
	
	public:
		
		~Device();
		
		bool isOpen();
		bool open();
		bool open(uint16_t vendorID, uint16_t productID);
		bool close();
		
		typedef std::vector<unsigned char> byte_buffer_t;
		
		bool sendData(byte_buffer_t &data);
		
	private:
		
		bool m_isOpen = false;
		uint16_t m_vendorID = 0;
		uint16_t m_productID = 0;
		hid_device *m_hidHandle;
		
};

#endif
