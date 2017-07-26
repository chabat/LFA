#include<stdio.h>
#include<string.h>
#include<utility>
#include<string>
#include<vector>
#include<map>
#include"grammar.h"
#include"determinize.h"
using namespace std;

#define MAX_STATE 1123

typedef pair<string, bool> psb;
typedef vector<psb> vpsb;
typedef vector<string> vs;
typedef vector<int> vi;
typedef vector<vi> vii;
typedef vector<vii> viii;

int main(void) {
  int i;
  int states_cont = 0; //Contador de estados. Diz quantos estados tem.
  int terms_cont = 0; //Contador de terminais.
  int states_qtty = 0;
  int lim = 0;
  vpsb states_name; //vector onde a posição i corresponde ao i-ésimo não-terminal.
  vs terms_name; //vector onde a posição i corresponde ao i-ésimo terminal.
  map<string, int> map_states; //Mapeando os não terminais para um ID.
  map<string, int> map_terms; //Mapeia os terminais para saber se já está no autômato.
  vi transition_cont; //Vector em quantos estados diferentes cada terminal aparece.
  char last_state_generated[MAX_STATE];
  FILE *input_file;
  input_file = fopen("input/input7.txt", "r");
  symbols_mape(input_file, states_cont, states_name, map_states, terms_cont, terms_name, map_terms, states_qtty, transition_cont, lim);
  viii afnd(states_qtty, vii(terms_cont, vi())); //Declarando o AFND
  vi alive (states_qtty, 0);
  create_afnd(input_file, states_cont, states_name, map_states, terms_cont, terms_name, map_terms, afnd, last_state_generated);
  minimize_afnd(states_cont, terms_cont, afnd, alive, transition_cont, states_name, terms_name, map_states, map_terms, lim);
  automaton_determinize(afnd, states_cont, terms_cont, states_name, terms_name, transition_cont, alive, map_states, map_terms, last_state_generated);
  remove_unreachable(states_cont, terms_cont, afnd, alive, states_name, terms_name, map_states, map_terms);
  print_file(states_cont, terms_cont, afnd, states_name, terms_name, transition_cont, alive);
  fclose(input_file);
  return 0;
}

//OBESERVASÕIS <<
//mape_token recebe vpsb &states_name, mas não o usa.
