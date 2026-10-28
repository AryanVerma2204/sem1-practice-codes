#include <iostream>
#include<vector>
#include<fstream>
using namespace std;

class DirectedGraph{
private:
    int vertices;
    vector<vector<int>> adjacency_list;

public:
    DirectedGraph(int vertices) : vertices(vertices) {
        adjacency_list.resize(vertices);
    }

    void add_edge(int source, int destination) {
        adjacency_list[source].push_back(destination);
    }

    const vector<vector<int>>& get_adjacency_list() const {
        return adjacency_list;
    }
    void print_adjacency_list() const {
        for (int i = 0; i < vertices; ++i) {
            cout << "Vertex " << i << ": ";
            for (int neighbor : adjacency_list[i]) {
                cout << neighbor << " ";
            }
            cout << endl;
        }
    }
};

class MarkovTransitionMatrix {
private:
    vector<vector<double>> transition_matrix;
public:
    MarkovTransitionMatrix(const DirectedGraph& graph) {
        int vertices = graph.get_adjacency_list().size();
        transition_matrix.resize(vertices, vector<double>(vertices, 0.0));
    }

    const vector<vector<double>>& get_transition_matrix() const {
        return transition_matrix;
    }

    void CreateMarkovTransitionMatrix(const DirectedGraph& graph) {
        const auto& adjacency_list = graph.get_adjacency_list();
        int vertices = adjacency_list.size();

        for (int i = 0; i < vertices; ++i) {
            int out_degree = adjacency_list[i].size();
            if (out_degree > 0) {
                double probability = 1.0 / out_degree;
                for (int neighbor : adjacency_list[i]) {
                    transition_matrix[neighbor][i] = probability;
                }
            }
        }
    }
    void print_transition_matrix() const {
        for (const auto& row : transition_matrix) {
            for (double value : row) {
                cout << value << "     ";
            }
            cout << endl;
        }
    }
};
class ReadFromFile{
public:
    void readGraphFromFile(const string& filename, DirectedGraph& graph) {
        ifstream file(filename);
        if (!file) {
            cerr << "Error opening file: " << filename << endl;
            return;
        }
        int vertices;
        file >> vertices;
        graph = DirectedGraph(vertices);
        int source, destination;
        while (file >> source >> destination) {
            graph.add_edge(source, destination);
        }
        file.close();
    }
};

class WriteToFile{
public:
    void writeTransitionMatrixToFile(const string& filename, const MarkovTransitionMatrix& markov_matrix) {
        ofstream file(filename);
        if (!file) {
            cerr << "Error opening file: " << filename << endl;
            return;
        }
        const auto& transition_matrix = markov_matrix.get_transition_matrix();
        for (const auto& row : transition_matrix) {
            for (double value : row) {
                file << value << " ";
            }
            file << endl;       
    }
        file.close();
    }
};  

class EigenvalueCalculationAlgorithm {
public:
    double rayleighQuotient(const vector<double>& x, const MarkovTransitionMatrix& markov_matrix) {
        const auto& transition_matrix = markov_matrix.get_transition_matrix();
        int vertices = transition_matrix.size();
        double numerator = 0.0;
        double denominator = 0.0;
        for(int i =0;i<vertices;i++)
        {
            double rowsum = 0.0;
            for(int j = 0; j<vertices;j++)
            {
                rowsum += transition_matrix[i][j]*x[j];
            }
            numerator = x[i]*rowsum;
            denominator += x[i]*x[i];
        }
    return numerator/denominator;
    }
    vector<double> computeDominantEigenvalueUsingPowerIteration(const MarkovTransitionMatrix& markov_matrix, int max_iterations = 100, double tolerance = 1e-6) {
        const auto& transition_matrix = markov_matrix.get_transition_matrix();
        int vertices = transition_matrix.size();
       
    }
    vector<double> computeDominantEigenvalueUsingInverseIteration(const MarkovTransitionMatrix& markov_matrix, int max_iterations = 100, double tolerance = 1e-6);
    vector<double> computeDominantEigenvalueUsingRayleighQuotientIteration(const MarkovTransitionMatrix& markov_matrix, int max_iterations = 100, double tolerance = 1e-6);

};
    

int main()
{
    // cout<< "Enter the number of vertices in the directed graph: ";
    // int vertices;
    // cin >> vertices;    
    // cout<< "Enter each edge ie source and destination vertices: ";
    ReadFromFile fileReader;
    fileReader.readGraphFromFile();
    DirectedGraph graph();
    int source, destination;
    cout << "Enter edges (source destination) one per line, and press Ctrl+D (or Ctrl+Z on Windows) to finish:" << endl;
    while (cin >> source >> destination) {
        graph.add_edge(source, destination);
    }
    MarkovTransitionMatrix markov_matrix(graph);
    markov_matrix.CreateMarkovTransitionMatrix(graph);  
    markov_matrix.print_transition_matrix();
    return 0;
}
//you need to correct the file read structure and implement the power iteration algo