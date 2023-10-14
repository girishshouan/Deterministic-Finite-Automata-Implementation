# Deterministic-Finite-Automata-Implementation
This repo has a simple implementation of a Deterministic Finite Automata. The automata is represented by a DFA class which has the information relating to all the states in form of a vector of pointers of the State class. 
Each state is a pointer of State class, which has all the information related to the state and it's transition function.
The program takes as an input a DFA A together with a word w over the same alphabet, and returns ACCEPT whenever A accepts w, or REJECT otherwise.
