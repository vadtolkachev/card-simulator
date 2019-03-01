#pragma once

#include <string>
#include <memory>

class IKCImage
{
public:
	typedef std::shared_ptr<IKCImage> Shared;

	virtual ~IKCImage() {};
	static Shared imageFromFile(const std::string& path);
	static Shared imageFromBuffer(const std::string& buffer);
	static Shared imageWithName(const std::string& resourceName);
	virtual bool saveToFile(const std::string& path) = 0;
	virtual bool saveToBuffer(std::string& buffer, float outputWidth, float outputHeight) = 0;
	virtual float width() = 0;
	virtual float height() = 0;
};