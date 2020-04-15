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
 * Life of Deferred Events
 * The deferred events remain the external queue of the state machine till its handled by one of the state event handler
 * or overwritten by new events.
 * That means, if event is popped out of EventQueue for handling in the state and it is not being handled, it will get discarded or lost.
 * To avoid, this, state needs to defer the event again to make it available for next state.
 * At secondState, the event event_OutOfGreenEvent is popped out from the Event Queue,
 * Since there is no handler of this event in secondState and the event is not marked as deferred event, it will be lost.
 * This will be followed by popping off event event_OutOfBlueEvent which will be handled in secondState
 * When we get into this state, the event queue is empty, so it will not execute the event handler for event_OutOfGreenEvent.
 */

struct event_OutOfBlueEvent : sc::event<event_OutOfBlueEvent> {};
struct event_OutOfGreenEvent : sc::event<event_OutOfGreenEvent> {};
struct event_MoveToSecond : sc::event<event_MoveToSecond> {};

struct firstState;
struct secondState;
struct statemachine : sc::state_machine<statemachine, firstState>{};

struct firstState : sc::simple_state<firstState, statemachine> {
	firstState() { cout << "In State => firstState" << endl; }
	typedef mpl::list<
		sc::deferral<event_OutOfBlueEvent>,
		sc::deferral<event_OutOfGreenEvent>,
		sc::transition<event_MoveToSecond, secondState>
	>reactions;

};

struct secondState : sc::simple_state<secondState, statemachine> {
	secondState() { cout << "In State => secondState" << endl; }
	typedef mpl::list<
		sc::custom_reaction<event_OutOfGreenEvent>,
		sc::custom_reaction<event_OutOfBlueEvent>
		> reactions;
	sc::result react(const event_OutOfBlueEvent & event) {
		cout << "event_OutOfBlueEvent Tiggered in => secondState" << endl;
		return discard_event();
	}
	sc::result react(const event_OutOfGreenEvent & event) {
		cout << "event_OutOfGreenEvent Tiggered in => secondState" << endl;
		return discard_event();
	}
};


int main() {
	statemachine sm;
	sm.initiate();
	// will do nothing
	sm.process_event(event_OutOfBlueEvent());
	sm.process_event(event_OutOfGreenEvent());
	// will change state and trigger event_OutOfBlueEvent and event_OutOfGreenEvent in second state
	sm.process_event(event_MoveToSecond());
	return 0;
}

