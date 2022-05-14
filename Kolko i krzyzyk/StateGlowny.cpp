#include "StateGlowny.h"

namespace Engine
{
	void StateGlowny::DodajState(StateRef nowyState, bool czyZamienia)
	{
		this->_czyDodaje = true;
		this->_czyZamienia = czyZamienia;

		this->_nowyState = std::move(nowyState);
	}

	void StateGlowny::UsunState()
	{
		this->_czyUsuwa = true;
	}

	void StateGlowny::PrzetworzZmianyState()
	{
		if (this->_czyUsuwa && !this->_states.empty())
		{
			this->_states.pop();

			if (!this->_states.empty())
			{
				this->_states.top()->Resume();
			}

			this->_czyUsuwa = false;
		}

		if (this->_czyDodaje)
		{
			if (!this->_states.empty())
			{
				if (this->_czyZamienia)
				{
					this->_states.pop( );
				}
				else
				{
					this->_states.top()->Pause();
				}
			}

			this->_states.push( std::move( this->_nowyState));
			this->_states.top()->Init();
			this->_czyDodaje = false;
		}
	}

	StateRef& StateGlowny::AktywnyState()
	{
		return this->_states.top();
	}
}