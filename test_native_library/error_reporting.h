#pragma once

#include <string>
#include <mutex>

using std::string;

#define MOIRAI_API __declspec(dllexport) // __declspec is a microsoft thing

namespace moirai {
	namespace error_handling {
		class MOIRAI_API error_log
		{
		public:
			typedef void(*exception_callback)(const char * str);
			error_log();
			//typedef void(__stdcall * exception_callback)(const char * str);
			template<typename TException>
			void handle_std_exception(const TException& e);
			void register_exception_callback(const void* callback, bool allow_override = false);
			string get_last_exception_message();
			bool has_callback_registered();
		private:
			std::string last_exception_message;
			exception_callback callback;
			// We will make the error_log within the API single-threaded to prevent concurrent messages
			// R and probably Python would bomb if more than one error is reported concurrently.
			// The mutex cannot be used in the R package itself (too old a G++ in RTools), so we may as well 
			// implement it here where we can use VCPP.
			std::recursive_mutex mutex;

		};

		template<typename TException>
		void error_log::handle_std_exception(const TException& e)
		{
			std::lock_guard<std::recursive_mutex> guard(mutex);
			last_exception_message = string(e.what());
			if (callback != nullptr)
				(*callback)(last_exception_message.c_str());
			else
				throw e;
		}
	}
}