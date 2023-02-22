//HW 1 Vipul Sawant
// SU ID 347120278

#include<iostream>
#include<thread>
#include<vector>
#include <fstream>

using namespace std;


class Timer {
public:
    chrono::system_clock::time_point Begin;
    chrono::system_clock::time_point End;
    chrono::system_clock::duration RunTime;
    Timer() {//constructor
        Begin = chrono::system_clock::now();
    }
    ~Timer() {
        End = chrono::system_clock::now();
        RunTime = End - Begin;
        cout << "Run Time is " << chrono::duration_cast<chrono::milliseconds>(RunTime).count() << "ms" << endl;
    }
};

ofstream out1("Output1.txt");
ofstream out2("Output2.txt");


void Sort_Iterative(vector<int> &Data,int n1,int n2, int j,int i, bool up);
void Sort_Iterative_main(vector<int>& Data, bool up);

void Front_Recursive(vector<int>& Data, int n1, int n2, bool up, bool front_call_sort);
//Front function modified for including calls that need to be terminated after single compariosn cycle 

void Sort_Recursive(vector<int>& Data, int n1, int n2, bool Up, bool thread_call);
//Sort function modified for including calls made by thread. 
//Initially to be called as false in all cases

int main() {

    int n{ 536870912 }, m{ 25 };//536870912
    vector<int> Data(n);
    for (auto& i : Data) i = rand() % m;
    {
        Timer TT;
        Sort_Recursive(Data, 0, int(Data.size() - 1), true, false);
    }
    for (auto i : Data) {
        out1 << i << " ";
    }
    cout << "Finished Printing file 1" << endl;
    for (auto& i : Data) i = rand() % m;

    {
        Timer TT;
        Sort_Iterative_main(Data, true);
        
    }
    for (auto i : Data) {
        out2 << i << " ";
    }
    cout << "Finished Printing file 2" << endl;
	return 0;
}
void Sort_Iterative_main(vector<int>& Data, bool up) {
    for (int i = 2; i <= Data.size(); i *= 2) {
        for (int j = i / 2; j > 0; j /= 2) {
            if (i == Data.size() / 2 && j == Data.size() / 4) {
                thread T1(Sort_Iterative, ref(Data), 0, int(Data.size() - 1) / 8, j, i, up);
                thread T2(Sort_Iterative, ref(Data), (int(Data.size() - 1) / 8) + 1, int(Data.size() - 1) / 4, j, i, up);
                thread T3(Sort_Iterative, ref(Data), (int(Data.size() - 1) / 2) + 1, int(Data.size() / 2) + int(Data.size() - 1) / 8, j, i, !up);
                Sort_Iterative(Data, (int(Data.size() / 2) + int(Data.size() - 1) / 8) + 1, int(Data.size() / 2) + int(Data.size() - 1) / 4, j, i, !up);
                T1.join();
                T2.join();
                T3.join();
            }
            else if (i == Data.size() && j == Data.size() / 2) {
                thread T1(Sort_Iterative, ref(Data), 0, int(Data.size() / 8) - 1, j, i, up);
                thread T2(Sort_Iterative, ref(Data), int(Data.size() / 8), int(Data.size() / 4) - 1, j, i, up);
                thread T3(Sort_Iterative, ref(Data), int(Data.size() / 4), int(Data.size() / 4) + int(Data.size() / 8) - 1, j, i, up);
                Sort_Iterative(Data, int(Data.size() / 4) + int(Data.size() / 8), int(Data.size() / 2) - 1, j, i, up);
                T1.join();
                T2.join();
                T3.join();
            }
            else if (i == Data.size() && j == Data.size() / 4) {
                thread T1(Sort_Iterative, ref(Data), 0, int(Data.size() - 1) / 8, j, i, up);
                thread T2(Sort_Iterative, ref(Data), (int(Data.size() - 1) / 8) + 1, int(Data.size() - 1) / 4, j, i, up);
                thread T3(Sort_Iterative, ref(Data), (int(Data.size() - 1) / 2) + 1, int(Data.size() / 2) + int(Data.size() - 1) / 8, j, i, up);
                Sort_Iterative(Data, (int(Data.size() / 2) + int(Data.size() - 1) / 8) + 1, int(Data.size() / 2) + int(Data.size() - 1) / 4, j, i, up);
                T1.join();
                T2.join();
                T3.join();
            }
            else 
            {
                if (i == Data.size() / 2) {
                    thread T1(Sort_Iterative, ref(Data), 0, int(Data.size() - 1) / 4, j, i, up);
                    thread T2(Sort_Iterative, ref(Data), (int(Data.size() - 1) / 4) + 1, int(Data.size() - 1) / 2, j, i, up);
                    thread T3(Sort_Iterative, ref(Data), (int(Data.size() - 1) / 2) + 1, int(Data.size() / 4) * 3 -1, j, i, !up);
                    Sort_Iterative(Data, int(Data.size() / 4) * 3, int(Data.size() - 1), j, i, !up);
                    T1.join();
                    T2.join();
                    T3.join();
                }
                else if (i == Data.size()) {
                    thread T1(Sort_Iterative, ref(Data), 0, int(Data.size() - 1) / 4, j, i, up);
                    thread T2(Sort_Iterative, ref(Data), (int(Data.size() - 1) / 4) + 1, int(Data.size() - 1) / 2, j, i, up);
                    thread T3(Sort_Iterative, ref(Data), (int(Data.size() - 1) / 2) + 1, int(Data.size() / 4) * 3 - 1, j, i, up);
                    Sort_Iterative(Data, int(Data.size() / 4) * 3, int(Data.size() - 1), j, i, up);
                    T1.join();
                    T2.join();
                    T3.join();
                }
                else {
                    thread T1(Sort_Iterative, ref(Data), 0, int(Data.size() - 1) / 4, j, i, up);
                    thread T2(Sort_Iterative, ref(Data), (int(Data.size() - 1) / 4) + 1, int(Data.size() - 1) / 2, j, i, !up);
                    thread T3(Sort_Iterative, ref(Data), (int(Data.size() - 1) / 2) + 1, int(Data.size() / 4) * 3 - 1, j, i, up);
                    Sort_Iterative(Data, int(Data.size() / 4) * 3, int(Data.size() - 1), j, i, !up);
                    T1.join();
                    T2.join();
                    T3.join();
                }
            }
        }
    }
}


void Sort_Iterative(vector<int>&Data,int n1, int n2, int j,int l, bool up) {
    
    if ((l == Data.size() / 2) && j == l / 2 || (l == Data.size()) && ( j == l/2 || j == l/4)) {
        for (int i = n1; i <= n2; i++) {
            if (up) {
                if (Data[i] > Data[i + j]) swap(Data[i], Data[i + j]);
            }
            else if (Data[i] < Data[i + j]) swap(Data[i], Data[i + j]);
        }
    }
    else {
        int a = l / 2;
        if (l == 2 && j == 1) up = up;
        for (int i = n1; i < n2; i += 2 * j) {
            for (int k = 0; k < j; k++) {
                if (up) {
                    if (Data[i + k] > Data[i + k + j]) swap(Data[i + k], Data[i + k + j]);
                }
                else if (Data[i + k] < Data[i + k + j]) swap(Data[i + k], Data[i + k + j]);
                a--;
            }
            if (a == 0 && l != Data.size()) {
                up = !up;
                a = l / 2;
            }
        }
    }
}

void Front_Recursive(vector<int>& Data, int n1, int n2, bool up, bool front_call_sort) {

    for (int i = 0; i <= (n2 - n1) / 2; ++i) {
        if (up) {
            if (Data[n1 + i] > Data[n1 + i + (n2 - n1 + 1) / 2]) swap(Data[n1 + i], Data[n1 + i + (n2 - n1 + 1) / 2]);
        }
        else if (Data[n1 + i] < Data[n1 + i + (n2 - n1 + 1) / 2]) swap(Data[n1 + i], Data[n1 + i + (n2 - n1 + 1) / 2]);
    }

    if (n2 - n1 == 1 || front_call_sort == true) return;
    Front_Recursive(Data, n1, (n2 + n1) / 2, up, false);
    Front_Recursive(Data, (n2 + n1) / 2 + 1, n2, up, false);
}
void Sort_Recursive(vector<int>& Data, int n1, int n2, bool Up, bool thread_call) {

    if (Data.size() <= 4) {
        if (n2 - n1 == 1) {
            if (Up) {
                if (Data[n1] > Data[n2]) swap(Data[n1], Data[n2]);
            }
            else {
                if (Data[n1] < Data[n2]) swap(Data[n1], Data[n2]);
            }

            return;
        }
        Sort_Recursive(Data, n1, (n1 + n2) / 2, Up, false);
        Sort_Recursive(Data, (n1 + n2) / 2 + 1, n2, !Up, false);
        Front_Recursive(Data, n1, n2, Up, false);
    }
    else {
        if (n2 - n1 == Data.size() - 1) {
            //First Sort using 4 threads
            {
                thread T1(Sort_Recursive, ref(Data), 0, int(Data.size() - 1) / 4, Up, true);
                thread T2(Sort_Recursive, ref(Data), (int(Data.size() - 1) / 4) + 1, int(Data.size() - 1) / 2, !Up, true);
                thread T3(Sort_Recursive, ref(Data), (int(Data.size() - 1) / 2) + 1, int(Data.size() / 4) * 3 - 1, Up, true);
                Sort_Recursive(Data, int(Data.size() / 4) * 3, int(Data.size() - 1), !Up, true);
                if (T1.joinable())T1.join();
                if (T2.joinable())T2.join();
                if (T3.joinable())T3.join();
            }
            //Bottleneck for 4 threads hence using 2 threadsto call front
            {
                thread T1(Front_Recursive, ref(Data), 0, int(Data.size() - 1) / 2, Up, true);
                Front_Recursive(Data, (int(Data.size() - 1) / 2) + 1, int(Data.size() - 1), !Up, true);
                if (T1.joinable())T1.join();
            }
            // Front using 4 threads
            {
                thread T1(Front_Recursive, ref(Data), 0, int(Data.size() - 1) / 4, Up, false);
                thread T2(Front_Recursive, ref(Data), (int(Data.size() - 1) / 4) + 1, int(Data.size() - 1) / 2, Up, false);
                thread T3(Front_Recursive, ref(Data), (int(Data.size() - 1) / 2) + 1, int(Data.size() / 4) * 3 - 1, !Up, false);
                Front_Recursive(Data, int(Data.size() / 4) * 3, int(Data.size() - 1), !Up, false);
                if (T1.joinable())T1.join();
                if (T2.joinable())T2.join();
                if (T3.joinable())T3.join();
            }
        }

        if (n2 - n1 == 1) {
            if (Up) {
                if (Data[n1] > Data[n2]) swap(Data[n1], Data[n2]);
            }
            else {
                if (Data[n1] < Data[n2]) swap(Data[n1], Data[n2]);
            }

            return;
        }
        if (thread_call) {// Sort and front calls if called by threads
            Sort_Recursive(Data, n1, (n1 + n2) / 2, Up, true);
            Sort_Recursive(Data, (n1 + n2) / 2 + 1, n2, !Up, true);
            Front_Recursive(Data, n1, n2, Up, false);
            return;
        }

        //Single thread call for front
        {
            Front_Recursive(Data, n1, n2, Up, true);
        }
        //Bottleneck after compariosn of all elements as grouping can be done in 2 parts
        {
            thread T1(Front_Recursive, ref(Data), 0, int(Data.size() - 1) / 2, Up, true);
            Front_Recursive(Data, (int(Data.size() - 1) / 2) + 1, int(Data.size() - 1), Up, true);
            if (T1.joinable())T1.join();
        }
        //Final Front using 4 threads with all being ascending or descending
        {
            thread T1(Front_Recursive, ref(Data), 0, int(Data.size() - 1) / 4, Up, false);
            thread T2(Front_Recursive, ref(Data), (int(Data.size() - 1) / 4) + 1, int(Data.size() - 1) / 2, Up, false);
            thread T3(Front_Recursive, ref(Data), (int(Data.size() - 1) / 2) + 1, int(Data.size() / 4) * 3 - 1, Up, false);
            Front_Recursive(Data, int(Data.size() / 4) * 3, int(Data.size() - 1), Up, false);
            if (T1.joinable())T1.join();
            if (T2.joinable())T2.join();
            if (T3.joinable())T3.join();
        }
    }
}


