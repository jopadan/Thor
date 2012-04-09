/////////////////////////////////////////////////////////////////////////////////
//
// Aurora C++ Library
// Copyright (c) 2012 Jan Haller
// 
// This software is provided 'as-is', without any express or implied
// warranty. In no event will the authors be held liable for any damages
// arising from the use of this software.
// 
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it
// freely, subject to the following restrictions:
// 
// 1. The origin of this software must not be misrepresented; you must not
//    claim that you wrote the original software. If you use this software
//    in a product, an acknowledgment in the product documentation would be
//    appreciated but is not required.
// 
// 2. Altered source versions must be plainly marked as such, and must not be
//    misrepresented as being the original software.
// 
// 3. This notice may not be removed or altered from any source distribution.
//
/////////////////////////////////////////////////////////////////////////////////

/// @file
/// @brief Type aur::SafeBool and corresponding functionality

#ifndef AURORA_SAFEBOOL_HPP
#define AURORA_SAFEBOOL_HPP


namespace aur
{
namespace detail
{

	// Helpers for Safe-Bool idiom (use member-function pointers since they support quite few operators)
	struct SafeBoolHolder
	{
		// Dummy function
		void Function() {}
	};

} // namespace detail

// ---------------------------------------------------------------------------------------------------------------------------


/// @addtogroup Tools
/// @{

/// @brief SafeBool type
/// @hideinitializer
typedef void (detail::SafeBoolHolder::*SafeBool)();
//AURORA_FAKE_DOC(typedef void (detail::SafeBoolHolder::*SafeBool)(), typedef bool SafeBool);

/// @brief SafeBool literal, evaluates to true
/// @hideinitializer
const SafeBool SafeBoolTrue = &detail::SafeBoolHolder::Function;

/// @brief SafeBool literal, evaluates to false
/// @hideinitializer
const SafeBool SafeBoolFalse = nullptr;

/// @brief Conversion function from bool to SafeBool
///
inline SafeBool toSafeBool(bool condition)
{
	return condition ? SafeBoolTrue : SafeBoolFalse;
}

/// @}

} // namespace aur

#endif // AURORA_SAFEBOOL_HPP
