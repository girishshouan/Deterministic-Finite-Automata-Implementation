#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>


class state{
public:
  std::string name;
  bool isStarting = false;
  bool isAccepting = false;
  std::vector<char> validInputs;
  std::unordered_map<char, std::string> transitionFunction;

  state(std::string _name, bool _isStarting, bool _isAccepting, std::unordered_map<char, std::string> _transitionFunction){
    this->name = _name;
    this->isStarting = _isStarting;
    this->isAccepting = _isAccepting;
    transitionFunction = _transitionFunction;
    for(auto &_pair : _transitionFunction){
      validInputs.push_back(_pair.first);
    }
  }

  void print(){
    std::cout<<"Name:  "<<this->name<<"\n";
    std::cout<<"isStarting:  "<<this->isStarting<<"\n";
    std::cout<<"isAccepting:  "<<this->isAccepting<<"\n";
    std::cout<<"Printing Valid inputs for this state.\n";
    for(auto &input : this->validInputs){
        std::cout<<input<<"\t";
        std::cout<<"\n";
    }
    std::cout<<"Transition Function:\n";
    for(auto& _pair : transitionFunction){
      std::cout<<_pair.first<<"-->"<<_pair.second<<"\n";
    }
  }
};




class DFA{
  public:
    std::vector<state*> states;
    state* startingState;
    state* currentState;
    DFA(std::vector<state*> _states){
      this->states = _states;
      for(state* st : states){
        if(st->isStarting == true){
            this->startingState = st;
            break;
        }
      }
    }

    void printDFA(){
        std::cout<<"The starting state is:  "<<startingState->name<<"\n";
        std::cout<<"Printing states.\n";
        for(state* st: this->states){
            st->print();
            std::cout<<"\n";
        }
    }

    void check(std::string word){
        this->currentState = this->startingState;
        for(int i=0; i<word.size(); i++){
            
            if(std::find(currentState->validInputs.begin(), currentState->validInputs.end(), word[i]) != currentState->validInputs.end()){
                //Input is valid.
                std::string nextStateName = currentState->transitionFunction[word[i]];
                for(state *st : this->states){
                    if(st->name == nextStateName){
                        currentState = st;
                    }
                }
            }
            else{
                std::cout<<"The word "<<word<<" is not acceptable - Not in Alphabet.\n";
                return;
            }

        }

        if(currentState->isAccepting){
            std::cout<<"The word "<<word<<" has been accepted by the DFA.\n";
        }
        else{
            std::cout<<"The word "<<word<<" has been rejected by the DFA.\n";
        }
    }

};



int main() {
    std::unordered_map<char, std::string> transitionMap;
    transitionMap['a'] = "q1";
    transitionMap['b'] = "q2";
    state *q1 = new state("q1", true, true, transitionMap);
    //q1->print();
    transitionMap.clear();
    transitionMap['a'] = "q3";
    transitionMap['b'] = "q2";
    state *q2 = new state("q2", false, true, transitionMap);
    //q2->print();
    transitionMap.clear();
    transitionMap['a'] = "q3";
    transitionMap['b'] = "q3";
    state *q3 = new state("q3", false, false, transitionMap);
    //q3->print();
    
    std::vector<state*> states;
    states.push_back(q1);states.push_back(q2);states.push_back(q3);
    DFA *test = new DFA(states);
    test->printDFA();
    test->check("ab");
    test->check("aaaaaaaaaaaaaaaaaabbbbbb");
    test->check("abbbbbbbbbbbbbbbbbbbbbbbbbbb");
    test->check("aaaba");
    test->check("abv");

}