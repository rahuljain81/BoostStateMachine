//https://github.com/CodesBay/State-Machine-Using-Boost-Statechart/tree/master/Chapter-6
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
 * if an event is unhandled in Inner State, it gets automatically propagated to Outer State.
 * Which means all unhandled states can be handled in Outer State.
 * This is good unless we come to a situation where we want only certain events to be propagated to Outer State
 * because we want to do something as part of this event handling in Inner State as well as in_ Outer state.
 * forward_even() _for these situations.
 * forward_event() also provides us the flexibility of choosing, which all events are allowed to be propagate to outer state
 * and which are not
 */

struct firstState;

// Inner States of firstState
struct firstState_Inner_1;

// Inner State Events that will be  forwarded
struct event_First_Inner_1 : sc::event<event_First_Inner_1> {};

// The State Machine
struct statemachine : sc::state_machine<statemachine, firstState> {};

// First State
struct firstState : sc::simple_state<firstState, statemachine, firstState_Inner_1>
{
	firstState() { cout << "In State => firstState" << endl; }

	typedef sc::custom_reaction<event_First_Inner_1> reactions;

	sc::result react(const event_First_Inner_1 & event) {
		cout << "Received Event @ Outer State => firstState" << endl;
		return discard_event();
	}
};

// Inner State
struct firstState_Inner_1 : sc::simple_state<firstState_Inner_1, firstState> {
	firstState_Inner_1() { cout << "In State => firstState_Inner_1" << endl; }
	typedef sc::custom_reaction<event_First_Inner_1> reactions;
	sc::result react(const event_First_Inner_1 & event) {
		cout << "Forwarding Event => event_First_Inner_1 => From firstState_Inner_1" << endl;
		return forward_event();
	}
};

// The Main
int main() {
	statemachine sm;
	sm.initiate();
	// Inner state Events
	sm.process_event(event_First_Inner_1());
	return 0;
}
