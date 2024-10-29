
#include "error_reporting.h"

using std::string;

namespace moirai {
	namespace error_handling {


		error_log::error_log()
		{
			last_exception_message = string("");
			callback = nullptr;
		}

		string error_log::get_last_exception_message()
		{
			return last_exception_message;
		}

		void error_log::register_exception_callback(const void* callback, bool allow_override)
		{
			if (callback == nullptr)
				this->callback = nullptr;
			else
			{
				if (this->callback != nullptr && !allow_override)
					throw std::logic_error("moirai::error_log already has an error handler set up!");
				else
					this->callback = (error_log::exception_callback) callback;
			}
		}

		bool error_log::has_callback_registered()
		{
			return (this->callback != nullptr);
		}

	}
}
