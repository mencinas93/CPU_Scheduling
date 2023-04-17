
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include <sstream>

using namespace std;

struct Job {
    int name;
    int requested_time;
    int duration;
};

void roundRobin(vector<Job>& jobs, int quantum)
{
    queue<Job> job_queue; // queue to store jobs
    int current_time = 0; // current time in milliseconds

    while (!jobs.empty() || !job_queue.empty()) {
        if (!jobs.empty() && jobs.front().requested_time <= current_time) {
            job_queue.push(jobs.front());
            jobs.erase(jobs.begin());
        }

        if (!job_queue.empty()) {
            Job current_job = job_queue.front();
            job_queue.pop();

            int job_duration = min(quantum, current_job.duration);
            cout << "$>Job " << current_job.name << ", scheduled for " << job_duration << "ms" << endl;

            current_time += job_duration;
            current_job.duration -= job_duration;

            if (current_job.duration > 0) {
                job_queue.push(current_job);
            } else {
                cout << "$>Job " << current_job.name << " scheduled for  " << job_duration << "ms, completed" << endl;
            }
        } else {
            current_time++;
        }
    }
}
int main()
{
    string file_name = "job.txt";
    int quantum = 10;

    ifstream input(file_name);
    if (!input.is_open()) {
        cout << "Failed to open file." << endl;
        return 1;
    }

    vector<Job> jobs; // vector to store jobs

    int name;
    int requested_time;
    int duration;

    string line;
    while (getline(input, line)) {
        stringstream ss(line);
        string token;

    
        getline(ss, token, ',');
        name = stoi(token); // Convert string to integer

        getline(ss, token, ',');
        requested_time = stoi(token);

        getline(ss, token, ',');
        duration = stoi(token);

        Job job;
        job.name = name;
        job.requested_time = requested_time;
        job.duration = duration;
        jobs.push_back(job);
    }

    input.close();

    roundRobin(jobs, quantum);

    return 0;
}
