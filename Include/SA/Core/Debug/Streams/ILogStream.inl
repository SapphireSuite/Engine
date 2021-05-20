// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

namespace Sa
{
#if SA_LOGGING

	template <typename StreamT, typename LogT>
	ILogStream& ILogStreamT<StreamT, LogT>::Output(const ILog& _log)
	{
		const LogT* logT = dynamic_cast<const LogT*>(&_log);

		if (logT)
			logT->Output(dynamic_cast<StreamT&>(*this));

		return *this;
	}

#endif
}
