//https://github.com/CodesBay/State-Machine-Using-Boost-Statechart/tree/master/Chapter-7
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
 * Error Handling
 * To handle situation, where we need to do some cleanup activities, boost::statechart provides some mechanisms.
 * A function with a signature void exit(){...} could be defined for every state.
 * This only thing to remember is that the function gets called ONLY IF state gets terminated because state machine is moved to another state.
 * This function will not get called, if the state is terminated because a state machine itself is terminated.
 * NOTE: The exit() function gets called before destructor, so it's perfectly okay to treat exit() as a class member function
 * and do the thing(s) which is otherwise not recommended in destructors.
 * There is no difference between the behaviour of exit in Inner States.
 * It will be called when the state is transitioned from one state to another state.
 * As with Outer States, the exit() functions shall not be called when the state machine is terminated.
 */

// States
struct firstState;
struct secondState;

// State Events
struct event_MoveToSecond : sc::event<event_MoveToSecond> {};

// State Machines
struct statemachine : sc::state_machine<statemachine, firstState> {
	void exit() { cout << "exit() called in state_machine" << endl; }
};

struct firstState : sc::simple_state<firstState, statemachine>
{
	firstState() { cout << "In State => firstState" << endl; }
	typedef sc::transition<event_MoveToSecond, secondState> reactions;
	void exit() { cout << "exit() called in State => firstState" << endl; }

};
struct secondState : sc::simple_state<secondState, statemachine> {
	secondState() { cout << "In State => secondState" << endl; }
	void exit() { cout << "exit() called in State => secondState" << endl; }
};

// The main
int main() {
	statemachine sm;
	sm.initiate();
	sm.process_event(event_MoveToSecond());
	sm.terminate();
	return 0;
}
