// #include <bits/stdc++.h>
// #include "graph.h"
// #include <array>
#include "netlist2graph.h"

using namespace std;

tuple<int, vector<string>> split_ports(string str)
{
    vector<string> ports;

    int cnt = 0;

    string port;
    int num_of_bits;
    stringstream ss(str);
    while (ss >> port)
    {
        // get num_of_bits
        if (cnt == 1)
        {
            string tmp;
            for (auto c : port)
            {
                if (c == ':')
                    break;
                if (c >= '0' && c <= '9')
                    tmp += c;
            }
            num_of_bits = stoi(tmp) + 1;
        }
        // get ports
        if (cnt >= 2)
        {
            string port_ = port.substr(0, min(port.find(','), port.find(';')));
            ports.push_back(port_);
        }

        cnt++;
    }

    return make_tuple(num_of_bits, ports);
}

tuple<map<string, Gate *>, map<string, Gate *>, int> read_file(string file, string *module_name, map<string, int> *module_inputs, map<string, int> *module_outputs)
{
    string str;
    ifstream ifs(file, ifstream::in);

    // initial settings
    string std_library[] = {"and", "or", "nand", "nor", "not", "buf", "xor", "xnor"};
    vector<pair<string, Gate *>> output_map; // wire name, gate that produces the output
    vector<tuple<string, Gate *, int>> input_map;  // wire name, gate that accepts the input, input index

    int gate_number = 0;

    while (getline(ifs, str))
    {
        stringstream ss(str);
        while (ss.good())
        {
            string element;
            getline(ss, element, ' ');
            // finding module name
            if (element == "module")
            {
                *module_name = str;
            }
            // ========== finding inputs ==============
            else if (element == "input")
            {
                string high_bit;
                int port_start_id;
                if (str.find('[') != string::npos)
                {
                    high_bit = str.substr(str.find('[') + 1, str.find(':') - str.find('[') - 1);
                    port_start_id = str.find(']') + 1;
                }
                else
                {
                    high_bit = "0";
                    port_start_id = str.find("input") + 5;
                }
                int input_bits = stoi(high_bit) + 1;
                string ports_string = str.substr(port_start_id, string::npos);
                stringstream ss2(ports_string);
                string port;
                while (ss2.good())
                {
                    getline(ss2, port, ',');
                    port.erase(remove(port.begin(), port.end(), ' '), port.end());
                    port.erase(remove(port.begin(), port.end(), ';'), port.end());
                    (*module_inputs)[port] = input_bits;
                }
            }
            // ========== finding outputs ==============
            else if (element == "output")
            {
                string high_bit;
                int port_start_id;
                if (str.find('[') != string::npos)
                {
                    high_bit = str.substr(str.find('[') + 1, str.find(':') - str.find('[') - 1);
                    port_start_id = str.find(']') + 1;
                }
                else
                {
                    high_bit = "0";
                    port_start_id = str.find("output") + 6;
                }
                int output_bits = stoi(high_bit) + 1;
                string ports_string = str.substr(port_start_id, string::npos);
                stringstream ss2(ports_string);
                string port;
                while (ss2.good())
                {
                    getline(ss2, port, ',');
                    port.erase(remove(port.begin(), port.end(), ' '), port.end());
                    port.erase(remove(port.begin(), port.end(), ';'), port.end());
                    (*module_outputs)[port] = output_bits;
                }
            }
            // =========== finding gates ==============
            // find gate
            if (find(begin(std_library), end(std_library), element) != end(std_library))
            {
                string gate_name = element;
                string gate_ports_str = str.substr(str.find('(') + 1, str.find(')') - str.find('(') - 1);
                vector<string> gate_ports;
                string port;
                stringstream ss3(gate_ports_str);
                while (ss3.good())
                {
                    getline(ss3, port, ',');
                    port.erase(remove(port.begin(), port.end(), ' '), port.end());
                    gate_ports.push_back(port);
                }
                Gate *newGate = new Gate(gate_name);
                newGate->no = gate_number;
                gate_number ++;
                // output_map[gate_ports[0]] = newGate;
                output_map.push_back(make_pair(gate_ports[0], newGate));
                for (int i = 1; i < gate_ports.size(); i++)
                {
                    // input_map[gate_ports[i]] = newGate;
                    input_map.push_back(make_tuple(gate_ports[i], newGate, i-1));
                }
            }
        }
    }
    ifs.close();

    map<string, Gate *> primary_inputs;
    map<string, Gate *> primary_outputs;
    // ======== initialize primary inputs and outputs ==========
    // inputs
    for (auto inp : (*module_inputs))
    {
        int inp_bits = inp.second;
        if (inp_bits == 1){
            string tmp = inp.first;
            Gate* newGate = new Gate;
            newGate->gate_name = tmp;
            primary_inputs[tmp] = newGate;
        }
        else{
            for (int i = 0; i < inp_bits; i++){
                string tmp = inp.first + "[" + to_string(i) + "]";
                Gate* newGate = new Gate;
                newGate->gate_name = tmp;
                primary_inputs[tmp] = newGate;
            }
        }
    }
    // deal with constant 1'b0, 1'b1
    Gate* const_0_gate = new Gate("1'b0");
    const_0_gate->value = 0;
    Gate* const_1_gate = new Gate("1'b1");
    const_1_gate->value = 1;
    primary_inputs["1'b0"] = const_0_gate;
    primary_inputs["1'b1"] = const_1_gate;

    // outputs
    for (auto outp : (*module_outputs))
    {
        int outp_bits = outp.second;
        // cout << outp.first << endl;
        if (outp_bits == 1){
            string tmp = outp.first;
            Gate* newGate = new Gate;
            newGate->gate_name = tmp;
            primary_outputs[tmp] = newGate;
        }
        else{
            for (int i = 0; i < outp_bits; i++){
                string tmp = outp.first + "[" + to_string(i) + "]";
                Gate* newGate = new Gate;
                newGate->gate_name = tmp;
                primary_outputs[tmp] = newGate;
            }
        }
    }

    // === connect the gates =====
    // connect input map
    for (auto wire_map : input_map)
    {
        string wire_name = get<0>(wire_map);
        Gate *arrived_gate = get<1>(wire_map);
        int input_id = get<2>(wire_map);

        // find in output map
        auto tmp = find_if(output_map.begin(), output_map.end(), [&wire_name](auto x) { return x.first == wire_name; });
        if (tmp != output_map.end())
        {
            Gate *departed_gate = tmp->second;
            arrived_gate->inputs.push_back(make_tuple(departed_gate, 0));
            // vector<tuple<Gate*, int>> output_connects {make_tuple(arrived_gate, 0)};
            // departed_gate->outputs.push_back(output_connects);
            if (departed_gate->num_of_outputs() == 0) 
            {
                vector<tuple<Gate*, int>> output_connects {make_tuple(arrived_gate, input_id)};
                departed_gate->outputs.push_back(output_connects);
            }
            else
            {
                departed_gate->outputs[0].push_back(make_tuple(arrived_gate, input_id));
            }
        }
        else
        { // find in primary inputs
            auto tmp2 = primary_inputs.find(wire_name);
            if (tmp2 != primary_inputs.end())
            {
                Gate *departed_gate = tmp2->second;
                arrived_gate->inputs.push_back(make_tuple(departed_gate, 0));
                if (departed_gate->num_of_outputs() == 0) 
                {
                    vector<tuple<Gate*, int>> output_connects {make_tuple(arrived_gate, input_id)};
                    departed_gate->outputs.push_back(output_connects);
                }
                else
                {
                    departed_gate->outputs[0].push_back(make_tuple(arrived_gate, input_id));
                }
                
            }
            else {
                cout << "Something Went Wrong: no " <<  wire_name << " found" << endl;
            }
        }
    }
    // connect primary outputs
    for (auto wire_map : primary_outputs)
    {
        string wire_name = wire_map.first;
        Gate *arrived_gate = wire_map.second;
        // find in output map
        auto tmp = find_if(output_map.begin(), output_map.end(), [&wire_name](auto x) { return x.first == wire_name; });
        if (tmp != output_map.end())
        {
            Gate *departed_gate = tmp->second;
            arrived_gate->inputs.push_back(make_tuple(departed_gate, 0));
            // vector<tuple<Gate*, int>> output_connects {make_tuple(arrived_gate, 0)};
            // departed_gate->outputs.push_back(output_connects);
            if (departed_gate->num_of_outputs() == 0) 
            {
                vector<tuple<Gate*, int>> output_connects {make_tuple(arrived_gate, 0)};
                departed_gate->outputs.push_back(output_connects);
            }
            else
            {
                departed_gate->outputs[0].push_back(make_tuple(arrived_gate, 0));
            }
        }
        else
        { // find in primary inputs
            auto tmp2 = primary_inputs.find(wire_name);
            if (tmp2 != primary_inputs.end())
            {
                Gate *departed_gate = tmp2->second;
                arrived_gate->inputs.push_back(make_tuple(departed_gate, 0));
                // vector<tuple<Gate*, int>> output_connects {make_tuple(arrived_gate, 0)};
                // departed_gate->outputs.push_back(output_connects);
                if (departed_gate->num_of_outputs() == 0) 
                {
                    vector<tuple<Gate*, int>> output_connects {make_tuple(arrived_gate, 0)};
                    departed_gate->outputs.push_back(output_connects);
                }
                else
                {
                    departed_gate->outputs[0].push_back(make_tuple(arrived_gate, 0));
                }
            }
            else {
                cout << "Something Went Wrong: no " <<  wire_name << " found" << endl;
            }
        }
    }
    return make_tuple(primary_inputs, primary_outputs, gate_number);
}

// int main()
// {
//     // Gate *root = new Gate("dao");
//     // cout << root->num_of_inputs();

//     // ======== input ========================
//     string file_path = "full_adder.v";
//     // ======== basic netlist info ===========
//     string module_name;
//     map<string, int> module_inputs;
//     map<string, int> module_outputs;

//     map<string, Gate *> primary_inputs = read_file(file_path, &module_name, &module_inputs, &module_outputs);
//     // for (auto dao : module_inputs)
//     // {
//     //     cout << dao.first << " " << dao.second << endl;
//     // }
//     cout << primary_inputs.find("a")->second->outputs[0]->gate_name << endl;

//     // debug
//     // for (auto dao: module_inputs){
//     //     cout << dao.first << " " << dao.second << endl;
//     // }
//     // for (auto dao: module_outputs){
//     //     cout << dao.first << " " << dao.second << endl;
//     // }

//     // auto curr = primary_inputs.find("in1[2]")->second;
//     // while (1){
//     //     cout << curr->gate_name << endl;
//     //     curr = curr->outputs[0];
//     // }
//     return 0;
// }
