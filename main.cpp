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
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

class Job {
public:
    Job(int id, int arrival_time, int duration)
            : job_id(id), arrival_time(arrival_time), duration(duration), remaining_time(duration) {}

    int job_id;
    int arrival_time;
    int duration;
    int remaining_time;

    void print_scheduled(int current_time) {
        cout << "$> Job " << job_id << ", scheduled for " << current_time << "ms" << endl;
    }

    void print_completed() {
        cout << "$> Job " << job_id << ", completed" << endl;
    }
};

// Function to simulate round-robin scheduling
void round_robin_scheduling(vector<Job>& jobs, int time_quantum) {
    unsigned int n = jobs.size();
    int current_time = 0;
    vector<Job*> completed_jobs;
    int idx = 0;

    while (completed_jobs.size() < n) {
        Job& job = jobs[idx];

        if (job.remaining_time > 0) {
            if (job.arrival_time <= current_time) {
                job.print_scheduled(current_time);
                job.remaining_time -= time_quantum;
                current_time += time_quantum;

                if (job.remaining_time <= 0) {
                    job.print_completed();
                    completed_jobs.push_back(&job);
                }
            } else {
                current_time++;
            }
        }

        idx = (idx + 1) % n; // Move to the next job in a circular manner
    }
}

int main() {
    string file_name = "job.txt"; // Replace with the name of your input file
    int time_quantum = 10; // Time quantum for round-robin scheduling

    // Read jobs from input file
    ifstream file(file_name);
    if (!file.is_open()) {
        cout << "Failed to open file: " << file_name << endl;
        return 1;
    }

    vector<Job> jobs;
    string job_line;
    while (getline(file, job_line)) {
        stringstream ss(job_line);
        string job_id_str, arrival_time_str, duration_str;
        if (getline(ss, job_id_str, ',') &&
            getline(ss, arrival_time_str, ',') &&
            getline(ss, duration_str, ',')) {
            int job_id = stoi(job_id_str);
            int arrival_time = stoi(arrival_time_str);
            int duration = stoi(duration_str);
            Job job(job_id, arrival_time, duration);
            jobs.push_back(job);
        } else {
            cout << "Failed to parse line: " << job_line << endl;
        }
    }
    file.close();

    // Perform round-robin scheduling
    round_robin_scheduling(jobs, time_quantum);

    return 0;
}
