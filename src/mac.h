#pragma once

#include <cstdint>
#include <string>
#include <algorithm>
#include <sstream>
#include <iomanip>
#include <iostream>

// ----------------------------------------------------------------------------
// Mac
// ----------------------------------------------------------------------------
struct Mac final
{
	static constexpr int SIZE = 6;

	// constructor
	Mac() = default;
	Mac(const Mac &r)
	{
		std::copy(r.mac_, r.mac_ + SIZE, this->mac_);
	}
	Mac(const uint8_t *r)
	{
		std::copy(r, r + SIZE, this->mac_);
	}
	Mac(const std::string &r);

	// assign operator
	Mac &operator=(const Mac &r)
	{
		std::copy(r.mac_, r.mac_ + SIZE, this->mac_);
		return *this;
	}

	// casting operator
	explicit operator uint8_t *() const { return const_cast<uint8_t *>(this->mac_); }
	explicit operator std::string() const;

	// comparison operator
	bool operator==(const Mac &r) const { return std::equal(this->mac_, mac_ + SIZE, r.mac_); }
	bool operator==(const uint8_t *r) const { return std::equal(this->mac_, mac_ + SIZE, r); }
	bool operator!=(const Mac &r) const { return !std::equal(this->mac_, mac_ + SIZE, r.mac_); }

	void clear()
	{
		*this = nullMac();
	}

	bool isNull() const
	{
		return *this == nullMac();
	}

	bool isBroadcast() const
	{ // FF:FF:FF:FF:FF:FF
		return *this == broadcastMac();
	}

	bool isMulticast() const
	{ // 01:00:5E:0*
		return mac_[0] == 0x01 && mac_[1] == 0x00 && mac_[2] == 0x5E && (mac_[3] & 0x80) == 0x00;
	}

	static Mac randomMac();
	static Mac &nullMac();
	static Mac &broadcastMac();

protected:
	uint8_t mac_[SIZE];
};

namespace std
{
	template <>
	struct hash<Mac>
	{
		size_t operator()(const Mac &r) const
		{
			return std::_Hash_impl::hash(&r, Mac::SIZE);
		}
	};
}
