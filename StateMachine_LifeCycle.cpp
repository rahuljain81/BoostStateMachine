//https://github.com/CodesBay/State-Machine-Using-Boost-Statechart/tree/master/Chapter-3
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

struct statemachine : sc::state_machine<statemachine, firstState> {
		statemachine () {
			cout << "In statemachine " << endl;
		}
		~statemachine () {
			cout << "Out statemachine " << endl;
		}
	};

struct event_MoveToSecond : sc::event<event_MoveToSecond> {};
struct event_MoveToFirst : sc::event<event_MoveToFirst> {};

struct firstState : sc::simple_state<firstState, statemachine> {
    firstState() {
    	cout<<"In State => firstState => Construction"<<endl; 
    }
    ~firstState() { 
    	cout<<"In State => firstState => Destruction"<<endl; 
    }
    typedef sc::transition<event_MoveToSecond, secondState> reactions;
};

struct secondState : sc::simple_state<secondState, statemachine> {
    secondState() { 
    	cout<<"In State => secondState => Construction"<<endl; 
    }
    ~secondState() { 
    	cout<<"In State => secondState => Destruction"<<endl; 
    }
    typedef sc::transition<event_MoveToFirst, firstState> reactions;
};


//Dynamic memory for the State machine
int main() {
    statemachine * sm = new statemachine();
    sm->initiate();
    sm->process_event(event_MoveToSecond());
    sm->process_event(event_MoveToFirst());
    delete sm;
    return 0;
}
