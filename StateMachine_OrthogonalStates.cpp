//https://github.com/CodesBay/State-Machine-Using-Boost-Statechart/tree/master/Chapter-8
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
 * Orthogonal states can be considered as a Meta State which can run multiple parallel internal states,
 * i.e they can run independently of each other. An orthogonal state is useful when when a state want to have multiple inner states.
 * Just like creating multiple event handlers, the construct mpl::list is used to create multiple inner states.
 */

// The main state
struct firstState;

// Forward Declarator : Multiple Inner States
struct firstState_Inner_1;
struct firstState_Inner_2;
struct firstState_Inner_3;

// Creating state machine with firstState
struct statemachine : sc::state_machine<statemachine, firstState> {};

// Making firstState as orthogonal state
struct firstState : sc::simple_state<firstState, statemachine,
	mpl::list<firstState_Inner_1, firstState_Inner_2, firstState_Inner_3 >>
  {};

// Create constructors of firstState inner states
struct firstState_Inner_1 : sc::simple_state<firstState_Inner_1, firstState::orthogonal<0>> {
	firstState_Inner_1() { cout << "In State => firstState_Inner_1" << endl; }
};

struct firstState_Inner_2 : sc::simple_state<firstState_Inner_2, firstState::orthogonal<1>> {
	firstState_Inner_2() { cout << "In State => firstState_Inner_2" << endl; }
};

struct firstState_Inner_3 : sc::simple_state<firstState_Inner_3, firstState::orthogonal<2>> {
	firstState_Inner_3() { cout << "In State => firstState_Inner_3" << endl; }
};

// Run the statemachine to see the output

int main() {
	statemachine sm;
	// This will start with 3 Initial state
	sm.initiate();
	return 0;
}
