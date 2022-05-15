#pragma once

#include <memory>
#include <stack>

#include "State.h"

namespace Engine
{
	typedef std::unique_ptr<State> StateRef;

	class StateGlowny
	{
	public:
		StateGlowny() {};
		~StateGlowny() {};

		void DodajState(StateRef nowyState, bool czyZamienia = true);
		void UsunState();

		void PrzetworzZmianyState();

		StateRef& AktywnyState();

	private:
		std::stack<StateRef> _states;
		StateRef _nowyState;

		bool _czyUsuwa;
		bool _czyDodaje;
		bool _czyZamienia;
	};
}

//stan Maszyny