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

#include "Device.h"

#include <iostream>
#include <vector>

#include "hidapi/hidapi.h"


using namespace std;


Device::~Device() {
	close();
}

bool Device::isOpen() {
	return m_isOpen;
}

bool Device::open() {
	if (m_isOpen) return true;
	return open(0x0, 0x0);
}

bool Device::open(uint16_t vendorID, uint16_t productID) {
	if (m_isOpen && ! close()) return false;
	m_vendorID = vendorID;
	m_productID = productID;
	
	if (hid_init() < 0) return false;
	
	struct hid_device_info *devs, *dev;
	devs = hid_enumerate(vendorID, productID);
	dev = devs;
	
	if (! dev) {
		hid_exit();
		return false;
	}
	
	m_hidHandle = hid_open(m_vendorID, m_productID, NULL);
	
	if(m_hidHandle == 0) {
		hid_exit();
		return false;
	}
	
	m_isOpen = true;
	return true;
}

bool Device::close() {
	if (! m_isOpen) return true;
	m_isOpen = false;
	
	hid_close(m_hidHandle);
	m_hidHandle = NULL;
	hid_exit();
	return true;
	
	return false;
}

bool Device::sendData(byte_buffer_t &data) {
	if (data.size() > 0) {
		if (! open(m_vendorID, m_productID)) return false;
		if (hid_write(m_hidHandle, const_cast<unsigned char*>(data.data()), data.size()) < 0) {
			std::cout<<"Error: Can not write to hidraw"<<std::endl;
			return false;
		}
		close();
		return true;
	}
	
	return false;
}
