#include "pch.hpp"

#include "common/LoggerManager.hpp"
#include "common/Logger.hpp"

#include "common/FileLogger.hpp"

class FileLogger : public Logger
{
public:

	FileLogger()
		: debug_("client/debug.log")
		, info_("client/info.log")
		, warn_("client/warn.log")
		, error_("client/error.log")
		, full_("client/full.log")
	{
		cache_line_.reserve(4 * 1024);
	}

	// NOTE: ignores styles
	// NOTE: ignores type
	virtual void AddLine(Level level, Type type, std::initializer_list<cs::StyledString> line)
	{
		cache_line_.clear();

		{
			char buf[32];
			assert(GetSystemTimeStr(nullptr, 0) <= sizeof(buf));
			size_t time_len = GetSystemTimeStr(buf, sizeof(buf));

			cache_line_.push_back('[');
			cache_line_.insert(cache_line_.end(), buf, buf + time_len);
			cache_line_.push_back(']');
			cache_line_.push_back(' ');
		}

		switch (level)
		{
			case Level::Debug:
				cache_line_.push_back('D');
				break;
			case Level::Info:
				cache_line_.push_back('I');
				break;
			case Level::Warning:
				cache_line_.push_back('W');
				break;
			case Level::Error:
				cache_line_.push_back('E');
				break;
		}

		cache_line_.push_back(' ');

		for (const auto& part : line)
			cache_line_.insert(cache_line_.end(), part.value.begin(), part.value.end());

		cache_line_.push_back('\n');

		switch (level)
		{
			case Level::Debug:   if (min_level_ >= level) debug_.Add(std::string_view(cache_line_.data(), cache_line_.size())); break;
			case Level::Info:    if (min_level_ >= level) info_.Add(std::string_view(cache_line_.data(), cache_line_.size())); break;
			case Level::Warning: if (min_level_ >= level) warn_.Add(std::string_view(cache_line_.data(), cache_line_.size())); break;
			case Level::Error:   if (min_level_ >= level) error_.Add(std::string_view(cache_line_.data(), cache_line_.size())); break;
		}

		full_.Add(std::string_view(cache_line_.data(), cache_line_.size()));
	}

	virtual void Flush() override
	{
		debug_.Flush();
		info_.Flush();
		warn_.Flush();
		error_.Flush();
		full_.Flush();
	}

private:

	Level min_level_ = Logger::Level::Debug;
	std::vector<char> cache_line_;

	common_loggers::FileLogger debug_;
	common_loggers::FileLogger info_;
	common_loggers::FileLogger warn_;
	common_loggers::FileLogger error_;
	common_loggers::FileLogger full_;
};

static RegisterLoggerStatic<FileLogger> registered;
