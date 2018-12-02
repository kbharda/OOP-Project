#pragma once

// Final Project Milestone 2
//
// Version 1.0
// Date 11/21/2018
// Author Kashyap Bharda (140622176)
// Description THE ERROR MODULE(tracks the error state of client)
//
// Revision History
// -----------------------------------------------------------
// Name               Date                 Reason
/////////////////////////////////////////////////////////////////

#define _CRT_SECURE_NO_WARNINGS

#ifndef AID_ERROR_H
#define AID_ERROR_H

namespace aid {

	class Error {

	private:
		//Private member:
		char* errorMessage;

	public:

		explicit Error(const char* errorMessage = nullptr);

		Error(const Error& em) = delete;

		Error& operator=(const Error& em) = delete;

		virtual ~Error();

		void clear();

		bool isClear() const;

		void message(const char* str);

		const char* message() const;

	};

	//Helper Function
	std::ostream& operator<<(std::ostream& ostr, const Error& err);
}

#endif // ! AID_ERROR_H
