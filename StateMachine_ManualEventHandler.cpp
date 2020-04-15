//https://github.com/CodesBay/State-Machine-Using-Boost-Statechart/tree/master/Chapter-2
#include <iostream>
using namespace std;

#include <boost/statechart/event.hpp>
#include <boost/statechart/state_machine.hpp>
#include <boost/statechart/simple_state.hpp>
#include <boost/statechart/transition.hpp>
#include <boost/statechart/custom_reaction.hpp>

namespace sc = boost::statechart;
namespace mpl = boost::mpl;


struct firstState;
struct secondState;

struct statemachine : sc::state_machine<statemachine, firstState> {};

struct event_MoveToSecondState : sc::event<event_MoveToSecondState> {};

struct firstState : sc::simple_state<firstState, statemachine>
{
	firstState() { cout << "In State => firstState" << endl; }

	typedef sc::custom_reaction<event_MoveToSecondState> reactions;

	// The custom event handler
	sc::result react(const event_MoveToSecondState &event) {
		return transit<secondState>();
	}
};
struct secondState : sc::simple_state<secondState, statemachine>
{
	secondState() { cout << "In State => secondState" << endl; }
};


int main() {
	statemachine sm;
	sm.initiate();
	sm.process_event(event_MoveToSecondState());
	return 0;
}
