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
 * we can transit to another state from inside a Meta State.
 * For example, if we have a state called secondState, outside of meta state firstState,
 * we can transit to secondState from any one of the inner state.
 */


// Outer States
struct firstState;
struct secondState;


// Inner States of firstState
struct firstState_Inner_1;
struct firstState_Inner_2;


// Inner State Events
struct event_Inner_To_Second : sc::event<event_Inner_To_Second> {};

struct statemachine : sc::state_machine<statemachine, firstState>{};

struct firstState : sc::simple_state<firstState, statemachine, firstState_Inner_1> {

};

struct firstState_Inner_1 : sc::simple_state<firstState_Inner_1, firstState> {
	firstState_Inner_1() { cout << "In State => firstState_Inner_1" << endl; }
	typedef sc::transition<event_Inner_To_Second, secondState> reactions;
};

struct firstState_Inner_2 : sc::simple_state<firstState_Inner_2, firstState> {
	firstState_Inner_2() { cout << "In State => firstState_Inner_2" << endl; }
};


struct secondState : sc::simple_state<secondState, statemachine> {
	secondState() { cout << "In State => secondState" << endl; }
};


int main() {
	statemachine sm;
	sm.initiate();
	sm.process_event(event_Inner_To_Second());
	return 0;
}
