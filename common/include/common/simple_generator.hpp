#pragma once

template <
	typename TResult,
	typename TState,
	typename TAdvance,
	typename TProjStateToResult = decltype([](const TState& state) -> TResult { return state; })>
class simple_generator
{
public:

	constexpr simple_generator(TState&& initial_state, TAdvance&& advance_func)
		: initial_state_{ static_cast<TState&&>(initial_state) }
		, advance_func_{ static_cast<TAdvance&&>(advance_func) }
	{
	}

	constexpr explicit simple_generator(TAdvance&& advance_func)
		: simple_generator(TState{}, static_cast<TAdvance&&>(advance_func))
	{
	}

	struct simple_iterator
	{
		simple_generator* gen;
		TState state;

		constexpr simple_iterator(simple_generator* _gen)
			: gen{ _gen }
		{
			if (gen)
				state = gen->initial_state_;
		}

		constexpr simple_iterator& operator++()
		{
			gen->advance_func_(state, [this]() { gen = nullptr; });
			return *this;
		}

		constexpr bool operator==(const simple_iterator& other) const
		{
			if (gen != other.gen)
				return false;

			if (!gen)
				return true;

			return state == other.state;
		}

		constexpr TResult operator*() const
		{
			return gen->proj_state_to_result_(state);
		}
	};

	constexpr simple_iterator begin() { return simple_iterator(this); }
	constexpr simple_iterator end() { return simple_iterator(nullptr); }

private:

	[[no_unique_address]] TState initial_state_;
	[[no_unique_address]] TAdvance advance_func_;
	[[no_unique_address]] TProjStateToResult proj_state_to_result_;
};

template <typename TResultState, typename TAdvance>
constexpr auto make_simple_generator(TAdvance&& advance_func)
{
	return simple_generator<TResultState, TResultState, TAdvance>(static_cast<TAdvance&&>(advance_func));
}

template <typename TResultState, typename TAdvance>
constexpr auto make_simple_generator(TResultState&& initial_state, TAdvance&& advance_func)
{
	return simple_generator<TResultState, TResultState, TAdvance>(static_cast<TResultState&&>(initial_state), static_cast<TAdvance&&>(advance_func));
}

template <
	typename TResult,
	typename TState,
	typename TProjStateToResult,
	typename TAdvance>
constexpr auto make_simple_generator(TAdvance&& advance_func)
{
	return simple_generator<TResult, TState, TAdvance, TProjStateToResult>(static_cast<TAdvance&&>(advance_func));
}

template <
	typename TResult,
	typename TState,
	typename TProjStateToResult,
	typename TAdvance>
constexpr auto make_simple_generator(TState&& initial_state, TAdvance&& advance_func)
{
	return simple_generator<TResult, TState, TAdvance, TProjStateToResult>(static_cast<TState&&>(initial_state), static_cast<TAdvance&&>(advance_func));
}
