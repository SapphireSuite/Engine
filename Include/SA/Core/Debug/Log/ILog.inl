// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

namespace Sa
{
#if SA_LOGGING

	template <typename StreamT>
	void ILogT<StreamT>::Output(StreamT& _stream) const
	{
		_stream << ToWString() << std::endl;
	}

#endif
}
