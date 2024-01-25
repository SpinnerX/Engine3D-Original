#pragma once

#include <string>

namespace RendererEngine {

	class FileDialogs{
	public:
		// @note filter is to specify when saving files to specific extension types.
		// @param returns string - which is the filepath.
		static std::string openFile(const char* filter);
		static std::string saveFile(const char* filter);
	};

}
