//https://github.com/CodesBay/State-Machine-Using-Boost-Statechart/tree/master/Chapter-5
#include <iostream>
using namespace std;

#include <boost/statechart/event.hpp>
#include <boost/statechart/state_machine.hpp>
#include <boost/statechart/simple_state.hpp>
#include <boost/statechart/transition.hpp>
#include <boost/statechart/custom_reaction.hpp>

namespace sc = boost::statechart;
namespace mpl = boost::mpl;

//Required
#include <boost/statechart/deferral.hpp>


/*
 * Basically with sc::deferral, the State Machine keeps the NOT HANDLED events in a separate queue.
 * Events in that queue are triggered every time a state is transitioned from the current state to any other state.
 * It will be interesting to note that the sequence of the events is maintained, i.e they will be triggered in sequence
*/

// States
struct firstState;
struct secondState;


// Events
struct event_OutOfBlueEvent : sc::event<event_OutOfBlueEvent> {};
struct event_MoveToSecond : sc::event<event_MoveToSecond> {};

struct statemachine : sc::state_machine<statemachine, firstState>{};

struct firstState : sc::simple_state<firstState, statemachine> {
	firstState() {
		cout << "In State => firstState" << endl;
	}

	typedef mpl::list<
		sc::deferral<event_OutOfBlueEvent>,
		sc::transition<event_MoveToSecond, secondState>
	>reactions;

};

struct secondState : sc::simple_state<secondState, statemachine> {
	secondState() {
		cout << "In State => secondState" << endl;
	}
	typedef sc::custom_reaction<event_OutOfBlueEvent> reactions;

	sc::result react(const event_OutOfBlueEvent & event) {
		cout << "event_OutOfBlueEvent Tiggered in => secondState" << endl;
		return discard_event();
	}
};

int main() {
	statemachine sm;
	sm.initiate();
	// will do nothing
	sm.process_event(event_OutOfBlueEvent());
	// will change state and trigger event_OutOfBlueEvent in second state
	sm.process_event(event_MoveToSecond());
	return 0;
}


