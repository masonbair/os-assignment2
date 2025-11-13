#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

static void usage(const char* prog){
    cerr << "Usage: " << prog << " <input-file>\n";
    cerr << "Input file format:\n";
    cerr << "  n_processes n_resources\n";
    cerr << "  allocation matrix (n_processes lines, each with n_resources ints)\n";
    cerr << "  max allocation matrix (n_processes lines, each with n_resources ints)\n";
    cerr << "  available vector (1 line with n_resources ints)\n";
}

int main(int argc, char* argv[]){
    if(argc < 2){
        usage(argv[0]);
        return 1;
    }

    ifstream fin(argv[1]);
    if(!fin){
        cerr << "Failed to open file: " << argv[1] << '\n';
        return 1;
    }

    int n_processes = 0;
    int n_resources = 0;
    if(!(fin >> n_processes >> n_resources)){
        cerr << "Invalid input: couldn't read n_processes and n_resources\n";
        usage(argv[0]);
        return 1;
    }

    if(n_processes <= 0 || n_resources <= 0){
        cerr << "n_processes and n_resources must be positive integers\n";
        return 1;
    }

    vector<vector<int>> allocation(n_processes, vector<int>(n_resources));
    vector<vector<int>> max_allocation(n_processes, vector<int>(n_resources));
    vector<int> available(n_resources);

    //Reads the allocation matrix
    for(int i = 0; i < n_processes; ++i){
        for(int j = 0; j < n_resources; ++j){
            if(!(fin >> allocation[i][j])){
                cerr << "Invalid input while reading allocation matrix at [" << i << "][" << j << "]\n";
                return 1;
            }
        }
    }

    //Reads the max allocation matrix
    for(int i = 0; i < n_processes; ++i){
        for(int j = 0; j < n_resources; ++j){
            if(!(fin >> max_allocation[i][j])){
                cerr << "Invalid input while reading max allocation matrix at [" << i << "][" << j << "]\n";
                return 1;
            }
        }
    }

    //Reads the available vector
    for(int j = 0; j < n_resources; ++j){
        if(!(fin >> available[j])){
            cerr << "Invalid input while reading available vector at [" << j << "]\n";
            return 1;
        }
    }

    vector<bool> finished_processes(n_processes, false);
    vector<vector<int>> needed_resources(n_processes, vector<int>(n_resources));
    vector<int> correct_processing_order(n_processes);
    int number_of_processes_finished = 0;

    // Build the needed resource matrix
    for(int i = 0; i < n_processes; ++i){
        for(int j = 0; j < n_resources; ++j){
            needed_resources[i][j] = max_allocation[i][j] - allocation[i][j];
        }
    }

    // This simulates if there will be a deadlock or not in the processes
    for(int repeat = 0; repeat < n_processes; ++repeat){
        for(int process = 0; process < n_processes; ++process ){
            if(!finished_processes[process]){
                bool enough_resources = true;
                for(int i = 0; i < n_resources; ++i){
                    if(needed_resources[process][i] > available[i]){
                        enough_resources = false;
                        break;
                    }
                }
                // IF the process has enough resources then we can check it off as completed
                if(enough_resources){
                    // record the process at the current index, then increment the finished count
                    correct_processing_order[number_of_processes_finished] = process;
                    ++number_of_processes_finished;
                    // Loops through the available resources and adds the allocation since a process is finishing
                    for(int available_resource_index = 0; available_resource_index < n_resources; ++available_resource_index){
                        available[available_resource_index] += allocation[process][available_resource_index];
                    }
                    finished_processes[process] = true;
                }
            }
        }
    }

    if(number_of_processes_finished == n_processes){
        cout << "After running the algorithm, a safe sequence is as follows" << endl;
        for(int i = 0; i < n_processes; ++i){
            cout << "P" << correct_processing_order[i];
            if(i + 1 < n_processes) cout << ", ";
        }
        cout << endl;
    } else {
        cout << "These processes will have a deadlock" << endl;
    }

    return 0;
}