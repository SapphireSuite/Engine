// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <UTH/Group.hpp>

namespace Sa::UTH
{
//{ Group

	void Group::Update(bool _pred)
	{
		count.Increment(_pred);

		if (!_pred)
			localExit = EXIT_FAILURE;
	}

	void Group::Spread(Group& _parent)
	{
		if (localExit == EXIT_FAILURE)
			_parent.localExit = EXIT_FAILURE;

		_parent.count += count;
	}

//}
}
