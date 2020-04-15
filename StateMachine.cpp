//https://github.com/CodesBay/State-Machine-Using-Boost-Statechart/tree/master/Chapter-1
#include <iostream>
using namespace std;

#include <boost/statechart/event.hpp>
#include <boost/statechart/state_machine.hpp>
#include <boost/statechart/simple_state.hpp>
#include <boost/statechart/transition.hpp>
#include <boost/statechart/custom_reaction.hpp>

namespace sc = boost::statechart;

struct firstState;
struct statemachine : sc::state_machine<statemachine, firstState>
{
	statemachine() { cout << "Starting => statemachine" << endl; }
};

struct firstState : sc::simple_state<firstState, statemachine>
{
	firstState() { cout << "In State => firstState" << endl; }
};

int main() {
	statemachine sm;
	sm.initiate();
	return 0;
}
