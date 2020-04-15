//https://github.com/CodesBay/State-Machine-Using-Boost-Statechart/tree/master/Chapter-9
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
 * State Machine Contexts
 * the statemachine as well as the state themselves can have the contexts of their own which needs to be accessed during different transitions.
 * Boost::Statechart context allows accessing of statemachine and state contexts from event handlers.
 * The context<>() can't be used inside the constructor / destructors of the state
 */

struct firstState;
struct secondState;

struct statemachine : sc::state_machine<statemachine, firstState> {
	int stateVariable;
	statemachine() : stateVariable(100) {
		cout << "StateMachine State Variable Constructor Value = " << stateVariable << endl;
	}
};


struct event_MoveToSecondState : sc::event<event_MoveToSecondState> {};
struct event_CheckSMVariable : sc::event<event_CheckSMVariable> {};

struct firstState : sc::simple_state<firstState, statemachine> {
	typedef sc::custom_reaction<event_MoveToSecondState> reactions;
	sc::result react(const event_MoveToSecondState & event) {
		context<statemachine>().stateVariable = 200;
		return transit<secondState>();
	}
};
struct secondState : sc::simple_state<secondState, statemachine> {
	typedef sc::custom_reaction<event_CheckSMVariable> reactions;
	sc::result react(const event_CheckSMVariable & event) {
		cout << "Inside event => event_CheckSMVariable | StateMachine State Variable Value = " << context<statemachine>().stateVariable << endl;
		return discard_event();
	}
};

// The Main function

int main() {
	statemachine sm;
	sm.initiate();
	sm.process_event(event_MoveToSecondState());
	sm.process_event(event_CheckSMVariable());
  return 0;
}
