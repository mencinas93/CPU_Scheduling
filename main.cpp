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
public: Job(int id, int arrival_time,int burst_time): id_(id), arrival_time_(arrival_time), burst_time_(burst_time), remaining_time_(burst_time){}
    int id() const {
        return id_;
    }
    int arrival_time() const {
        return arrival_time_;
    }
    int burst_time() const {
        return burst_time_;
    }
    int remaining_time() const {
            return remaining_time_;
        }
    //remainder time
        void set_remaining_time(int remaining_time) {
            remaining_time_ = remaining_time;
        }
    //updates the status of remaining time.
    //public access to private
private:
    int id_;
    int arrival_time_;
    int burst_time_;
    int remaining_time_;
};

class Scheduler {
public:
    Scheduler(vector<Job>& jobs) : jobs_(jobs) {}

    void run() {
        int current_time = 0;

        while (!jobs_.empty()) {
            Job& job = jobs_.front();

            if (job.remaining_time() <= 10) {
                cout << "$>Job " << job.id() << ", scheduled for " << job.remaining_time() << "ms, completed" << endl;
                current_time += job.remaining_time();
                jobs_.erase(jobs_.begin());
            } else {
                cout << "$>Job " << job.id() << ", scheduled for 10ms" << endl;
                current_time += 10;
                job.set_remaining_time(job.remaining_time()-10);

                // Move the job to the back of the queue
                jobs_.push_back(job);
                jobs_.erase(jobs_.begin());            }
            for (int i = 0; i < jobs_.size(); ) {
                if (jobs_[i].arrival_time() <= current_time) {
                    cout << "$>Job " << jobs_[i].id() << ", scheduled for " << jobs_[i].burst_time() - jobs_[i].remaining_time() << "ms" << endl;
                    //add the job to the front of the queue
                    jobs_.insert(jobs_.begin(), jobs_[i]);
                    jobs_.erase(jobs_.begin() + i);
                    i = 0;
                } else {
                    i++;
            // Check if any new jobs have arrived
           
                }
            }
        }
    }

private:
    vector<Job>& jobs_;
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
    int id = 1;
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
        jobs.push_back(Job(id++, arrival_time, burst_time));
    }
    Scheduler scheduler(jobs);
      scheduler.run();

    
    for (const auto& job : jobs) {
            cout << "Job " << job.id() << ": Arrival Time " << job.arrival_time() << ", Burst Time " << job.burst_time() << endl;
        }
     
    return 0;
}
