/*
 We learned several CPU scheduling algorithm in class. Your task for this project is to simulate the round robin CPU scheduling with time quantum = 10ms algorithm using an input file containing jobs for CPU

 Project Details:

 Input:

 Job.txt is provided as input file. Each line contains the name of the job, requesting time (millisecond since computer started) and duration (millisecond). For example:

 Job 1, 20, 50

 means a job for CPU called “Job 1” is requested to run at 20ms since CPU started, and the duration of the job is 50ms.

 Output:

 Schedule job order similar to the following format

 $>Job 1, scheduled for 4ms
 $>Job 2, scheduled for 3ms
 $>Job 1, scheduled for 5ms
 $>Job 3, scheduled for 5ms
 $>Job 2, scheduled for 3ms, completed
 $>job 1, scheduled for 2ms, completed

 Because round robin is deterministic, you should see the same job scheduling result every time you run your code.

 */
#include <fstream>
#include <iostream>
#include <string>
#include <vector>


using namespace std;
//job class with constructor of arrtime,burst and name
class Job{
public: Job(int id, int arrival_time,int burst_time): id_(id), arrival_time_(arrival_time), burst_time_(burst_time){}
    int id() const {
        return id_;
    }
    int arrival_time() const {
        return arrival_time_;
    }
    int burst_time() const {
        return burst_time_;
    }
    //public access to private
private:
    int id_;
    int arrival_time_;
    int burst_time_;
};
int main() {
    ifstream iFile;
    
    iFile.open("job.txt");
    if (!iFile.is_open()){
        cout << "Not inputting file!/n";
    }
    vector<Job> jobs;
    //vector to place job lines

    string line;
    int id = 0;
    // name of ID
    while(getline(iFile,line)){
        int arrival_time,burst_time;
        if(sscanf(line.c_str(), "%d,%d,%d", &id, &arrival_time, &burst_time) != 3) {
            //reads three integers separated by commas
            //turns string input to integer
            cout << "Invalid input line: " << line << endl;
// if cant be inputted error alert
            continue;
        }
        jobs.push_back(Job(id, arrival_time, burst_time));
    }
    for (const auto& job : jobs) {
            cout << "Job " << job.id() << ": Arrival Time " << job.arrival_time() << ", Burst Time " << job.burst_time() << endl;
        }
    return 0;
}
