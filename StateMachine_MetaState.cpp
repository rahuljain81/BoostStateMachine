//https://github.com/CodesBay/State-Machine-Using-Boost-Statechart/tree/master/Chapter-4
#include <iostream>
using namespace std;

#include <boost/statechart/event.hpp>
#include <boost/statechart/state_machine.hpp>
#include <boost/statechart/simple_state.hpp>
#include <boost/statechart/transition.hpp>
#include <boost/statechart/custom_reaction.hpp>

namespace sc = boost::statechart;
namespace mpl = boost::mpl;


/*
 * A functional state machine mainly consists of Meta States. A Meta State is a State with multiple inner state.
 * The State can itself act as a mini state machine.
 * The only difference between a normal state and the meta state is that the normal state takes statemachine as a 2nd template parameter
 * while meta state takes Meta State as 2nd template parameter.
 * Normal State:
 * Meta State:
 * struct firstState : sc::simple_state<firstState, statemachine, firstState_Inner_1>
 * struct firstState_Inner_1 : sc::simple_state<firstState_Inner_1, firstState>
 */


struct firstState; // The Meta State

// Inner States of firstState
struct firstState_Inner_1;
struct firstState_Inner_2;
struct firstState_Inner_3;

// Inner State Movement Events
struct event_Inner1_Inner2 : sc::event<event_Inner1_Inner2> {};
struct event_Inner2_Inner3 : sc::event<event_Inner2_Inner3> {};
struct event_Inner3_Inner1 : sc::event<event_Inner3_Inner1> {};

// Defining the State Machine
struct statemachine : sc::state_machine<statemachine, firstState>{};

// Defining the Meta State
struct firstState : sc::simple_state<firstState, statemachine, firstState_Inner_1> {};

// The 3 Inner States of the Meta State
struct firstState_Inner_1 : sc::simple_state<firstState_Inner_1, firstState> {
	firstState_Inner_1() { cout << "In State => firstState_Inner_1" << endl; }
	typedef sc::transition<event_Inner1_Inner2, firstState_Inner_2> reactions;
};

struct firstState_Inner_2 : sc::simple_state<firstState_Inner_2, firstState> {
	firstState_Inner_2() { cout << "In State => firstState_Inner_2" << endl; }
	typedef sc::transition<event_Inner2_Inner3, firstState_Inner_3> reactions;
};

struct firstState_Inner_3 : sc::simple_state<firstState_Inner_3, firstState> {
	firstState_Inner_3() { cout << "In State => firstState_Inner_3" << endl; }
	typedef sc::transition<event_Inner3_Inner1, firstState_Inner_1> reactions;
};

// The main functiona

int main() {
	statemachine sm;
	sm.initiate();
	sm.process_event(event_Inner1_Inner2());
	sm.process_event(event_Inner2_Inner3());
	sm.process_event(event_Inner3_Inner1());

	return 0;
}
