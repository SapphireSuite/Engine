// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <iostream>

#include <Core/Debug/ConsoleColor.hpp>

#include <Collections/Debug>

#include <Core/Support/Windows.hpp>

namespace Sa
{
#if SA_LOGGING

	void SetConsoleColor(ConsoleColor _cslColor)
	{
		SetConsoleColor(static_cast<uint8>(_cslColor));
	}

#if SA_WIN

	/// Windows console handle.
	HANDLE cslHandle = GetStdHandle(STD_OUTPUT_HANDLE);

	void SetConsoleColor(uint8 _cslColorMask)
	{
		uint8 attrib = 0u;

		uint8 fg = 0x07 & _cslColorMask; // fg bits only.

		switch (fg)
		{
			case static_cast<uint8>(ConsoleColor::None_FG):
				attrib = 7;
				break;
			case static_cast<uint8>(ConsoleColor::Red_FG):
				attrib = 4;
				break;
			case static_cast<uint8>(ConsoleColor::Green_FG):
				attrib = 2;
				break;
			case static_cast<uint8>(ConsoleColor::Blue_FG):
				attrib = 1;
				break;
			case static_cast<uint8>(ConsoleColor::Cyan_FG):
				attrib = 3;
				break;
			case static_cast<uint8>(ConsoleColor::Magenta_FG):
				attrib = 5;
				break;
			case static_cast<uint8>(ConsoleColor::Yellow_FG):
				attrib = 6;
				break;
			case static_cast<uint8>(ConsoleColor::Black_FG):
				attrib = 0u;
				break;
			default:
				SA_LOG(L"ConsoleColor foreground bit [" << fg << L"] not supported", Warning, Core);
				attrib = 7;
				break;
		}

		if (_cslColorMask & ConsoleColor::Bright_FG) // Bright foreground?
			attrib += 8u;


		uint8 bg = 0x70 & _cslColorMask; // bg bits only.

		switch (bg)
		{
			case static_cast<uint8>(ConsoleColor::None_BG):
				break;
			case static_cast<uint8>(ConsoleColor::Red_BG):
				attrib += 4u << 4u;
				break;
			case static_cast<uint8>(ConsoleColor::Green_BG):
				attrib += 2u << 4u;
				break;
			case static_cast<uint8>(ConsoleColor::Blue_BG):
				attrib += 1u << 4u;
				break;
			case static_cast<uint8>(ConsoleColor::Cyan_BG):
				attrib += 3u << 4u;
				break;
			case static_cast<uint8>(ConsoleColor::Magenta_BG):
				attrib += 5u << 4u;
				break;
			case static_cast<uint8>(ConsoleColor::Yellow_BG):
				attrib += 6u << 4u;
				break;
			case static_cast<uint8>(ConsoleColor::White_BG):
				attrib += 7u << 4u;
				break;
			default:
				SA_LOG(L"ConsoleColor background bit [" << bg << L"] not supported", Warning, Core);
				break;
		}

		if (_cslColorMask & ConsoleColor::Bright_BG) // Bright background?
			attrib += 8u << 4u;


		SetConsoleTextAttribute(cslHandle, attrib);
	}

#else

	void SetConsoleColor(uint8 _cslColorMask)
	{
		std::string attrib = "\033[";
		uint8 fg = 0x07 & _cslColorMask; // fg bits only.

		// Bright? Unix share fg and bg brightness.
		attrib += _cslColorMask & (ConsoleColor::Bright_FG | ConsoleColor::Bright_BG) ? "1;" : "0;";

		switch (fg)
		{
			case static_cast<uint8>(ConsoleColor::None_FG):
				attrib += "0";
				break;
			case static_cast<uint8>(ConsoleColor::Red_FG):
				attrib += "31";
				break;
			case static_cast<uint8>(ConsoleColor::Green_FG):
				attrib += "32";
				break;
			case static_cast<uint8>(ConsoleColor::Blue_FG):
				attrib += "34";
				break;
			case static_cast<uint8>(ConsoleColor::Cyan_FG):
				attrib += "36";
				break;
			case static_cast<uint8>(ConsoleColor::Magenta_FG):
				attrib += "35";
				break;
			case static_cast<uint8>(ConsoleColor::Yellow_FG):
				attrib += "33";
				break;
			case static_cast<uint8>(ConsoleColor::Black_FG):
				attrib += "30";
				break;
			default:
				SA_LOG(L"ConsoleColor foreground bit [" << fg << L"] not supported", Warning, Core);
				break;
		}

		uint8 bg = 0x70 & _cslColorMask; // bg bits only.

		switch (bg)
		{
			case static_cast<uint8>(ConsoleColor::None_BG):
				break;
			case static_cast<uint8>(ConsoleColor::Red_BG):
				attrib += ";41";
				break;
			case static_cast<uint8>(ConsoleColor::Green_BG):
				attrib += ";42";
				break;
			case static_cast<uint8>(ConsoleColor::Blue_BG):
				attrib += ";44";
				break;
			case static_cast<uint8>(ConsoleColor::Cyan_BG):
				attrib += ";46";
				break;
			case static_cast<uint8>(ConsoleColor::Magenta_BG):
				attrib += ";45";
				break;
			case static_cast<uint8>(ConsoleColor::Yellow_BG):
				attrib += ";43";
				break;
			case static_cast<uint8>(ConsoleColor::White_BG):
				attrib += ";47";
				break;
			default:
				SA_LOG(L"ConsoleColor background bit [" << bg << L"] not supported", Warning, Core);
				break;
		}

		attrib += "m";

		std::cout << attrib;
	}

#endif

#endif
}
