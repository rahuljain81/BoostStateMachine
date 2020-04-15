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
struct thirdState;

struct statemachine : sc::state_machine<statemachine, firstState> {};

struct event_MoveToSecondState : sc::event<event_MoveToSecondState> {};
struct event_MoveToThirdState : sc::event<event_MoveToThirdState> {};

struct firstState : sc::simple_state<firstState, statemachine>
{
	firstState() {
		cout << "In State => firstState" << endl;
	}
	typedef mpl::list<
		sc::transition<event_MoveToSecondState, secondState>,
		sc::transition<event_MoveToThirdState, thirdState>
	> reactions;
};
struct secondState : sc::simple_state<secondState, statemachine>
{
	secondState() { cout << "In State => secondState" << endl; }
};
struct thirdState : sc::simple_state<thirdState, statemachine>
{
	thirdState() { cout << "In State => thirdState" << endl; }
};


int main() {
	statemachine sm;
	sm.initiate();
	sm.process_event(event_MoveToThirdState());
	return 0;
}
