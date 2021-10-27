#pragma once

#include "SearchWeb.h"

using namespace System;

namespace DotNETCppInteropLibrary {

	public ref class InteropSearchResults
	{
	public:
		InteropSearchResults(int score, String^ url)
			: mScore(score),
			  mUrl(url)
		{}

		// copy constructor, which is required to return variable of
		// this class in InteropSearchWeb::Search(String^) call.
		// Notice that CLR type references are specified via '%',
		// while c++ references are done via '&' in managed c++
		// code (which is this interop library.
		InteropSearchResults(const InteropSearchResults% other);

		int mScore;
		String^ mUrl;
	};

	public ref class InteropSearchWeb
	{
	public:
		InteropSearchWeb();
		virtual ~InteropSearchWeb();

		InteropSearchResults Search(String^ keyword);

	private:
		// can only have pointer of native class
		NativeLibrary::SearchWeb* mpSearchWeb;
	};
}
