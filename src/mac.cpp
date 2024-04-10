#include "mac.h"

Mac::Mac(const std::string &r)
{
	std::string s;
	// Remove non-hexadecimal characters
	for (char ch : r)
	{
		if ((ch >= '0' && ch <= '9') || (ch >= 'A' && ch <= 'F') || (ch >= 'a' && ch <= 'f'))
		{
			s += ch;
		}
	}

	std::istringstream iss(s);
	int values[SIZE];
	for (int i = 0; i < SIZE; ++i)
	{
		iss >> std::hex >> values[i];
		if (iss.fail())
		{
			std::cerr << "Mac::Mac istringstream failed to convert r=" << r << std::endl;
			return;
		}
		mac_[i] = static_cast<uint8_t>(values[i]);
	}
}

Mac::operator std::string() const
{
	std::ostringstream stream;
	stream << std::uppercase << std::hex << std::setfill('0');
	for (int i = 0; i < SIZE; ++i)
	{
		if (i > 0)
			stream << ":";
		stream << std::setw(2) << static_cast<unsigned>(mac_[i]);
	}
	return stream.str();
}

Mac &Mac::nullMac()
{
	static uint8_t _value[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
	static Mac res(_value);
	return res;
}

Mac &Mac::broadcastMac()
{
	static uint8_t _value[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
	static Mac res(_value);
	return res;
}
