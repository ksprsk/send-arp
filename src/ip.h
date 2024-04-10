#pragma once

#include <cstdint>
#include <string>
#include <cstdio>

struct Ip final
{
	static constexpr int SIZE = 4;

	// constructor
	Ip() = default;
	explicit Ip(const uint32_t r) : ip_(r) {}
	explicit Ip(const std::string r);

	// casting operator
	operator uint32_t() const { return this->ip_; } // default
	explicit operator std::string() const;

	// comparison operator
	bool operator==(const Ip &r) const { return this->ip_ == r.ip_; }

	bool isLocalHost() const
	{ // 127.*.*.*
		return (this->ip_ & 0xFF000000) >> 24 == 0x7F;
	}

	bool isBroadcast() const
	{ // 255.255.255.255
		return this->ip_ == 0xFFFFFFFF;
	}

	bool isMulticast() const
	{ // 224.0.0.0 ~ 239.255.255.255
		uint8_t prefix = (this->ip_ & 0xFF000000) >> 24;
		return prefix >= 0xE0 && prefix < 0xF0;
	}

protected:
	uint32_t ip_;
};
